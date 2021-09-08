#ifndef LOAD_EEPROM
// Uncomment to use this program
//#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

void setup() {
  hw_setup();

  SET_NEW_PARENT(M_PRESETS);
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    menu.setup(MENU_PRESET);
  }
  else {
    switch(n.e()) {
      case 0:
        if ( menu.loop() ) n.jump_to(1);
        break;

      case 1:
        PRINT_NLINE(0,0, "FINISHED");
        PRINT_NLINE(0,1, " ");
        break;
    };
  }
}

#endif
#endif
