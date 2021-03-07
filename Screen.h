#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Standard.h"

#define X_MAX_SIZE 16
#define Y_MAX_SIZE 2

struct Screen {

  LiquidCrystal_I2C *lcd;

  void setup(uint8_t address, uint8_t width, uint8_t height) {
    lcd = new LiquidCrystal_I2C(address, width, height);

    lcd->init();
    lcd->clear();
    lcd->backlight();
  }

  void loop() {}

  // Print exact text at exact location
  void print(uint8_t x, uint8_t y, String text) {
    lcd->setCursor(x, y);
    lcd->print(text);
  }

  /*
   * x      = starting position on x axis
   * y      = starting position on y axis
   * text   = text to be printed at x,y position
   * length = size of 'text' plus padding
   * */
  void print_with_pad(uint8_t x, uint8_t y, String text, uint8_t length) {
    if ( text.length() > length ) return NULL;

    length -= text.length();
    print(x, y, text);
    for (int i=0; i<length; i++) lcd->print(' ');
  }

  // Print text then clear the rest of line with spaces
  void print_with_nline(uint8_t x, uint8_t y, String text) {
    uint8_t rest = X_MAX_SIZE;
    rest = rest - x - text.length();

    print(x, y, text);
    for (int i=0; i<rest; i++) lcd->print(' ');
  }

  void clear() { lcd->clear(); }

  void set_cursor(uint8_t x, uint8_t y) {
    lcd->setCursor(x, y);
  }

  void highlight(bool ans) {
    if ( ans ) { lcd->cursor();    }
    else       { lcd->noCursor(); }
  }

  void blink(bool ans) {
    if ( ans ) { lcd->blink();   }
    else       { lcd->noBlink(); }
  }
};

#endif
