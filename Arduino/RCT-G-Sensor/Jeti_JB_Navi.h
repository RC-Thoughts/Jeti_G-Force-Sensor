//
// Jetibox navigation and button actions
//

// Button codes
// 224  RIGHT
// 112  LEFT
// 208  UP
// 176  DOWN
// 144  UP & DOWN
// 9    LEFT & RIGHT
//
int read = delayTR (GETCHAR_TIMEOUT_ms);
if ( (read != 240 ) && (read != 0) )
{
  switch (read)
  {
    case 224 : // RIGHT
      if (current_screen != MAX_SCREEN)
      {
        current_screen++;
        if (current_screen == 8) {
          current_screen = 0;
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
        if (FilterOnOff == 1) {
          FilterOnOff = 0;
        }
        else {
          FilterOnOff ++;
        }
      }
      if (current_screen == 5) {
        if (Ndec == 2) {
          Ndec = 1;
        }
        else {
          Ndec++;
        }
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
        if (FilterOnOff == 0) {
          FilterOnOff = 1;
        }
        else {
          FilterOnOff --;
        }
      }
      if (current_screen == 5) {
        if (Ndec == 1) {
          Ndec = 2;
        }
        else {
          Ndec--;
        }
      }
      if (current_screen == 6) {
        // Store default values to eeprom
        xCalVal = 0;
        yCalVal = 0;
        zCalVal = 0;
        FilterOnOff = 0;
        Ndec = 1;
        EEPROM.write(0, xCalVal);
        EEPROM.write(1, yCalVal);
        EEPROM.write(2, zCalVal);
        EEPROM.write(3, FilterOnOff);
        EEPROM.write(4, Ndec);
        current_screen == 99;
        delay(1000);
        resetFunc();
      }
      if (current_screen == 7) {
        // Store setup values to eeprom
        EEPROM.write(0, xCalVal);
        EEPROM.write(1, yCalVal);
        EEPROM.write(2, zCalVal);
        EEPROM.write(3, FilterOnOff);
        EEPROM.write(4, Ndec);
        current_screen == 99;
        delay(1000);
        resetFunc();
      }
      break;
    case 144 : // UP+DOWN
      break;
    case 96 : // LEFT+RIGHT
      break;
  }
}
