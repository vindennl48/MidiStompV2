#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"

void e_tx_rx(Nav *n) {
  if ( n->not_init() ) {
    HW::screen.print(0,1,"BOO");
  }
  else {
  }
}
