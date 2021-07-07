#ifndef CHANNEL_H
#define CHANNEL_H

struct Channel {

  uint8_t          setpoint, actual, points, i_wait, i_wait_total = 0;
  uint8_t          pin, dim_setpoint, bright_setpoint             = 0;
  ShiftRegisterPWM *shift_reg;

  Channel(uint8_t pin, ShiftRegisterPWM *shift_reg) {
    this->pin       = pin;
    this->shift_reg = shift_reg;
  }

  void loop() {
    if (i_wait >= i_wait_total) {
      if      (setpoint >= actual + points) actual += points;
      else if (setpoint <= actual - points) actual -= points;
      else    actual = setpoint;

      i_wait = 0;

      shift_reg->set(pin, actual);
    }
    else {
      i_wait++;
    }
  }

  void set(uint8_t value, uint16_t time) {
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

  uint8_t get_value() { return actual; }

  void dim()    { set(dim_setpoint,    DEFAULT_LED_TIME_MS); }
  void bright() { set(bright_setpoint, DEFAULT_LED_TIME_MS); }

  void set_dim(uint8_t new_dim_setpoint)       { dim_setpoint = new_dim_setpoint; }
  void set_bright(uint8_t new_bright_setpoint) { bright_setpoint = new_bright_setpoint; }
};

#endif
