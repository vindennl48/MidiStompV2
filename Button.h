#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Standard.h"

#define LONG_PRESS_MS     500

#define STATE_SHORT_PRESS 1
#define STATE_LONG_PRESS  2

#define PRESS_TYPE_UP     0
#define PRESS_TYPE_DOWN   1

struct Button {
  unsigned long    timer;
  volatile uint8_t *pin, pos;

  struct Flags {
    union {
      uint8_t data;
      struct {
        unsigned toggle:1;       // 0 off, 1 on
        unsigned state:2;        // 0 off, 1 is_pressed, 2 is_long_pressed
        unsigned reset:1;        // 0 no reset, 1 needs reset (long pressed)
        unsigned press_type:1;   // 0 on up-stroke, 1 on down-stroke
      };
    };
  } __attribute__((packed)) f;

  void setup(
      volatile uint8_t *ddr,
      volatile uint8_t *pin,
      volatile uint8_t *port,
      uint8_t          pos,
      uint8_t          press_type )
  {
    setup(ddr, pin, port, pos);
    set_press_type(press_type);
  }

  void setup(
      volatile uint8_t *ddr,
      volatile uint8_t *pin,
      volatile uint8_t *port,
      uint8_t          pos )
  {
    this->pin    = pin;
    this->pos    = pos;
    this->f.data = 0;
    BIT_INPUT_SETUP(*ddr, *port, pos);
  }

  void loop() {
    f.state = false;  // Reset state to prevent double-triggers

    if ( f.toggle ) {

      if ( !get_pin_state() ) {  // When button is finally released
        f.toggle = false;

        // allow long_press and short_press only on up-stroke press_type
        if ( !f.press_type ) {
          if ( !f.reset ) f.state = STATE_SHORT_PRESS;   // short_press is triggered
          else            f.reset = false;               // long_press was triggered
        }
      }
      // only allow long_press on up-stroke press_type
      else if ( !f.press_type && !f.reset && timer + LONG_PRESS_MS < millis() ) {
        f.state = STATE_LONG_PRESS;
        f.reset = true;
      }

    } else {
      if ( get_pin_state() ) {
        f.toggle = true;

        // allow long_press on up-stroke press_type
        if ( !f.press_type ) {
          timer = millis();  // Set timer
        } else {
          f.state = true;
        }
      }
    }
  }

  bool is_pressed() {
    if ( f.state == STATE_SHORT_PRESS ) return true;
    return false;
  }

  bool is_long_pressed() {
    if ( f.state == STATE_LONG_PRESS ) return true;
    return false;
  }

  void set_press_type(uint8_t press_type) {
    if ( press_type == PRESS_TYPE_UP || press_type == PRESS_TYPE_DOWN )
      f.press_type = press_type;
  }

  bool get_pin_state() { return BIT_GET_VALUE(*pin, pos); }

};

#undef LONG_PRESS_MS

#undef STATE_SHORT_PRESS
#undef STATE_LONG_PRESS

#endif
