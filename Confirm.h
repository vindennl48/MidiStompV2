#ifndef CONFIRM_H
#define CONFIRM_H

struct Confirm {
  /* This is a yes/no confirmation screen that returns 1 for no, 2 for yes.
   * 0 is for maintaining the loop. */
  Menu    m;
  uint8_t cursor = 1;

  Confirm() {
    HW::screen.print_with_nline(0,0, "ARE YOU SURE?");
    HW::screen.print_with_nline(0,1, "YES           NO");
    HW::screen.highlight(true);
    HW::screen.blink(true);
    HW::leds.set(0,0,0);
  }

  uint8_t loop() {
    if ( m.not_initialized() ) {
      if      ( cursor == 0 ) HW::screen.set_cursor(0,  1);
      else if ( cursor == 1 ) HW::screen.set_cursor(14, 1);
    }
    else {
      if ( HW::knob.is_left() ) {
        if ( cursor != 0 ) {
          cursor = 0;
          m.reinitialize(); 
        }
      }
      else if ( HW::knob.is_right() )   {
        if ( cursor != 1 ) {
          cursor = 1; 
          m.reinitialize(); 
        }
      }
      else if ( HW::knob.is_pressed() ) {
        if      ( cursor == 0 ) {
          HW::screen.highlight(false);
          HW::screen.blink(false);
          return LTRUE; 
        }
        else if ( cursor == 1 ) { return LFALSE; }
      }
    }
    return false;
  }
} *confirm_p = nullptr;

#endif
