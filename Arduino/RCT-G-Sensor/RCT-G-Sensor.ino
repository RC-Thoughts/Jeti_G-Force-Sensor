/*
   -----------------------------------------------------------
                   Jeti G-Sensor v 1.1
   -----------------------------------------------------------

    Tero Salminen RC-Thoughts.com (c) 2017 www.rc-thoughts.com

  -----------------------------------------------------------

    Acceleration sensor for Jeti EX telemetry with cheap
    ADXL345 breakout-board and Arduino Pro Mini

    Jeti sensor values:
    - X-Axis G-force (in G)
    - Y-Axis G-force (in G)
    - Z-Axis G-force (in G)
    - Pitch angle (in °)
    - Roll angle (in °)

    User calibratable for all values

  -----------------------------------------------------------
    Shared under MIT-license by Tero Salminen (c) 2017
  -----------------------------------------------------------
*/
String gVersion = "v.1.1";
#include <EEPROM.h>
#include <stdlib.h>
#include <SoftwareSerialJeti.h>
#include <JETI_EX_SENSOR.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define prog_char  char PROGMEM
#define GETCHAR_TIMEOUT_ms 20

#ifndef JETI_RX
#define JETI_RX 3
#endif

#ifndef JETI_TX
#define JETI_TX 4
#endif

#define ITEMNAME_1 F("X-Axis")
#define ITEMTYPE_1 F("G")
#define ITEMVAL_1 &gX

#define ITEMNAME_2 F("Y-Axis")
#define ITEMTYPE_2 F("G")
#define ITEMVAL_2 &gY

#define ITEMNAME_3 F("Z-Axis")
#define ITEMTYPE_3 F("G")
#define ITEMVAL_3 &gZ

#define ITEMNAME_4 F("Pitch")
#define ITEMTYPE_4 F("\xB0")
#define ITEMVAL_4 &aPitch

#define ITEMNAME_5 F("Roll")
#define ITEMTYPE_5 F("\xB0")
#define ITEMVAL_5 &aRoll

#define ABOUT_1 F(" RCT Jeti Tools")
#define ABOUT_2 F("    G-Sensor")

SoftwareSerial JetiSerial(JETI_RX, JETI_TX);

void JetiUartInit()
{
  JetiSerial.begin(9700);
}

void JetiTransmitByte(unsigned char data, boolean setBit9)
{
  JetiSerial.set9bit = setBit9;
  JetiSerial.write(data);
  JetiSerial.set9bit = 0;
}

unsigned char JetiGetChar(void)
{
  unsigned long time = millis();
  while ( JetiSerial.available()  == 0 )
  {
    if (millis() - time >  GETCHAR_TIMEOUT_ms)
      return 0;
  }
  int read = -1;
  if (JetiSerial.available() > 0 )
  { read = JetiSerial.read();
  }
  long wait = (millis() - time) - GETCHAR_TIMEOUT_ms;
  if (wait > 0)
    delay(wait);
  return read;
}

char * floatToString(char * outstr, float value, int places, int minwidth = 0) {
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;
  int c = 0;
  int charcount = 1;
  int extra = 0;
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  for (i = 0; i < places; i++)
    d /= 10.0;
  tempfloat +=  d;
  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }
  if (tenscount > 0)
    charcount += tenscount;
  else
    charcount += 1;
  if (value < 0)
    charcount += 1;
  charcount += 1 + places;
  minwidth += 1;
  if (minwidth > charcount) {
    extra = minwidth - charcount;
    charcount = minwidth;
  }
  if (value < 0)
    outstr[c++] = '-';
  if (tenscount == 0)
    outstr[c++] = '0';
  for (i = 0; i < tenscount; i++) {
    digit = (int) (tempfloat / tens);
    itoa(digit, &outstr[c++], 10);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }
  if (places > 0)
    outstr[c++] = '.';
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    itoa(digit, &outstr[c++], 10);
    tempfloat = tempfloat - (float) digit;
  }
  if (extra > 0 ) {
    for (int i = 0; i < extra; i++) {
      outstr[c++] = ' ';
    }
  }
  outstr[c++] = '\0';
  return outstr;
}

JETI_Box_class JB;

unsigned char SendFrame()
{
  boolean bit9 = false;
  for (int i = 0 ; i < JB.frameSize ; i++ )
  {
    if (i == 0)
      bit9 = false;
    else if (i == JB.frameSize - 1)
      bit9 = false;
    else if (i == JB.middle_bit9)
      bit9 = false;
    else
      bit9 = true;
    JetiTransmitByte(JB.frame[i], bit9);
  }
}

uint8_t frame[10];
short value = 27;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

float gX = 0;
float gY = 0;
float gZ = 0;
int aPitch = 0;
int aRoll = 0;
float xCalVal = EEPROM.read(0);
float yCalVal = EEPROM.read(1);
float zCalVal = EEPROM.read(2);
float pCalVal = EEPROM.read(3);
float rCalVal = EEPROM.read(4);

