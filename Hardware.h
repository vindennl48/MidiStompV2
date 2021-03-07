#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include "Standard.h"
#include "Screen.h"
#include "Encoder.h"

#define LCD_ADDR     0x27
#define LCD_WIDTH    16
#define LCD_HEIGHT   2

struct HW {

  static Screen  screen;
  static Encoder knob;

  static void setup() {
    //Serial.begin(9600);  // Set up serial output

    LED_BOARD_SETUP;  // LED on the arduino board

    screen.setup(LCD_ADDR, LCD_WIDTH, LCD_HEIGHT);
    knob.setup(PIN_D5, PIN_D6, PIN_D7);
  }

  static void loop() {
    screen.loop();
    knob.loop();
  }

};

Screen  HW::screen;
Encoder HW::knob;

#undef LCD_ADDR
#undef LCD_WIDTH
#undef LCD_HEIGHT

#endif
