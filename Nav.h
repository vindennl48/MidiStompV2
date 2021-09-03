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
  void    reinit()           { init = false; }
  uint8_t is_active()        { return active; }
  void    activate()         { init = false; active = true; }
  void    jump_to(uint8_t e) { data = 0; event = e; }
  uint8_t back()             { data = 0; return true; }
  uint8_t reset()            { return back(); }
  uint8_t e()                { return event; }
};
