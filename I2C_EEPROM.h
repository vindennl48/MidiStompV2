#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

#include <Arduino.h>
#include "Helpers.h"

#define EEP_ADDRESS 0x50

struct EEPROM {
  static uint8_t read_uint8_t(uint16_t);
  static void    write_uint8_t(uint16_t, uint8_t);

  static uint16_t read_uint16_t(uint16_t);
  static void     write_uint16_t(uint16_t, uint16_t);

  static Text read_text(uint16_t);
  static void write_text(uint16_t, Text);
};

#endif
