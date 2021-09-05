#ifndef LOAD_EEPROM
// Uncomment to use this program
#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

Footswitch fsw[NUM_FSW_PER_PRESET];

void setup() {
  hw_setup();

  // First thing we have to do is load up the preset address in parents
  SET_NEW_PARENT(M_PRESETS);
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    menu.setup(MENU_PRESET);
  }
  else {
    menu.loop();
  }
}

#endif
#endif
