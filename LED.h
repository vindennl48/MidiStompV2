// PUBLIC DEFINES
#define DEFAULT_LED_TIME_MS 50
// --

struct Channel {
  uint8_t setpoint, actual, points, i_wait, i_wait_total;
  uint8_t pin, dim_setpoint, bright_setpoint;
  ShiftRegisterPWM *shift_reg;

  void setup(uint8_t pin, ShiftRegisterPWM *shift_reg) {
    setpoint = actual = points = i_wait = i_wait_total = 0;
    dim_setpoint = bright_setpoint = 0;

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
};

struct LED {
  Channel r, g, b;

  void setup(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, ShiftRegisterPWM *shift_reg) {
    r.setup(pin_r, shift_reg);
    g.setup(pin_g, shift_reg);
    b.setup(pin_b, shift_reg);
  }

  void loop() {
    r.loop();
    g.loop();
    b.loop();
  }

  void set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time = DEFAULT_LED_TIME_MS) {
    r.set(r_new, time);
    g.set(g_new, time);
    b.set(b_new, time);
  }
};
