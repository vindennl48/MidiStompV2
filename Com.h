#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include "Nav.h"

struct COM {
  static Nav     n;
  static uint8_t is_socket;

  static void    thru();
  static uint8_t socket();
  static void    debug(String);
};

#define DEBUG(text) COM::debug(String(text))

#endif