#define MAX_SCREEN 8
#define MAX_CONFIG 1
#define COND_LES_EQUAL 1
#define COND_MORE_EQUAL 2

void setup()
{
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.println("");
  Serial.print("RC-Thoughts G-Sensor "); Serial.println(gVersion);
  Serial.println("design by Tero Salminen @ RC-Thoughts 2017");
  Serial.println("Free and open-source - Released under MIT-license");
  Serial.println("");
  Serial.println("Ready!");
  Serial.println("");

  pinMode(JETI_RX, OUTPUT);
  JetiUartInit();

  // Reset calibration values if never set
  if (xCalVal == 255) {
    xCalVal = 0;
  }
  if (yCalVal == 255) {
    yCalVal = 0;
  }
  if (zCalVal == 255) {
    zCalVal = 0;
  }
  if (pCalVal == 255) {
    pCalVal = 0;
  }
  if (rCalVal == 255) {
    rCalVal = 0;
  }
  
  // Fix negative calibration values
  if (xCalVal > 126) {
    xCalVal = xCalVal - 255;
  }
  if (yCalVal > 126) {
    yCalVal = yCalVal - 255;
  }
  if (zCalVal > 126) {
    zCalVal = zCalVal - 255;
  }
  if (pCalVal > 126) {
    pCalVal = pCalVal - 255;
  }
  if (rCalVal > 126) {
    rCalVal = rCalVal - 255;
  }
  
  accel.begin();
  accel.setRange(ADXL345_RANGE_16_G);
  accel.setDataRate(ADXL345_DATARATE_400_HZ);

  JB.JetiBox(ABOUT_1, ABOUT_2);
  JB.Init(F("RCT"));
  JB.addData(ITEMNAME_1, ITEMTYPE_1);
  JB.addData(ITEMNAME_2, ITEMTYPE_2);
  JB.addData(ITEMNAME_3, ITEMTYPE_3);
  JB.addData(ITEMNAME_4, ITEMTYPE_4);
  JB.addData(ITEMNAME_5, ITEMTYPE_5);
  JB.setValue(1, ITEMVAL_1, 1);
  JB.setValue(2, ITEMVAL_2, 1);
  JB.setValue(3, ITEMVAL_3, 1);
  JB.setValue(4, ITEMVAL_4);
  JB.setValue(5, ITEMVAL_5);

  do {
    JB.createFrame(1);
    SendFrame();
    delay(GETCHAR_TIMEOUT_ms);
  }
  while (sensorFrameName != 0);
  digitalWrite(13, LOW);
}

int header = 0;
int lastbtn = 240;
int current_screen = 0;
int current_config = 0;
char temp[LCDMaxPos / 2];
char msg_line1[LCDMaxPos / 2];
char msg_line2[LCDMaxPos / 2];

