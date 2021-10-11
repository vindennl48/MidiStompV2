#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"
#include "Components.h"

void e_setup(Nav *n) {
  if ( n->not_init() ) {
    preset.load(0);
  }
  else {
    n->jump_to(E_MAIN);
  }
}
