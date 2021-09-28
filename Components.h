#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "Helpers.h"

/* EEPROM MAP */
#define NUM_COLORS 50
#define NUM_PEDALS 8

#define MAP_COLOR 10
#define MAP_PEDAL (MAP_COLOR + (NUM_COLORS*COLOR_SZ))
/* END EEPROM MAP */


#define COLOR_SZ 16
struct Color : ObjName {
  uint8_t id;

  Color();
  Color(uint8_t);

  uint16_t addr();
  uint8_t  at(uint8_t);
  void     set_at(uint8_t, uint8_t);
};

#endif
