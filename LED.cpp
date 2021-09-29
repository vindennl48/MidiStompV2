#include <Arduino.h>
#include "ShiftRegisterPWM.h"
#include "LED.h"

#define NUM_SHIFT_REGISTERS  2
#define SHIFT_REG_RESOLUTION 100

/* :: CHANNEL :: */
ShiftRegisterPWM Channel::shift_reg(NUM_SHIFT_REGISTERS, SHIFT_REG_RESOLUTION);

void Channel::setup(uint8_t pin) {
  shift_reg.setup();

  setpoint = actual = points = i_wait = i_wait_total = 0;
  dim_setpoint = bright_setpoint = 0;

  this->pin = pin;
}

void Channel::loop() {
  if (i_wait >= i_wait_total) {
    if      (setpoint >= actual + points) actual += points;
    else if (setpoint <= actual - points) actual -= points;
    else    actual = setpoint;

    i_wait = 0;

    shift_reg.set(pin, actual);
  }
  else {
    i_wait++;
  }
}

void Channel::set(uint8_t value) { set(value, 50); }
void Channel::set(uint8_t value, uint16_t time) {
  uint8_t difference;

  setpoint = value;

  if ( value > actual ) { difference = value - actual; }
  else                  { difference = actual - value; }

  if ( difference > time ) {
    i_wait_total = 1;
    points       = (uint8_t)(difference/time);
  }
  else if ( time > difference ) {
    points       = 1;
    i_wait_total = (uint8_t)(time/difference);
  }
  else {
    points       = 1;
    i_wait_total = 1;
  }
}

uint8_t Channel::get_value() { return actual; }
/* :: END CHANNEL :: */



/* :: LED :: */
void LED::setup(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b) {
  r.setup(pin_r);
  g.setup(pin_g);
  b.setup(pin_b);
}

void LED::loop() {
  r.loop();
  g.loop();
  b.loop();
}

void LED::set(uint8_t r_new, uint8_t g_new, uint8_t b_new) {
  set(r_new, g_new, b_new, DEFAULT_LED_TIME_MS);
}
void LED::set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time) {
  r.set(r_new, time);
  g.set(g_new, time);
  b.set(b_new, time);
}
/* :: END LED :: */
