#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"
#include "Components.h"

void e_main(Nav *n) {
  if ( n->not_init() ) {
    preset.print_main_screen();
  }
  else {
  }
}
