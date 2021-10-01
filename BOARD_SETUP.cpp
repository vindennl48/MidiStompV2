#include "Main_Events.h"
#include "Hardware.h"

void board_setup() {
  HW::setup();
  HW::screen.print(0,0,"Hey You");
}
