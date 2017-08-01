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
        strcat_P((char*)&msg_line1, (const char*)F(" Set X to 0.0G"));
        if (gX < 0) {
            strcat_P((char*)&msg_line2, (const char*)F(" X:"));
            } else {
            strcat_P((char*)&msg_line2, (const char*)F(" X: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gX, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (const char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, xCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 2 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F(" Set Y to 0.0G"));
        if (gY < 0) {
            strcat_P((char*)&msg_line2, (const char*)F(" Y:"));
            } else {
            strcat_P((char*)&msg_line2, (const char*)F(" Y: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gY, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (const char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, yCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 3 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F(" Set Z to 1.0G"));
        if (gZ < 0) {
            strcat_P((char*)&msg_line2, (const char*)F(" Z:"));
            } else {
            strcat_P((char*)&msg_line2, (const char*)F(" Z: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, gZ, 1);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (const char*)F("G Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, zCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 4 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F("Set Pitch to 0\xB0"));
        if (aPitch < 0) {
            strcat_P((char*)&msg_line2, (const char*)F("Val:"));
            } else {
            strcat_P((char*)&msg_line2, (const char*)F("Val: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, aPitch, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (const char*)F("\xB0 Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, pCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 5 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F("Set Roll to 0\xB0"));
        if (aRoll < 0) {
            strcat_P((char*)&msg_line2, (const char*)F("Val:"));
            } else {
            strcat_P((char*)&msg_line2, (const char*)F("Val: "));
        }
        temp[0] = 0;
        floatToString((char*)&temp, aRoll, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        strcat_P((char*)&msg_line2, (const char*)F("\xB0 Cor:"));
        temp[0] = 0;
        floatToString((char*)&temp, rCalVal, 0);
        strcat((char*)&msg_line2, (char*)&temp);
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 6 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F("Save: Up and Dn"));
        strcat_P((char*)&msg_line2, (const char*)F("Back: <"));
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;
    }
    case 99 : {
        msg_line1[0] = 0; msg_line2[0] = 0;
        strcat_P((char*)&msg_line1, (const char*)F("Settings stored!"));
        strcat_P((char*)&msg_line2, (const char*)F("Press < to exit"));
        JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
        break;       
    }
    case MAX_SCREEN : {
        JB.JetiBox_P(ABOUT_1, ABOUT_2);
        break;
    }
    JB.JetiBox((char*)&msg_line1, (char*)&msg_line2);
}
