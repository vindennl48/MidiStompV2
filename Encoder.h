#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "Standard.h"
#include "Button.h"

#define ENC_OFF 0
#define ENC_CW  1
#define ENC_CCW 2

struct Encoder {
  volatile uint8_t *pin_clk, pos_clk,
                   *pin_dt,  pos_dt;

  Button button;

  struct Flags {
    union {
      uint8_t data;
      struct {
        unsigned current_clk:1;   // true / false
        unsigned prev_clk:1;      // true / false
        unsigned state:2;         // 0 off, 1 CW, 2 CCW
      };
    };
  } f;

  // example: encoder.setup(PIN_D5, PIN_D6, PIN_D7);
  void setup(
      volatile uint8_t *ddr_clk,
      volatile uint8_t *pin_clk,
      volatile uint8_t *port_clk,
      uint8_t          pos_clk,

      volatile uint8_t *ddr_dt,
      volatile uint8_t *pin_dt,
      volatile uint8_t *port_dt,
      uint8_t          pos_dt,

      volatile uint8_t *ddr_btn,
      volatile uint8_t *pin_btn,
      volatile uint8_t *port_btn,
      uint8_t          pos_btn )
  {
    // Set up encoder
    this->pin_clk = pin_clk;
    this->pos_clk = pos_clk;
    this->pin_dt  = pin_dt;
    this->pos_dt  = pos_dt;
    this->f.data  = 0;

    BIT_INPUT_SETUP(*ddr_clk, *port_clk, pos_clk);
    BIT_INPUT_SETUP(*ddr_dt,  *port_dt,  pos_dt );

    // Set starting point for clk
    this->f.prev_clk = get_clk_state();

    // Set up button
    button.setup(ddr_btn, pin_btn, port_btn, pos_btn);
  }

  void loop() {
    button.loop();

    // reset state and get current state
    f.state       = ENC_OFF;
    f.current_clk = get_clk_state();

    // If these are different, a pulse has occurred
    if ( f.current_clk != f.prev_clk ) {

      // only activate if current_clk is high
      if ( f.current_clk ) {

        // If these are different, encoder went counter-clockwise
        if ( get_dt_state() != f.current_clk ) {
          f.state = ENC_CCW;
        } else {
          f.state = ENC_CW;
        }

      }

      f.prev_clk = f.current_clk;

    }
  }
  
  // Encoder functions
  bool is_left()       { if ( f.state == ENC_CCW ) return true; return false; }
  bool is_right()      { if ( f.state == ENC_CW  ) return true; return false; }
  bool get_clk_state() { return BIT_GET_VALUE(*pin_clk, pos_clk); }
  bool get_dt_state()  { return BIT_GET_VALUE(*pin_dt,  pos_dt ); }

  // Button functions
  bool is_pressed()      { return button.is_pressed(); }
  bool is_long_pressed() { return button.is_long_pressed(); }
  void set_press_type(uint8_t press_type) {
    button.set_press_type(press_type);
  }
};

#undef ENC_OFF
#undef ENC_CW
#undef ENC_CCW

#endif
