#include "Components.h"
#include "I2C_EEPROM.h"

/* :: COLOR :: */
Color::Color(uint8_t id) : id(id) {}
Color::Color() : id(0) {}
uint16_t Color::addr() {
  return ( MAP_COLOR + (id * COLOR_SZ) + TEXT_SZ );
}
uint8_t Color::at(uint8_t n) {
  return EEPROM::read_uint8_t( addr() + MOD(n,3) );
}
void Color::set_at(uint8_t n, uint8_t x) {
  EEPROM::write_uint8_t( addr() + MOD(n,3), x );
}
/* :: END COLOR :: */
