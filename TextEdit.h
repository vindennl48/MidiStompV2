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

  bool loop() {
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
              cursor = CONTAIN(cursor-1, 0, TEXT_SZ+1);
            }
            else if ( knob.is_right() ) {
              cursor = CONTAIN(cursor+1, 0, TEXT_SZ+1);
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
            if      ( knob.is_left() )  letter = CONTAIN(letter-1, 0, ALPHABET_SZ);
            else if ( knob.is_right() ) letter = CONTAIN(letter+1, 0, ALPHABET_SZ);
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
