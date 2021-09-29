#include "Button.h"

#define LONG_PRESS_MS     500

#define STATE_SHORT_PRESS 1
#define STATE_LONG_PRESS  2

Timer btn_timer = 0;

void Button::setup(
  volatile uint8_t *ddr,
  volatile uint8_t *pin,
  volatile uint8_t *port,
  uint8_t          pos )
{
  setup(ddr, pin, port, pos, PRESS_TYPE_UP);
}

void Button::setup(
  volatile uint8_t *ddr,
  volatile uint8_t *pin,
  volatile uint8_t *port,
  uint8_t          pos,
  uint8_t          press_type )
{
  this->pin        = pin;
  this->pos        = pos;
  this->data       = 0;
  this->press_type = press_type;

  BIT_INPUT_SETUP(*ddr, *port, pos);
}
void Button::loop() {
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

uint8_t Button::is_pressed() {
  return state == STATE_SHORT_PRESS ? true : false; 
}
uint8_t Button::is_long_pressed() {
  return state == STATE_LONG_PRESS ? true : false;
}
void Button::set_press_type(uint8_t press_type) {
  this->press_type = press_type > 1 ? PRESS_TYPE_UP : press_type;
}
uint8_t Button::get_pin_state() { return BIT_GET_VALUE(*pin, pos); }
