#ifndef Screen_H
#define Screen_H

#include <LiquidCrystal_I2C.h>
#include "Standard.h"

#define SCREEN_ADDR   0x27
#define SCREEN_WIDTH  16
#define SCREEN_HEIGHT 2

struct Screen {
  static LiquidCrystal_I2C lcd;
  static Timer             lcd_timer;

  static void setup();
  static void loop();
  static void print(uint8_t, uint8_t, String);
  static void print_nline(uint8_t, uint8_t, String);
  static void flash();
};

#endif
