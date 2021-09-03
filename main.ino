#include "Includes.h"

#ifndef ALT_PROGRAM

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    leds_set(200, 0, 255);
    print(0,0, "Hello");
    print_nline(0,0, "Hi");
  }
}

#endif
