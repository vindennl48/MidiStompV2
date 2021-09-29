#include "Components.h"
#include "I2C_EPROM.h"



/* :: COLOR :: */
Color::Color() : id(0) {}
Color::Color(uint16_t id) : id(id) {}
uint16_t Color::addr() {
  return ( MAP_COLOR + (id * COLOR_SZ) );
}
uint8_t Color::at(uint8_t n) {
  return EPROM::read_uint8_t( addr() + TEXT_SZ + MOD(n,3) );
}
void Color::set_at(uint8_t n, uint8_t x) {
  EPROM::write_uint8_t( addr() + TEXT_SZ + MOD(n,3), x );
}
/* :: END COLOR :: */



/* :: FEATURE :: */
Feature::Feature() : id(0) {}
Feature::Feature(uint16_t id) : id(id) {}

uint16_t Feature::addr() {
  return ( MAP_FEATURE + (id * FEATURE_SZ) );
}
uint8_t Feature::type() {
  return EPROM::read_uint8_t( addr() + TEXT_SZ );
}
void Feature::set_type(uint8_t x) {
  EPROM::write_uint8_t( addr() + TEXT_SZ, x );
}
uint8_t Feature::pitch() {
  return EPROM::read_uint8_t( addr() + TEXT_SZ + 1 );
}
void Feature::set_pitch(uint8_t x) {
  EPROM::write_uint8_t( addr() + TEXT_SZ + 1, x );
}
/* :: END FEATURE :: */



/* :: PEDAL :: */
Pedal::Pedal() : id(0) {}
Pedal::Pedal(uint16_t id) : id(id) {}

uint16_t Pedal::addr() {
  return ( MAP_PEDAL + (id * PEDAL_SZ) );
}
uint8_t Pedal::channel() {
  return EPROM::read_uint8_t( addr() + TEXT_SZ );
}
void Pedal::set_channel(uint8_t x) {
  EPROM::write_uint8_t( addr() + TEXT_SZ, x );
}
Feature Pedal::feature(uint8_t n) {
  return Feature( n + (id * NUM_PEDALS) );
}
/* :: END PEDAL :: */



/* :: PARAM :: */
Param::Param() : id(0), is_preset(false), data(0) {}
Param::Param(uint16_t id, uint8_t is_preset)
  : id(id), is_preset(is_preset), data(0) {
  data = EPROM::read_uint16_t( addr() );
}

uint16_t Param::addr() {
  if ( is_preset )
    return ( MAP_PRESET_PARAM + (id * PARAM_SZ) );
  else
    return ( MAP_PARAM + (id * PARAM_SZ) );
}
void Param::save() {
  EPROM::write_uint16_t( addr(), data );
}
Pedal Param::pedal() {
  return Pedal(d_pedal_id);
}
void Param::set_pedal(Pedal x) {
  d_pedal_id = x.id;
  save();
}
Feature Param::feature() {
  return pedal().feature(d_feature);
}
void Param::set_feature(Feature x) {
  /* NEED to calculate relative d_feature */
  d_feature = x.id;
  /* NEED to calculate relative d_feature */
  save();
}
uint8_t Param::velocity() {
  return d_velocity;
}
void Param::set_velocity(uint8_t x) {
  d_velocity = x;
  save();
}
void Param::send_midi() {}
/* :: END PARAM :: */



/* :: FSW :: */
Footswitch footswitches[NUM_FSW_PER_PRESET];

Footswitch::Footswitch() : id(0) { setup(); }
Footswitch::Footswitch(uint16_t id) : id(id) { setup(); }

uint16_t Footswitch::addr() {
  return ( MAP_FSW + (id * FSW_SZ) );
}
void Footswitch::setup() {
  color[0] = EPROM::read_uint8_t ( addr() );
  //color[1] = EPROM::read_uint8_t ( addr() + 1 );
  //color[2] = EPROM::read_uint8_t ( addr() + 2 );
  //data     = EPROM::read_uint16_t( addr() + 3 );
}
Param Footswitch::param(uint8_t n) {
  return param(d_state, n);
}
Param Footswitch::param(uint8_t s, uint8_t n) {
  return Param( n + (id * NUM_PARAMS_PER_FSW) + (s * NUM_PARAMS_PER_STATE), false );
}
Param Footswitch::lp_param(uint8_t n) {
  // state 0-2 are normal states, state 3 is long press
  return param(NUM_STATES_PER_FSW-1, n);
}

uint8_t Footswitch::mode()                    { return d_mode; }
void    Footswitch::set_mode(uint8_t x)       { d_mode = x & 0b111; }
uint8_t Footswitch::lp_mode()                 { return d_lp_mode; }
void    Footswitch::set_lp_mode(uint8_t x)    { d_lp_mode  = x & 0b111; }
uint8_t Footswitch::press_type()              { return d_press_type; }
void    Footswitch::set_press_type(uint8_t x) { d_press_type = x & 0b1; }

void Footswitch::save() {
  EPROM::write_uint8_t ( addr()    , color[0] );
  EPROM::write_uint8_t ( addr() + 1, color[1] );
  EPROM::write_uint8_t ( addr() + 2, color[2] );
  EPROM::write_uint16_t( addr() + 3, data );
}

void Footswitch::update_state() {
  d_state += 1;
  if ( d_mode == FSW_MODE_CYCLE ) {
    if ( d_state >= 3 ) d_state = 0;
  }
  else if ( d_mode == FSW_MODE_ONESHOT ) {
    d_state = 0;
  }
  else if ( FSW_MODE_TOGGLE && d_state >= 2 ) d_state = 0;
}
void Footswitch::send_midi() {
  for (int i=0; i<NUM_PARAMS_PER_STATE; i++) param(i).send_midi();
}
void Footswitch::lp_send_midi() {
  for (int i=0; i<NUM_PARAMS_PER_STATE; i++) lp_param(i).send_midi();
}
/* :: END FSW :: */



/* :: PRESET :: */
Preset::Preset() : id(0), submenu_id(0) {}
Preset::Preset(uint16_t id) : id(id), submenu_id(0) {}

uint16_t Preset::addr() {
  return ( MAP_PRESET + (id * PRESET_SZ) );
}

Footswitch* Preset::fsw(uint8_t n) {
  return fsw(submenu_id, n);
}
Footswitch* Preset::fsw(uint8_t s, uint8_t n) {
  return &footswitches[n + (submenu_id * NUM_FSW_PER_SUBMENU)];
}

Footswitch Preset::get_fsw_from_eeprom(uint8_t n) {
  return get_fsw_from_eeprom(submenu_id, n);
}
Footswitch Preset::get_fsw_from_eeprom(uint8_t s, uint8_t n) {
  return Footswitch(
    n + (id * NUM_FSW_PER_PRESET) +
      (submenu_id * NUM_FSW_PER_SUBMENU)
  );
}
/* :: END PRESET :: */
