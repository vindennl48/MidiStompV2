#ifndef KNOB_H
#define KNOB_H

#include "Button.h"

struct Knob {
  volatile uint8_t *pin_clk, pos_clk,
                   *pin_dt,  pos_dt;

  Button btn;

  union {
    uint8_t data;
    struct {
      unsigned current_clk:1;   // true / false
      unsigned prev_clk:1;      // true / false
      unsigned state:2;         // 0 off, 1 CW, 2 CCW
    };
  };

  void setup(
    volatile uint8_t*, volatile uint8_t*, volatile uint8_t*, uint8_t,
    volatile uint8_t*, volatile uint8_t*, volatile uint8_t*, uint8_t,
    volatile uint8_t*, volatile uint8_t*, volatile uint8_t*, uint8_t);

  void loop();
  
  // Encoder functions
  uint8_t is_left();
  uint8_t is_right();
  uint8_t get_clk_state();
  uint8_t get_dt_state();

  // Button functions
  uint8_t is_pressed();
  uint8_t is_long_pressed();
  void    set_press_type(uint8_t);
};

#endif
