#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"

void e_setup(Nav *n) {
  if ( n->not_init() ) {
    HW::screen.print(0,0,"SETUP");
  }
  else {
    n->jump_to(E_MAIN);
  }
}
