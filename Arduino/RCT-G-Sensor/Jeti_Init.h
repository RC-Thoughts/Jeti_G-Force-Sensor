//
// Stuff done in initialisation of sketch
//

// Jetibox Start Screen
//
#define ABOUT_1 F(" RCT Jeti Tools")
#define ABOUT_2 F(" G-Sensor  v1.3")

//
// Max screens in jetibox (navigating over this goes to start)
//
#define MAX_SCREEN 10

//
// Sensor ID (0x02) - Needs to be unique in a model
//
const unsigned char Jeti_SensorID4 = 0x02;

//
// Sensor variables & other init-stuff nede
//
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
float gX = 0;
float gY = 0;
float gZ = 0;
float gXc = 0;
float gYc = 0;
float gZc = 0;
long gXv = 0;
long gYv = 0;
long gZv = 0;
float xCalVal = EEPROM.read(0);
float yCalVal = EEPROM.read(1);
float zCalVal = EEPROM.read(2);
int FilterOnOff = EEPROM.read(3);
int Ndec = EEPROM.read(4);
