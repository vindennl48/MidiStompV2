#include <Arduino.h>
#include <Wire.h>
#include "I2C_EPROM.h"

uint8_t EPROM::read_uint8_t(uint16_t addr) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEP_ADDRESS, 1);
  return Wire.read();
}

void EPROM::write_uint8_t(uint16_t addr, uint8_t x) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.write(x);
  Wire.endTransmission();
  delay(5);
}

uint16_t EPROM::read_uint16_t(uint16_t addr) {
  return ( read_uint8_t(addr)<<8 | read_uint8_t(addr+1) );
}
void EPROM::write_uint16_t(uint16_t addr, uint16_t x) {
  write_uint8_t(addr, x>>8);
  write_uint8_t(addr, (x<<8)>>8);  // shift up 8 to remove top byte
}

String EPROM::read_text(uint16_t addr) {
  String result;
  for (int i=0; i<12; i++)
    result += (char)read_uint8_t(addr + i);
  return result;
}
void   EPROM::write_text(uint16_t addr, String t) {}
