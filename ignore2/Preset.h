#ifndef PRESET_H
#define PRESET_H

#include <Arduino.h>
#include "Param.h"

struct Preset {
  static uint8_t  preset_id;    // current preset_id
  static uint16_t hd_start();   // start of presets in eeprom
  static uint16_t addr();
  static uint16_t addr(uint8_t);

  void name(uint8_t);
  PresetParam param(uint8_t);
};


#endif
