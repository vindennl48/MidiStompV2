struct Nav {
  union {
    uint16_t data;
    struct {
      unsigned event:8;
      unsigned init:1;
      unsigned active:1;
    };
  };

  Nav() { data = 0; }

  uint8_t not_init() {
    uint8_t result = init;
    init           = true;
    return !result; 
  }
  void    reinit()           { serial_thru(); init = false; }
  uint8_t is_active()        { serial_thru(); return active; }
  void    activate()         { serial_thru(); init = false; active = true; }
  void    jump_to(uint8_t e) { serial_thru(); data = 0; event = e; }
  uint8_t back()             { serial_thru(); data = 0; return true; }
  uint8_t reset()            { serial_thru(); return back(); }
  uint8_t e()                { serial_thru(); return event; }

  // This is the best place to put this, it will be triggered multiple times
  // during a program loop.  This should be fast enough to catch all midi clock
  // data coming thru
  void serial_thru() {
    // Might want to set a setting to stop thruput in the future
    if (Serial.available() > 0) Serial.write(Serial.read());
  }
};
