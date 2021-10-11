#ifndef HARDWARE_H
#define HARDWARE_H

#include "Button.h"
#include "Knob.h"
#include "Screen.h"
#include "LED.h"

#define TEXT_SZ   13
#define TXT_BUF_1 0
#define TXT_BUF_2 1
extern char buffer[2][TEXT_SZ];

#define NUM_BTNS 4
#define NUM_LEDS (NUM_BTNS)

struct HW {
  static Button btns[NUM_BTNS];
  static Knob   knob;
  static Screen screen;
  static LED    leds[NUM_LEDS];

  static void setup();
  static void loop();

  static void leds_set(Color);
  static void leds_set(Color, uint16_t);
  static void leds_set(uint8_t, uint8_t, uint8_t);
  static void leds_set(uint8_t, uint8_t, uint8_t, uint16_t);
};

#endif
