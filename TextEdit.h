// PRIVATE
#define E_SELECT_LETTER 0
#define E_EDIT_LETTER   1
// --

struct TextEdit {
  Nav     n;
  uint8_t cursor = 0;
  uint8_t letter = 0;

  void setup() {
    n.reset();
    cursor = 0;

    // Get text to edit
    eReadBlock( GET_ACTIVE_PARENT_NOT_OPTION, (uint8_t*)text[TXT_BUF_1], TEXT_SZ );

    PRINT_NLINE(0,1, F("SAVE      CANCEL"));
    lcd.cursor();  // Highlight
  }

  uint8_t loop() {
    switch( n.e() ) {
      default:
      case E_SELECT_LETTER:
        if ( n.not_init() ) {
          PRINT_NLINE(0,0, text[TXT_BUF_1]);
          lcd.setCursor(cursor, 0);
          lcd.blink();
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if ( knob.is_left() ) {
              cursor = CONTAIN((int)cursor-1, (int)0, (int)TEXT_SZ+1);
            }
            else if ( knob.is_right() ) {
              cursor = CONTAIN((int)cursor+1, (int)0, (int)TEXT_SZ+1);
            }

            if      ( cursor == TEXT_SZ-1 ) lcd.setCursor(     0, 1);
            else if ( cursor == TEXT_SZ )   lcd.setCursor(    10, 1);
            else                            lcd.setCursor(cursor, 0);
          }
          else if ( knob.is_pressed() ) {
            if ( cursor == TEXT_SZ-1 ) {
              // SAVE
              lcd.noCursor(); // noHighlight
              lcd.noBlink();
              eWriteBlock( GET_ACTIVE_PARENT_NOT_OPTION, (uint8_t*)text[TXT_BUF_1], TEXT_SZ );
              return n.back();
            }
            else if ( cursor == TEXT_SZ ) {
              // CANCEL
              lcd.noCursor(); // noHighlight
              lcd.noBlink();
              return n.back();
            }
            else {
              n.jump_to(E_EDIT_LETTER);
            }
          }
          else if ( knob.is_long_pressed() ) {
            // CANCEL
            lcd.noCursor(); // noHighlight
            lcd.noBlink();
            return n.back();
          }
          else if ( btns[0].is_down && btns[1].is_down ) {
            btns[0].is_down = false;
            btns[1].is_down = false;
            lcd.noCursor(); // noHighlight
            lcd.noBlink();
            eWriteBlock( GET_ACTIVE_PARENT_NOT_OPTION, (uint8_t*)text[TXT_BUF_1], TEXT_SZ );
            return n.back();
          }
          else if ( btns[1].is_down && btns[2].is_down ) {
            btns[1].is_down = false;
            btns[2].is_down = false;
            lcd.noCursor(); // noHighlight
            lcd.noBlink();
            return n.back();
          }
          else if ( btns[0].is_pressed() ) {
            //btns[0].is_down = false;
            text[TXT_BUF_1][cursor] = alphabet[0];
            lcd.print( alphabet[0] );
            lcd.setCursor(cursor, 0);
          }
          else if ( btns[1].is_pressed() ) {
            //btns[1].is_down = false;
            text[TXT_BUF_1][cursor] = alphabet[38];
            lcd.print( alphabet[38] );
            lcd.setCursor(cursor, 0);
          }
          else if ( btns[2].is_pressed() ) {
            //btns[2].is_down = false;
            text[TXT_BUF_1][cursor] = alphabet[27];
            lcd.print( alphabet[27] );
            lcd.setCursor(cursor, 0);
          }
        }
        break;

      case E_EDIT_LETTER:
        if ( n.not_init() ) {
          lcd.noBlink();
          set_letter();
          lcd.print( alphabet[letter] );
          lcd.setCursor(cursor, 0);
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if      ( knob.is_left() )  letter = CONTAIN((int)letter-1, (int)0, (int)ALPHABET_SZ-1);
            else if ( knob.is_right() ) letter = CONTAIN((int)letter+1, (int)0, (int)ALPHABET_SZ-1);
            lcd.print( alphabet[letter] );
            lcd.setCursor(cursor, 0);
          }
          else if ( knob.is_pressed() ) {
            text[TXT_BUF_1][cursor] = alphabet[letter];
            n.jump_to( E_SELECT_LETTER );
          }
          else if ( knob.is_long_pressed() ) {
            n.jump_to( E_SELECT_LETTER );
          }
        }
        break;
    };

    return false;
  }


  void set_letter() {
    for (int i=0; i<ALPHABET_SZ; i++) {
      if ( alphabet[i] == text[TXT_BUF_1][cursor] ) {
        letter = i;
        return;
      }
    }
    letter = 0;
  }

} text_edit;

#undef E_SELECT_LETTER
#undef E_EDIT_LETTER
