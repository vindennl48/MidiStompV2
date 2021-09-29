#include <Arduino.h>
#include "Nav.h"
#include "Hardware.h"
#include "Components.h"

#define E_SETUP        0
#define E_TX_RX        1
#define E_MAIN         2
#define E_SETTINGS     3
#define E_FSW_SETTINGS 4

Nav n;

void setup() {
  HW::setup();

  Preset preset(0);
  HW::screen.print(0,0,"Hey You");
  // for (int i=0; i<NUM_LEDS; i++)
  //   HW::leds[i].set(0, 0, 0);
}

void loop() {
  HW::loop();

  switch(n.e()) {
    case E_SETUP:
      break;

    case E_TX_RX:
      break;

    case E_MAIN:
      break;

    case E_SETTINGS:
      break;

    case E_FSW_SETTINGS:
      break;
  };

}
