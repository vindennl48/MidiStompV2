#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

#define EEPROM_ADDRESS 0x50

void eWriteByte(uint16_t address, uint8_t data) {
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

uint8_t eReadByte(uint16_t address) {
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDRESS, 1);
  return Wire.read();
}

void eWriteBlock(uint16_t address, const uint8_t *data, uint16_t size) {
  for (uint16_t i=0; i<size; i++) {
    eWriteByte(address + i, *(data+i));
  }
}

void eReadBlock(uint16_t address, uint8_t *data, uint16_t size) {
  for (uint16_t i=0; i<size; i++) {
    *(data+i) = eReadByte(address + i);
  }
}

template <typename T>
T get_data(uint16_t start) {
  T data;

  eReadBlock(
    start,
    (uint8_t*)&data,
    sizeof(T)
  );

  return data;
}

template <typename T>
void set_data(T *data, uint16_t start) {
  eWriteBlock(
    start,
    (const uint8_t*)data,
    sizeof(T)
  );
}

#undef EEPROM_ADDRESS

#endif
