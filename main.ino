#include <Arduino.h>
#include "Nav.h"
#include "Hardware.h"
#include "Main_Events.h"
#include "Com.h"

Nav n;

void setup() {
  HW::setup();
}

void loop() {
  HW::loop();

  // Connect to PC
  if ( COM::is_socket ) {
    if ( COM::socket() ) {
      n.reset();
    }
  }
  else {
    COM::thru();

    switch(n.e()) {
      case E_SETUP:        e_setup(&n);        break;
      case E_MAIN:         e_main(&n);         break;
      /*case E_SETTINGS:     e_settings(&n);     break;*/
      /*case E_FSW_SETTINGS: e_fsw_settings(&n); break;*/
    };
  }
}
