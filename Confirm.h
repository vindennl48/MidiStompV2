

struct Confirm {
  /* This is a yes/no confirmation screen that returns 1 for no, 2 for yes.
   * 0 is for maintaining the loop. */
  Nav     n;
  uint8_t cursor = 1;

  void setup() {
    PRINT_NLINE(0,0, "ARE YOU SURE?");
    PRINT_NLINE(0,1, "YES           NO");
    lcd.cursor();  // Highlight
    lcd.blink();
  }

  uint8_t loop() {
    if ( n.not_init() ) {
      if      ( cursor == 0 ) lcd.setCursor(0,  1);
      else if ( cursor == 1 ) lcd.setCursor(14, 1);
    }
    else {
      if ( knob.is_left() ) {
        if ( cursor != 0 ) {
          cursor = 0;
          n.reinit(); 
        }
      }
      else if ( knob.is_right() )   {
        if ( cursor != 1 ) {
          cursor = 1; 
          n.reinit(); 
        }
      }
      else if ( knob.is_pressed() ) {
        if      ( cursor == 0 ) {
          lcd.noCursor();  // Highlight
          lcd.noBlink();
          return LTRUE; 
        }
        else if ( cursor == 1 ) { return LFALSE; }
      }
    }
    return false;
  }
} confirm;
