#include "Includes.h"

#ifndef ALT_PROGRAM
#ifndef LOAD_EEPROM

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    print(0,1, "main");
  }
}

#endif
#endif
