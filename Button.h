#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Standard.h"

// PUBLIC DEF
#define PRESS_TYPE_UP    0  // Only activates when fsw is pressed THEN released
#define PRESS_TYPE_DOWN  1  // Activates as soon as fsw pressed down; Cannot use long-press

// timer for btn long presses, for all btns
// idea here is only one btn at a time uses the timer
extern Timer btn_timer;

struct Button {
  volatile uint8_t *pin, pos;

  union {
    uint8_t data;
    struct {
      unsigned toggle:1;       // 0 off, 1 on
      unsigned state:2;        // 0 off, 1 is_pressed, 2 is_long_pressed
      unsigned reset:1;        // 0 no reset, 1 needs reset (long pressed)
      unsigned press_type:1;   // 0 on up-stroke, 1 on down-stroke
      unsigned is_down:1;      // used to find if 2 or more pedals are down
                               // at the same time
    };
  };

  void setup(
    volatile uint8_t*, volatile uint8_t*, volatile uint8_t*,
    uint8_t);
  void setup(
    volatile uint8_t*, volatile uint8_t*, volatile uint8_t*,
    uint8_t, uint8_t);

  void    loop();
  uint8_t is_pressed();
  uint8_t is_long_pressed();
  void    set_press_type(uint8_t);
  uint8_t get_pin_state();
};

#endif
