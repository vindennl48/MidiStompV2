#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"

void e_setup(Nav *n) {
  if ( n->not_init() ) {
    HW::screen.print(0,1,"IDL UR GF");
  }
  else {
    n->jump_to(E_TX_RX);
  }
}
