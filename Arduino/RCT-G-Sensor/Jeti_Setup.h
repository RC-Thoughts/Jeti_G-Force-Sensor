//
// Stuff that needs to be inside void setup()
//

// Sensor Name
// Serial speed is 10240 for Pro Mini 3.3V due software serial
JB.Init(F("RCT-G"), JETI_RX, 10240);

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
if (FilterOnOff == 255) {
  FilterOnOff = 0;
}
if (Ndec == 255) {
  Ndec = 1;
}

// Fix negative calibration values
if (xCalVal > 126) {
  xCalVal = xCalVal - 256;
}
if (yCalVal > 126) {
  yCalVal = yCalVal - 256;
}
if (zCalVal > 126) {
  zCalVal = zCalVal - 256;
}
if (FilterOnOff > 2) {
  FilterOnOff = 0;
}
if (Ndec > 2 or Ndec < 1) {
  Ndec = 1;
}

// Define Jeti Sensor value name & unit & variable & precision (decimals)
// JB.setValue30(JB.addData(F("NAME"), F("UNIT")), &VARIABLE, DEC);
//
// Sensor-value ranges:
// JB.setValue6 =   -31 to 31               (Variable is uint8_t)
// JB.setValue30 =  -8191 to 8191           (Variable is int)
// JB.setValue30 =  -536870911 to 536870911 (Variable is long)

if (FilterOnOff != 1) {
  JB.setValue30(JB.addData(F("X-Axis"), F("G")), &gXr, Ndec);
  JB.setValue30(JB.addData(F("Y-Axis"), F("G")), &gYr, Ndec);
  JB.setValue30(JB.addData(F("Z-Axis"), F("G")), &gZr, Ndec);
}

if (FilterOnOff != 0) {
  JB.setValue30(JB.addData(F("X-Axis"), F("G")), &gXf, Ndec);
  JB.setValue30(JB.addData(F("Y-Axis"), F("G")), &gYf, Ndec);
  JB.setValue30(JB.addData(F("Z-Axis"), F("G")), &gZf, Ndec);
}

accel.begin();
accel.setRange(ADXL345_RANGE_16_G);
accel.setDataRate(ADXL345_DATARATE_400_HZ);
