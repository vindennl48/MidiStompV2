#ifndef PARAM_H
#define PARAM_H

#include <Arduino.h>
#include "Definitions.h"

struct Param {
  static uint16_t hd_start();   // start of preset in eeprom
  static uint16_t get_addr(uint8_t);

  union { struct {
    unsigned velocity_val:7;
    unsigned feature_id:5;
    unsigned pedal_id:4;
  };};

  Param();
  //Pedal   pedal();
  //Feature feature(uint8_t);
  //uint8_t velocity();

  void set_pedal(uint8_t);
  void set_feature(uint8_t);
  void set_velocity(uint8_t);
};

struct PresetParam : Param {
  static uint16_t hd_start();
};
struct FswParam : Param {
  static uint16_t hd_start();
};

#endif
