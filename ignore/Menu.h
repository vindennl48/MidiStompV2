#ifndef MENU_H
#define MENU_H


struct Menu {
  /* This lets us save information about the menu navigation between
   * different menus.  This also automates a lot of the mundane and
   * often overlooked tasks when switching between menus.  */
  union {
    uint16_t d;
    struct {
      unsigned event:8;
      unsigned initialized:1;
      unsigned active:1;
    };
  };

  Menu()  { d = 0; }
  ~Menu() {}

  bool not_initialized() {
    bool result = initialized;
    initialized = true;
    return !result; 
  }
  void    reinitialize()     { initialized = false; }
  bool    is_active()        { return active; }
  void    activate()         { initialized = false; active = true; }
  void    jump_to(uint8_t e) { d = 0; event = e; }
  bool    back()             { d = 0; return true; }
  uint8_t e()                { return event; }
};



#endif
