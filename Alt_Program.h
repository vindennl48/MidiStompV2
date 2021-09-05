#ifndef LOAD_EEPROM
// Uncomment to use this program
#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

Footswitch fsw[NUM_FSW_PER_PRESET];

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    print_nline(0,0,"Hi");
  }
}

#endif
#endif
