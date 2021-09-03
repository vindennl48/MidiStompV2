// PRIVATE DEF
#define ENC_OFF 0
#define ENC_CW  1
#define ENC_CCW 2
// --

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
    this->data  = 0;

    BIT_INPUT_SETUP(*ddr_clk, *port_clk, pos_clk);
    BIT_INPUT_SETUP(*ddr_dt,  *port_dt,  pos_dt );

    // Set starting point for clk
    this->prev_clk = get_clk_state();

    // Set up button
    btn.setup(ddr_btn, pin_btn, port_btn, pos_btn);
  }

  void loop() {
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
  
  // Encoder functions
  bool is_left()       { return state == ENC_CCW ? true : false; }
  bool is_right()      { return state == ENC_CW  ? true : false; }
  bool get_clk_state() { return BIT_GET_VALUE(*pin_clk, pos_clk); }
  bool get_dt_state()  { return BIT_GET_VALUE(*pin_dt,  pos_dt ); }

  // Button functions
  bool is_pressed()      { return btn.is_pressed(); }
  bool is_long_pressed() { return btn.is_long_pressed(); }
  void set_press_type(uint8_t press_type) {
    btn.set_press_type(press_type);
  }
};

#undef ENC_OFF
#undef ENC_CW
#undef ENC_CCW
