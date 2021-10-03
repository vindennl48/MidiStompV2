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
  COM::thru();

  // Connect to PC
  if ( COM::is_socket ) {
    if ( COM::socket() ) {
      COM::is_socket = false;
      n.reset();
    }
  }

  else {
    switch(n.e()) {
      case E_SETUP:        e_setup(&n);        break;
      /*case E_TX_RX:        e_tx_rx(&n);        break;*/
      case E_MAIN:         e_main(&n);         break;
      /*case E_SETTINGS:     e_settings(&n);     break;*/
      /*case E_FSW_SETTINGS: e_fsw_settings(&n); break;*/
    };
  }
}


/*

One way to do the history/menu system is to build the menus right into the
components.  Run a member function right off of the component you want to edit.

 */
