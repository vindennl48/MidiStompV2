#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <Arduino.h>
#include "Standard.h"
#include "Hardware.h"

// Definitions
#define ALPHABET_SIZE   38
#define TEXT_SIZE       16
#define E_SELECT_LETTER 0
#define E_EDIT_LETTER   1

struct TextEdit {
  // Chars that can be used
  static const String alphabet;

  static String  text;
  static String  text_orig;
  static uint8_t cursor;
  static uint8_t letter;
  static uint8_t event;
  static bool    initialized;

  static void setup(String in_text) {
    if ( in_text.length() != TEXT_SIZE ) {
      uint8_t rest = TEXT_SIZE-in_text.length();
      for (int i=0; i<rest; i++) in_text = in_text + ' ';
    }

    initialized = false;
    text        = in_text;
    text_orig   = in_text;
    cursor      = 0;
    letter      = 0;
    event       = 0;

    HW::screen.clear();
    HW::screen.print(0,1,"SAVE      CANCEL");
    HW::screen.highlight(true);
  }

  static bool loop() {
    switch(event) {
      case E_SELECT_LETTER:
        if ( !initialized ) {
          initialized = true;
          HW::screen.print(0,0,text);
          HW::screen.set_cursor(cursor,0);
          HW::screen.blink(true);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {

            if ( HW::knob.is_left() ) {
              if ( cursor > 0 ) { cursor--; }
            }
            else if ( HW::knob.is_right() ) {
              // +1 is for save and cancel options
              if ( cursor < TEXT_SIZE+1 ) { cursor++; }
            }

            // save option
            if ( cursor == TEXT_SIZE ) {
              HW::screen.set_cursor(0,1);
            }
            // cancel option
            else if ( cursor == TEXT_SIZE+1 ) {
              HW::screen.set_cursor(10,1);
            }
            else {
              HW::screen.set_cursor(cursor,0);
            }
          }

          else if ( HW::knob.is_pressed() ) {
            if ( cursor < TEXT_SIZE ) {
              event       = E_EDIT_LETTER;
              initialized = false;
            }
            else if ( cursor == TEXT_SIZE ) {
              // Clean up
              HW::screen.highlight(false);
              HW::screen.blink(false);
              // Save
              return true;
            }
            else {
              // Cancel
              text = text_orig;
              return true;
            }
          }
        }

        break;
      case E_EDIT_LETTER:
        if ( !initialized ) {
          initialized = true;
          HW::screen.blink(false);
          set_letter();
          HW::screen.lcd->print(alphabet[letter]);
          HW::screen.set_cursor(cursor,0);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if ( HW::knob.is_left() ) {
              if ( letter > 0 ) { letter--; }
            }
            else if ( HW::knob.is_right() ) {
              if ( letter+1 < ALPHABET_SIZE ) { letter++; }
            }

            HW::screen.lcd->print(alphabet[letter]);
            HW::screen.set_cursor(cursor,0);
          }
          else if ( HW::knob.is_pressed() ) {
            // Undo changing letter
            event       = E_SELECT_LETTER;
            initialized = false;
            text.setCharAt(cursor, alphabet[letter]);
          }
          else if ( HW::knob.is_long_pressed() ) {
            // Undo changing letter
            event       = E_SELECT_LETTER;
            initialized = false;
            HW::screen.lcd->print(text[cursor]);
            HW::screen.set_cursor(cursor,0);
          }
        }
        break;
    };

    return false;
  }

  static void set_letter() {
    for (int i=0; i<ALPHABET_SIZE; i++) {
      if ( alphabet[i] == text[cursor] ) {
        letter = i;
        return;
      }
    }
    letter = 0;
  }

  static String get_text() {
    return text;
  }
};

const String TextEdit::alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789-_";

String  TextEdit::text          = "";
String  TextEdit::text_orig     = "";
uint8_t TextEdit::cursor        = 0;
uint8_t TextEdit::letter        = 0;
uint8_t TextEdit::event         = 0;
bool    TextEdit::initialized   = false;

#undef ALPHABET_SIZE

#endif
