#include <Arduino.h>
#include "Helpers.h"
#include "I2C_EPROM.h"

/* :: OBJNAME :: */
uint16_t addr() { return 0; } // needs to be overloaded by host

String ObjName::name() {
  return EPROM::read_text( addr() );
}

void ObjName::set_name(String text) {
  EPROM::write_text( addr(), text );
}
/* :: END OBJNAME :: */


