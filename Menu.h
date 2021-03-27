#ifndef MENU_H
#define MENU_H


struct Menu {
  /* This lets us save information about the menu navigation between
   * different menus.  This also automates a lot of the mundane and
   * often overlooked tasks when switching between menus.  */
  union {
    uint8_t d;
    struct {
      unsigned event:6;
      unsigned initialized:1;
      unsigned active:1;
    };
  } __attribute__((packed)) d;

  Menu()  { d.d = 0; }
  ~Menu() {}

  bool not_initialized() {
    bool result   = d.initialized;
    d.initialized = true;
    return !result; 
  }
  bool    is_active()        { return d.active; }
  void    activate()         { d.active = true; }
  void    jump_to(uint8_t e) { d.d = 0; d.event = e; }
  bool    back()             { d.d = 0; return true; }
  uint8_t e()                { return d.event; }
};


#endif
