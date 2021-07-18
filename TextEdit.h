#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#define ALPHABET_SIZE 38

#define E_SELECT_LETTER 0
#define E_EDIT_LETTER   1

struct TextEdit {
  Menu    m;
  char    *text_old;
  char    text_new[STR_LEN_MAX] = " ";
  uint8_t cursor                = 0;
  uint8_t letter                = 0;

  TextEdit( char in_text[STR_LEN_MAX] ) { setup(in_text); }

  void setup( char in_text[STR_LEN_MAX] ) {
    text_old = in_text;
    memcpy(text_new, in_text, STR_LEN_MAX);
    cursor  = 0;
    letter  = 0;

    HW::screen.clear();
    HW::screen.print(0,1, "SAVE      CANCEL");
    HW::screen.highlight(true);
  }

  bool loop() {
    switch( m.e() ) {
      default:
      case E_SELECT_LETTER:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0, text_new);
          HW::screen.set_cursor(cursor, 0);
          HW::screen.blink(true);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  cursor = CONTAIN(cursor-1, 0, STR_LEN+1);
            else if ( HW::knob.is_right() ) cursor = CONTAIN(cursor+1, 0, STR_LEN+1);

            if      ( cursor == STR_LEN )   HW::screen.set_cursor(0, 1);
            else if ( cursor == STR_LEN+1 ) HW::screen.set_cursor(10, 1);
            else    HW::screen.set_cursor(cursor, 0);
          }
          else if ( HW::knob.is_pressed() ) {
            if      ( cursor < STR_LEN )  {
              m.jump_to( E_EDIT_LETTER ); 
            }
            else if ( cursor == STR_LEN ) {  // SAVE
              HW::screen.highlight(false);
              HW::screen.blink(false);
              memcpy(text_old, text_new, STR_LEN_MAX);
              return m.back();
            }
            else { // CANCEL
              return m.back();
            }
          }
        }
        break;
      case E_EDIT_LETTER:
        if ( m.not_initialized() ) {
          HW::screen.blink(false);
          set_letter();
          HW::screen.lcd->print( DB::letter_at(letter) );
          HW::screen.set_cursor(cursor, 0);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  letter = CONTAIN(letter-1, 0, ALPHABET_SIZE-1);
            else if ( HW::knob.is_right() ) letter = CONTAIN(letter+1, 0, ALPHABET_SIZE-1);
            HW::screen.lcd->print( DB::letter_at(letter) );
            HW::screen.set_cursor(cursor,0);
          }
          else if ( HW::knob.is_pressed() ) {
            // Change Letter
            text_new[cursor] = DB::letter_at(letter);
            m.jump_to( E_SELECT_LETTER );
          }
          else if ( HW::knob.is_long_pressed() ) {
            // Undo changing letter
            HW::screen.lcd->print( text_new[cursor] );
            HW::screen.set_cursor(cursor,0);
            m.jump_to( E_SELECT_LETTER );
          }
        }
        break;
    };

    return false;
  }


  void set_letter() {
    for (int i=0; i<ALPHABET_SIZE; i++) {
      if ( DB::letter_at(i) == text_new[cursor] ) {
        letter = i;
        return;
      }
    }
    letter = 0;
  }

} *text_edit_p = nullptr;

#undef E_SELECT_LETTER
#undef E_EDIT_LETTER

#endif
