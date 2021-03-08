#ifndef MENU_DEVICES_H
#define MENU_DEVICES_H

#include "Hardware.h"

struct MenuDevices {
  static uint8_t event;
  static uint8_t initialize;

  static bool loop() {
  }

};

uint8_t MenuSettings::event      = 0;
uint8_t MenuSettings::initialize = false;

#endif
