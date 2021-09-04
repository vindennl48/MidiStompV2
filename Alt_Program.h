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
    PRINT_NLINE(0,0, PresetParam::get_feature(1));
    PRINT_NLINE(0,1, PresetParam::get_velocity(1));
  }
}

#endif
#endif
