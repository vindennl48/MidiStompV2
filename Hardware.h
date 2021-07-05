#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include "Standard.h"
#include "Screen.h"
#include "Encoder.h"
#include "LEDs.h"
#include "Buttons.h"

#define LCD_ADDR     0x27
#define LCD_WIDTH    16
#define LCD_HEIGHT   2

struct HW {

  static Screen  screen;
  static Encoder knob;
  static LEDs    leds;
  static Buttons btns;

  static void setup() {
    //Serial.begin(9600);  // Set up serial output

    LED_BOARD_SETUP;  // LED on the arduino board

    screen.setup(LCD_ADDR, LCD_WIDTH, LCD_HEIGHT);
    knob.setup(PIN_D2, PIN_D3, PIN_D4);
    leds.setup();
    btns.setup();

    leds.at(0)->set_dim(10,0,0);
    leds.at(0)->set_bright(255,0,0);
    leds.at(0)->bright();

    leds.at(1)->set_dim(0,10,0);
    leds.at(1)->set_bright(0,255,0);
    leds.at(1)->bright();

    leds.at(2)->set_dim(0,0,10);
    leds.at(2)->set_bright(0,0,255);
    leds.at(2)->bright();

    leds.at(3)->set_dim(10,0,10);
    leds.at(3)->set_bright(255,0,255);
    leds.at(3)->bright();
  }

  static void loop() {
    screen.loop();
    knob.loop();
    leds.loop();
    btns.loop();
  }

};

Screen  HW::screen;
Encoder HW::knob;
LEDs    HW::leds;
Buttons HW::btns;

#undef LCD_ADDR
#undef LCD_WIDTH
#undef LCD_HEIGHT

#endif
