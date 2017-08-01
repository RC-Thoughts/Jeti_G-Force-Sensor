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
