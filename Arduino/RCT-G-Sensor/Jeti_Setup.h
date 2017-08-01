//
// Stuff that needs to be inside void setup()
//

// Sensor Name
JB.Init(F("RCT"), JETI_RX, 9700); // Define Sensor name

// Define Jeti Sensor value name & unit & variable & precision (decimals)
// JB.setValue14(JB.addData(F("NAME"), F("UNIT")), &VARIABLE, DEC);
//
// Sensor-value ranges:
// JB.setValue6 =   -31 to 31               (Variable is uint8_t)
// JB.setValue14 =  -8191 to 8191           (Variable is int)
// JB.setValue30 =  -536870911 to 536870911 (Variable is long)

JB.setValue14(JB.addData(F("X-Axis"), F("G")), &gXc, 1);
JB.setValue14(JB.addData(F("Y-Axis"), F("G")), &gYc, 1);
JB.setValue14(JB.addData(F("Z-Axis"), F("G")), &gZc, 1);
JB.setValue14(JB.addData(F("Pitch"), F("\xB0")), &aPitch, 0);
JB.setValue14(JB.addData(F("Roll"), F("\xB0")), &aRoll, 0);

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
