#include "Component.h"
#include "Definitions.h"
#include "Preset.h"
#include "Param.h"
#include "I2C_EEPROM.h"

// Static
uint8_t  Preset::preset_id = 0;

uint16_t Preset::addr() {
  return addr(preset_id);
}

COMPONENT_CREATE_FUNC_HD_START(Preset, HD_START_PRESETS);
COMPONENT_CREATE_FUNC_NAME(Preset);
COMPONENT_CREATE_FUNC_ADDR(Preset);
//COMPONENT_CREATE_FUNC_ALL(Preset, (HD_START_PRESETS));

// uint16_t hd_start() {
//   return HD_START_PRESETS;
// }
// uint16_t Preset::get_addr(uint8_t id) {
//   return GET_PARENT(hd_start(), id, sizeof(Preset));
// }

// Self
// void Preset::name(uint8_t buffer=TXT_BUF_1) {
//   eReadBlock(get_addr(), (uint8_t*)text[buffer], sizeof(TEXT_SZ));
// }

PresetParam Preset::param(uint8_t id) {
  return read_data<PresetParam>(PresetParam::addr(id));
}
