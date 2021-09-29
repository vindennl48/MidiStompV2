#include "Knob.h"

#define ENC_OFF 0
#define ENC_CW  1
#define ENC_CCW 2


void Knob::setup(
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
  this->pin_clk = pin_clk;
  this->pos_clk = pos_clk;
  this->pin_dt  = pin_dt;
  this->pos_dt  = pos_dt;
  this->data  = 0;

  BIT_INPUT_SETUP(*ddr_clk, *port_clk, pos_clk);
  BIT_INPUT_SETUP(*ddr_dt,  *port_dt,  pos_dt );

  // Set starting point for clk
  this->prev_clk = get_clk_state();

  // Set up button
  btn.setup(ddr_btn, pin_btn, port_btn, pos_btn);
}

void Knob::loop() {
  btn.loop();

  // reset state and get current state
  state       = ENC_OFF;
  current_clk = get_clk_state();

  // If these are different, a pulse has occurred
  if ( current_clk != prev_clk ) {

    // only activate if current_clk is high
    if ( current_clk ) {

      // If these are different, encoder went counter-clockwise
      if ( get_dt_state() != current_clk ) {
        state = ENC_CCW;
      } else {
        state = ENC_CW;
      }

    }

    prev_clk = current_clk;

  }
}

uint8_t Knob::is_left()       { return state == ENC_CCW ? true : false; }
uint8_t Knob::is_right()      { return state == ENC_CW  ? true : false; }
uint8_t Knob::get_clk_state() { return BIT_GET_VALUE(*pin_clk, pos_clk); }
uint8_t Knob::get_dt_state()  { return BIT_GET_VALUE(*pin_dt,  pos_dt ); }

uint8_t Knob::is_pressed()      { return btn.is_pressed(); }
uint8_t Knob::is_long_pressed() { return btn.is_long_pressed(); }
void Knob::set_press_type(uint8_t press_type) {
  btn.set_press_type(press_type);
}
