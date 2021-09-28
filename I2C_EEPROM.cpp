#include "I2C_EEPROM.h"
#include "Helpers.h"
#include <Arduino.h>
#include <Wire.h>

uint8_t EEPROM::read_uint8_t(uint16_t addr) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEP_ADDRESS, 1);
  return Wire.read();
}

void EEPROM::write_uint8_t(uint16_t addr, uint8_t x) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.write(x);
  Wire.endTransmission();
  delay(5);
}

uint16_t EEPROM::read_uint16_t(uint16_t addr) {
  return ( read_uint8_t(addr)<<8 | read_uint8_t(addr+1) );
}
void EEPROM::write_uint16_t(uint16_t addr, uint16_t x) {
  write_uint8_t(addr, x>>8);
  write_uint8_t(addr, (x<<8)>>8);  // shift up 8 to remove top byte
}

Text EEPROM::read_text(uint16_t addr) {}
void EEPROM::write_text(uint16_t addr, Text t) {}
