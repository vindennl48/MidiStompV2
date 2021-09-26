// PRIVATE
#define MAX_CURSOR_LOCS   5
#define RED_POS           0
#define GREEN_POS         6
#define BLUE_POS         13
#define SAVE_POS          0
#define CANCEL_POS       10

#define E_SELECT_CHANNEL  0
#define E_EDIT_CHANNEL    1
// --


struct ColorEdit {
  Nav     n;
  uint8_t cursor = 0;
  uint8_t old_value;

  void setup() {
    this->cursor = 0;
    lcd.cursor();  // Highlight

    uint16_t active_parent_addr = GET_ACTIVE_PARENT_NOT_OPTION;
    leds_set(
      Color::get_red(active_parent_addr),
      Color::get_green(active_parent_addr),
      Color::get_blue(active_parent_addr)
    );

    PRINT_NLINE(RED_POS,   0, leds[0].r.setpoint);
    PRINT      (GREEN_POS, 0, leds[0].g.setpoint);
    PRINT      (BLUE_POS,  0, leds[0].b.setpoint);
    PRINT(0,1, "SAVE      CANCEL");
  }

  bool loop() {
    switch ( n.e() ) {
      case E_SELECT_CHANNEL:
        if ( n.not_init() ) {
          if      ( cursor == 0 ) lcd.setCursor(RED_POS,    0);
          else if ( cursor == 1 ) lcd.setCursor(GREEN_POS,  0);
          else if ( cursor == 2 ) lcd.setCursor(BLUE_POS,   0);
          else if ( cursor == 3 ) lcd.setCursor(SAVE_POS,   1);
          else if ( cursor == 4 ) lcd.setCursor(CANCEL_POS, 1);
          lcd.blink();
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if      ( knob.is_left() )  cursor = CONTAIN((int)cursor-1, (int)0, (int)MAX_CURSOR_LOCS);
            else if ( knob.is_right() ) cursor = CONTAIN((int)cursor+1, (int)0, (int)MAX_CURSOR_LOCS);
            n.reinit();
          }
          else if ( knob.is_pressed() ) {
            if ( cursor < 3 ) {
              n.jump_to( E_EDIT_CHANNEL );
            }
            else {
              lcd.noCursor();  // no Highlight
              lcd.noBlink();

              if ( cursor == 3 ) { // SAVE
                uint16_t active_parent_addr = GET_ACTIVE_PARENT_NOT_OPTION;
                Color::set_red  (active_parent_addr, leds[0].r.setpoint);
                Color::set_green(active_parent_addr, leds[0].g.setpoint);
                Color::set_blue (active_parent_addr, leds[0].b.setpoint);
              }
              // else cancel

              return true;
            }
          }
        }
        break;

      case E_EDIT_CHANNEL:
        if ( n.not_init() ) {
          lcd.noBlink();
          switch(cursor) {
            case 0:  // RED
              old_value = leds[0].r.setpoint;
              break;
            case 1:  // GREEN
              old_value = leds[0].g.setpoint;
              break;
            case 2:  // BLUE
              old_value = leds[0].r.setpoint;
              break;
          };
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if ( knob.is_left() )  {
              switch(cursor) {
                case 0:  // RED
                  leds_set_red(ROTATE((int)leds[0].r.setpoint-1, (int)0, (int)256));
                  break;
                case 1:  // GREEN
                  leds_set_green(ROTATE((int)leds[0].g.setpoint-1, (int)0, (int)256));
                  break;
                case 2:  // BLUE
                  leds_set_blue(ROTATE((int)leds[0].b.setpoint-1, (int)0, (int)256));
                  break;
              };
            }
            else if ( knob.is_right() ) {
              switch(cursor) {
                case 0:  // RED
                  leds_set_red(ROTATE((int)leds[0].r.setpoint+20, (int)0, (int)256));
                  break;
                case 1:  // GREEN
                  leds_set_green(ROTATE((int)leds[0].g.setpoint+20, (int)0, (int)256));
                  break;
                case 2:  // BLUE
                  leds_set_blue(ROTATE((int)leds[0].b.setpoint+20, (int)0, (int)256));
                  break;
              };
            }
            switch(cursor) {
              case 0:
                PRINT(RED_POS, 0, "   ");
                PRINT(RED_POS, 0, leds[0].r.setpoint);
                break;
              case 1:
                PRINT(GREEN_POS, 0, "   ");
                PRINT(GREEN_POS, 0, leds[0].g.setpoint);
                break;
              case 2:
                PRINT(BLUE_POS, 0, "   ");
                PRINT(BLUE_POS, 0, leds[0].b.setpoint);
                break;
            };
          }
          else if ( knob.is_pressed() ) {
            n.jump_to( E_SELECT_CHANNEL );
          }
          else if ( knob.is_long_pressed() ) {
            switch(cursor) {
              case 0:  // RED
                leds_set_red(old_value);
                break;
              case 1:  // GREEN
                leds_set_green(old_value);
                break;
              case 2:  // BLUE
                leds_set_blue(old_value);
                break;
            };
            n.jump_to( E_SELECT_CHANNEL );
          }
        }
        break;
    };

    return false;
  }

} color_edit;

#undef MAX_CURSOR_LOCS
#undef RED_POS
#undef GREEN_POS
#undef BLUE_POS
#undef SAVE_POS
#undef CANCEL_POS

#undef E_SELECT_CHANNEL
#undef E_EDIT_CHANNEL
