#ifndef LOAD_EEPROM
// Uncomment to use this program
//#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    DEBUG("get_type: ", Feature::get_type(912));
  }
  else {
  }
}

#endif
#endif
