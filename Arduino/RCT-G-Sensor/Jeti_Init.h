//
// Stuff done in initialisation of sketch
//

// Jetibox Start Screen
//
#define ABOUT_1 F(" RCT Jeti Tools")
#define ABOUT_2 F("    G-Sensor")

//
// Max screens in jetibox (navigating over this goes to start)
//
#define MAX_SCREEN 8

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
int gXc = 0;
int gYc = 0;
int gZc = 0;
int aPitch = 0;
int aRoll = 0;
float xCalVal = EEPROM.read(0);
float yCalVal = EEPROM.read(1);
float zCalVal = EEPROM.read(2);
float pCalVal = EEPROM.read(3);
float rCalVal = EEPROM.read(4);