void process_screens()
{
  switch (current_screen)
  {
    case 0 : {
        JB.JetiBox(ABOUT_1, ABOUT_2);
        break;
      }
    case 1 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F(" Set X to 0.0G"));
        if (gX < 0) {
          strcat_P((char*)&msg_line2, (prog_char*)F(" X:"));
        } else {
          strcat_P((char*)&msg_line2, (prog_char*)F(" X: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gX, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (prog_char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, xCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 2 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F(" Set Y to 0.0G"));
        if (gY < 0) {
          strcat_P((char*)&msg_line2, (prog_char*)F(" Y:"));
        } else {
          strcat_P((char*)&msg_line2, (prog_char*)F(" Y: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gY, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (prog_char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, yCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 3 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F(" Set Z to 1.0G"));
        if (gZ < 0) {
          strcat_P((char*)&msg_line2, (prog_char*)F(" Z:"));
        } else {
          strcat_P((char*)&msg_line2, (prog_char*)F(" Z: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gZ, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (prog_char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, zCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 4 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F("Set Pitch to 0\xB0"));
        if (aPitch < 0) {
          strcat_P((char*)&msg_line2, (prog_char*)F("Val:"));
        } else {
          strcat_P((char*)&msg_line2, (prog_char*)F("Val: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, aPitch, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (prog_char*)F("\xB0 Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, pCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 5 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F("Set Roll to 0\xB0"));
        if (aRoll < 0) {
          strcat_P((char*)&msg_line2, (prog_char*)F("Val:"));
        } else {
          strcat_P((char*)&msg_line2, (prog_char*)F("Val: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, aRoll, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (prog_char*)F("\xB0 Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, rCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 6 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F("Save: Up and Dn"));
        strcat_P((char*)&msg_line2, (prog_char*)F("Back: <"));
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case 99 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (prog_char*)F("Settings stored!"));
        strcat_P((char*)&msg_line2, (prog_char*)F("Press < to exit"));
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
      }
    case MAX_SCREEN : {
        JB.JetiBox(ABOUT_1, ABOUT_2);
        break;
      }
  }
}

void loop()
{
  // May the G-Force be with you
  sensors_event_t event;
  accel.getEvent(&event);

  gX = (round(event.acceleration.x * 1.01972) / 10.0) - (xCalVal / 10);
  gY = (round(event.acceleration.y * 1.01972) / 10.0) - (yCalVal / 10);
  gZ = (round(event.acceleration.z * 1.01972) / 10.0) + (zCalVal / 10);
  gX = gX * -1.0;
  gY = gY * -1.0;

  aPitch = atan2(event.acceleration.x, event.acceleration.z) * (180 / PI) - (pCalVal);
  aRoll = atan2(event.acceleration.y, event.acceleration.z) * (180 / PI) - (rCalVal);
  aPitch = (aPitch * -1);
  aRoll = (aRoll * -1);

  // Debug - remove /* and */ below to enable
  /*
  Serial.print("X: "); Serial.print(gX);
  Serial.print(" Y: "); Serial.print(gY);
  Serial.print(" Z: "); Serial.print(gZ);
  Serial.print(" Pitch: "); Serial.print(aPitch);
  Serial.print(" Roll: "); Serial.print(aRoll);
  Serial.print(" xCal: "); Serial.print(xCalVal);
  Serial.print(" yCal: "); Serial.print(yCalVal);
  Serial.print(" zCal: "); Serial.print(zCalVal);
  Serial.print(" pCal: "); Serial.print(pCalVal);
  Serial.print(" rCal: "); Serial.println(rCalVal);
  */

  // Jeti stuff from here
  unsigned long time = millis();
  SendFrame();
  time = millis();
  int read = 0;
  pinMode(JETI_RX, INPUT);
  pinMode(JETI_TX, INPUT_PULLUP);

  JetiSerial.listen();
  JetiSerial.flush();

  while ( JetiSerial.available()  == 0 )
  {
    if (millis() - time >  5)
      break;
  }

  if (JetiSerial.available() > 0 )
  { read = JetiSerial.read();
    if (lastbtn != read)
    {
      lastbtn = read;
      switch (read)
      {
        case 224 : // RIGHT
          if (current_screen != MAX_SCREEN)
          {
            current_screen++;
            if (current_screen == 6) {
              current_screen = 6;
            }
          }
          break;
        case 112 : // LEFT
          if (current_screen == 99) {
            current_screen = 0;
          }
          if (current_screen != 0) {
            current_screen--;
          }
          break;
        case 208 : // UP
          if (current_screen == 1) {
            xCalVal = xCalVal + 1;
          }
          if (current_screen == 2) {
            yCalVal = yCalVal + 1;
          }
          if (current_screen == 3) {
            zCalVal = zCalVal + 1;
          }
          if (current_screen == 4) {
            pCalVal = pCalVal + 1;
          }
          if (current_screen == 5) {
            rCalVal = rCalVal + 1;
          }
          break;
        case 176 : // DOWN
          if (current_screen == 1) {
            xCalVal = xCalVal - 1;
          }
          if (current_screen == 2) {
            yCalVal = yCalVal - 1;
          }
          if (current_screen == 3) {
            zCalVal = zCalVal - 1;
          }
          if (current_screen == 4) {
            pCalVal = pCalVal - 1;
          }
          if (current_screen == 5) {
            rCalVal = rCalVal - 1;
          }
          break;
        case 144 : // UP+DOWN
          if (current_screen == 6) {
            // Store values to eeprom
            EEPROM.write(0, xCalVal);
            EEPROM.write(1, yCalVal);
            EEPROM.write(2, zCalVal);
            EEPROM.write(3, pCalVal);
            EEPROM.write(4, rCalVal);
            current_screen = 99;
          }
          break;
        case 96 : // LEFT+RIGHT
          if (current_screen == 0) {
            xCalVal = 0;
            yCalVal = 0;
            zCalVal = 0;
            pCalVal = 0;
            rCalVal = 0;
            EEPROM.write(0, xCalVal);
            EEPROM.write(1, yCalVal);
            EEPROM.write(2, zCalVal);
            EEPROM.write(3, pCalVal);
            EEPROM.write(4, rCalVal);
            current_screen = 99;
          }
          break;
      }
    }
  }
  if (current_screen != MAX_SCREEN)
    current_config = 0;
  process_screens();
  header++;
  if (header >= 5)
  {
    JB.createFrame(1);
    header = 0;
  }
  else
  {
    JB.createFrame(0);
  }

  long wait = GETCHAR_TIMEOUT_ms;
  long milli = millis() - time;
  if (milli > wait)
    wait = 0;
  else
    wait = wait - milli;
  pinMode(JETI_TX, OUTPUT);
}

