#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include "Standard.h"
#include "Screen.h"

#define LCD_ADDR     0x27
#define LCD_WIDTH    16
#define LCD_HEIGHT   2

struct HW {

  static Screen screen;

  static void setup() {
    //Serial.begin(9600);  // Set up serial output

    LED_BOARD_SETUP;

    screen.setup(LCD_ADDR, LCD_WIDTH, LCD_HEIGHT);
  }

  static void loop() {
    screen.loop();
  }

};

Screen HW::screen;

#undef LCD_ADDR
#undef LCD_WIDTH
#undef LCD_HEIGHT

#endif
