#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "ShiftRegisterPWM.h"
#include "Components.h"

// PUBLIC DEFINES
#define DEFAULT_LED_TIME_MS 50
// --

struct Channel {
  static ShiftRegisterPWM shift_reg;

  uint8_t setpoint, actual, points, i_wait, i_wait_total;
  uint8_t pin, dim_setpoint, bright_setpoint;

  void    setup(uint8_t);
  void    loop();
  void    set(uint8_t);
  void    set(uint8_t, uint16_t);
  uint8_t get_value();
};

struct LED {
  Channel r, g, b;

  void setup(uint8_t, uint8_t, uint8_t);
  void loop();
  void set(Color);
  void set(Color, uint16_t);
  void set(uint8_t, uint8_t, uint8_t);
  void set(uint8_t, uint8_t, uint8_t, uint16_t);
};

#endif
