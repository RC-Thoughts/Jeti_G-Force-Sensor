//
// Build Jetibox screens
//

switch (current_screen)
{
case 0 : {
    JB.JetiBox_P(ABOUT_1, ABOUT_2);
    break;
  }
case 1 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Calib. X to 0.0G"));
    if (gXc < 0) {
      strcat_P((char*)&msg_line2, (const char*)F("X:"));
    } else {
      strcat_P((char*)&msg_line2, (const char*)F("X: "));
    }
    temp[0] = 0;
    floatToString((char*)&temp, gXc, 2);
    strcat((char*)&msg_line2, (char*)&temp);
    strcat_P((char*)&msg_line2, (const char*)F(" Cor:"));
    temp[0] = 0;
    floatToString((char*)&temp, xCalVal, 0);
    strcat((char*)&msg_line2, (char*)&temp);
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 2 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Calib. Y to 0.0G"));
    if (gYc < 0) {
      strcat_P((char*)&msg_line2, (const char*)F("Y:"));
    } else {
      strcat_P((char*)&msg_line2, (const char*)F("Y: "));
    }
    temp[0] = 0;
    floatToString((char*)&temp, gYc, 2);
    strcat((char*)&msg_line2, (char*)&temp);
    strcat_P((char*)&msg_line2, (const char*)F(" Cor:"));
    temp[0] = 0;
    floatToString((char*)&temp, yCalVal, 0);
    strcat((char*)&msg_line2, (char*)&temp);
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 3 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Calib. Z to 1.0G"));
    if (gZc < 0) {
      strcat_P((char*)&msg_line2, (const char*)F("Z:"));
    } else {
      strcat_P((char*)&msg_line2, (const char*)F("Z: "));
    }
    temp[0] = 0;
    floatToString((char*)&temp, gZc, 2);
    strcat((char*)&msg_line2, (char*)&temp);
    strcat_P((char*)&msg_line2, (const char*)F(" Cor:"));
    temp[0] = 0;
    floatToString((char*)&temp, zCalVal, 0);
    strcat((char*)&msg_line2, (char*)&temp);
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 4 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Sensor: "));

    if (FilterOnOff == 0) {
      strcat_P((char*)&msg_line1, (const char*)F("Raw"));
    }
    else if (FilterOnOff == 1) {
      strcat_P((char*)&msg_line1, (const char*)F("Filtered"));
    }
    strcat_P((char*)&msg_line2, (const char*)F("Press Up/Dn"));
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 5 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Decimals: "));
    if (Ndec == 1) {
      strcat_P((char*)&msg_line1, (const char*)F("0.0G"));
    }
    if (Ndec == 2) {
      strcat_P((char*)&msg_line1, (const char*)F("0.00G"));
    }
    strcat_P((char*)&msg_line2, (const char*)F("Press Up/Dn"));
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 6 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Restore Defaults"));
    strcat_P((char*)&msg_line2, (const char*)F("Press Up & Dn"));
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 7 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Save Cur. Setup"));
    strcat_P((char*)&msg_line2, (const char*)F("Press Up & Dn"));
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case 99 : {
    msg_line1[0] = 0; msg_line2[0] = 0;
    strcat_P((char*)&msg_line1, (const char*)F("Settings Stored!"));
    strcat_P((char*)&msg_line2, (const char*)F("Press < To Exit"));
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
    break;
  }
case MAX_SCREEN : {
    JB.JetiBox_P(ABOUT_1, ABOUT_2);
    break;
  }
  JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
}
