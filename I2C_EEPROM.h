#ifndef I2C_EEP_H
#define I2C_EEP_H

#define EEP_ADDRESS 0x50

void eWriteByte(uint16_t address, uint8_t data) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

uint8_t eReadByte(uint16_t address) {
  Wire.beginTransmission(EEP_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEP_ADDRESS, 1);
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

#define EEP_FUNC(name, obj_class, start) \
  static obj_class name##_at(uint8_t id) { \
    return get_data<obj_class>(start + sizeof(obj_class) * id); \
  } \
  static void name##_save(uint8_t id, obj_class *new_obj) { \
    set_data<obj_class>(new_obj, start + sizeof(obj_class) * id); \
  }

#define EEP_FUNC_EXTEND(name, obj_class, start, num_obj) \
  static obj_class name##_at_single(uint8_t id) { \
    return get_data<obj_class>(start + sizeof(obj_class) * id); \
  } \
  static void name##_save_single(uint8_t id, obj_class *new_obj) { \
    set_data<obj_class>(new_obj, start + sizeof(obj_class) * id); \
  } \
  static obj_class name##_at(uint8_t parent_id, uint8_t id) { \
    return get_data<obj_class>(start + sizeof(obj_class) * num_obj * parent_id + sizeof(obj_class) * id); \
  } \
  static void name##_save(uint8_t parent_id, uint8_t id, obj_class *new_obj) { \
    set_data<obj_class>(new_obj, start + sizeof(obj_class) * num_obj * parent_id + sizeof(obj_class) * id); \
  }

#undef EEP_ADDRESS

#endif
