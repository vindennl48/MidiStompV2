#ifndef BUTTON_H
#define BUTTON_H

// PUBLIC DEF
#define PRESS_TYPE_UP    0  // Only activates when fsw is pressed THEN released
#define PRESS_TYPE_DOWN  1  // Activates as soon as fsw pressed down; Cannot use long-press

// PRIVATE DEF
#define LONG_PRESS_MS     500

#define STATE_SHORT_PRESS 1
#define STATE_LONG_PRESS  2
// --

// timer for btn long presses, for all btns
// idea here is only one btn at a time uses the timer
Timer btn_timer = 0;

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
      volatile uint8_t *ddr,
      volatile uint8_t *pin,
      volatile uint8_t *port,
      uint8_t          pos,
      uint8_t          press_type=PRESS_TYPE_UP )
  {
    this->pin        = pin;
    this->pos        = pos;
    this->data       = 0;
    this->press_type = press_type;
    BIT_INPUT_SETUP(*ddr, *port, pos);
  }

  void loop() {
    state = false;  // Reset state to prevent double-triggers

    if ( toggle ) {

      if ( !get_pin_state() ) {  // When button is finally released
        toggle  = false;
        is_down = false;

        // allow long_press and short_press only on up-stroke press_type
        if ( !press_type ) {
          if ( !reset ) state = STATE_SHORT_PRESS;   // short_press is triggered
          else          reset = false;               // long_press was triggered
        }
      }
      // only allow long_press on up-stroke press_type
      else if ( !press_type && !reset && btn_timer + LONG_PRESS_MS < millis() ) {
        state = STATE_LONG_PRESS;
        reset = true;
      }

    } else {
      if ( get_pin_state() ) {
        toggle  = true;
        is_down = true;

        // allow long_press on up-stroke press_type
        if ( !press_type ) {
          btn_timer = millis();  // Set timer
        } else {
          state = true;
        }
      }
    }
  }

  bool is_pressed() {
    return state == STATE_SHORT_PRESS ? true : false;
  }

  bool is_long_pressed() {
    return state == STATE_LONG_PRESS ? true : false;
  }

  void set_press_type(uint8_t press_type) {
    this->press_type = press_type > 1 ? PRESS_TYPE_UP : press_type;
  }

  bool get_pin_state() { return BIT_GET_VALUE(*pin, pos); }

};

// PRIVATE UNDEF
#undef LONG_PRESS_MS

#undef STATE_SHORT_PRESS
#undef STATE_LONG_PRESS
// --

#endif
