#ifndef VALUE_EDIT_H
#define VALUE_EDIT_H

#define E_MAIN       0
#define E_EDIT_VALUE 1

struct ValueEdit {
  Menu   m;
  String title;
  uint16_t value_old;
  uint16_t value, min, max, cursor;

  ValueEdit(uint16_t value_old, uint16_t min=0, uint16_t max=255, String title="VALUE") {
    this->title     = title;
    this->value_old = value_old;
    this->value     = value_old;
    this->min       = min;
    this->max       = max;
    this->cursor    = 0;

    HW::screen.print_with_nline(0,0, title + ": ");
    HW::screen.print_with_nline(0,1, "SAVE      CANCEL");
    HW::screen.print(13,0, "   ");
    HW::screen.print(13,0, value);
    HW::screen.highlight(true);
  }

  bool loop() {
    switch( m.e() ) {
      case E_MAIN:
        if ( m.not_initialized() ) {
          HW::screen.print(13,0, "   ");
          HW::screen.print(13,0, value);
          cursor = 0;
          HW::screen.blink(true);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  cursor = CONTAIN(cursor-1, 0, 2);
            else if ( HW::knob.is_right() ) cursor = CONTAIN(cursor+1, 0, 2);

            if      ( cursor == 0 ) HW::screen.set_cursor(13, 0);
            else if ( cursor == 1 ) HW::screen.set_cursor(0,  1);
            else if ( cursor == 2 ) HW::screen.set_cursor(10, 1);
          }
          else if ( HW::knob.is_pressed() ) {
            if ( cursor == 0 ) { // EDIT
              m.jump_to(E_EDIT_VALUE); 
            }
            else if ( cursor == 1 ) { // SAVE
              HW::screen.highlight(false);
              HW::screen.blink(false);
              m.back();
              return value;
            }
            else { // CANCEL
              HW::screen.highlight(false);
              HW::screen.blink(false);
              value = value_old;
              m.back();
              return value;
            }
          }
        }
        break;

      case E_EDIT_VALUE:
        if ( m.not_initialized() ) {
          HW::screen.blink(false);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  { value = CONTAIN(value-1, min, max); }
            else if ( HW::knob.is_right() ) { value = CONTAIN(value+1, min, max); }

            HW::screen.print(13,0, "   ");
            HW::screen.print(13,0, value);
          }
          else if ( HW::knob.is_pressed() ){
            m.jump_to(E_MAIN);
          }
          else if ( HW::knob.is_long_pressed() ){
            value = value_old;
            m.jump_to(E_MAIN);
          }
        }
        break;
    };

    return false;
  }

  uint16_t get_result() { return value; }

} *value_edit_p = nullptr;

#undef E_MAIN
#undef E_EDIT_VALUE

#endif
