#include "Param.h"
#include "Preset.h"


//-PARAM------------------------------------------------------------------------
// Static
uint16_t Param::hd_start() {
  return HD_START_PRESET_PARAMS;
}

uint16_t Param::get_addr(uint8_t id) {
  return GET_PARENT(hd_start(), id, sizeof(Param));
}

// Self
Param::Param() {
  pedal_id     = NUM_PEDALS;
  feature_id   = 0;
  velocity_val = 0;
}

//Pedal   Param::pedal() {}
//Feature Param::feature(uint8_t id) {}
//uint8_t Param::velocity() {}

void Param::set_pedal(uint8_t id) {}
void Param::set_feature(uint8_t id) {}
void Param::set_velocity(uint8_t value) {}
//------------------------------------------------------------------------------



//-PRESET PARAM-----------------------------------------------------------------
uint16_t PresetParam::hd_start() {
  return HD_START_PRESET_PARAMS;
}
//------------------------------------------------------------------------------



//-FSW PARAM--------------------------------------------------------------------
uint16_t FswParam::hd_start() {
  return HD_START_FSW_PARAMS;
}
//------------------------------------------------------------------------------
