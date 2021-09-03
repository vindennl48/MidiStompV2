#include "Includes.h"

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    leds_set(255,0,0);
  }
  else {
  }
}
