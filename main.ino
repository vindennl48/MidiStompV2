#include <Arduino.h>
#include "Nav.h"
#include "Hardware.h"
#include "Components.h"

Nav n;

void setup() {
  HW::setup();

  Preset preset(0);
  HW::screen.print(0,0,"Hey You");
}

void loop() {
  HW::loop();

  switch(n.e()) {
    case 0:
      break;
  };

}
