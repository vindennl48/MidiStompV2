// Comment out to use main program
#define ALT_PROGRAM

#ifdef ALT_PROGRAM

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    leds_set(0,0,0);
    print(0,0, F("Alt Prg"));
  }
}

#endif
