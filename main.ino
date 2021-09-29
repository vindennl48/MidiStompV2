#include <Arduino.h>
#include "Nav.h"
#include "Hardware.h"

Nav n;

void setup() {
  HW::setup();

  HW::screen.print(0,0,"Hey You");
}

void loop() {
  HW::loop();

  switch(n.e()) {
    case 0:
      break;
  };

}
