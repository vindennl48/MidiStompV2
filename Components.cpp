#include "Components.h"
#include "Hardware.h"
#include "I2C_EPROM.h"

/* :: OPTION :: */
Option::Option() : id(0) {}
Option::Option(uint16_t id) : id(id) {}

uint16_t Option::addr() {
  return ( MAP_OPTION + (id * OPTION_SZ) );
}
String Option::title() {
  return EPROM::read_text( addr() );
}
/* :: END OPTION :: */



/* :: MENU :: */
Menu::Menu() : id(0) {}
Menu::Menu(uint16_t id) : id(id) {}

uint16_t Menu::addr() {
  return ( MAP_MENU + (id * MENU_SZ) );
}

String Menu::title() {
  return EPROM::read_text( addr() );
}
uint8_t Menu::num_options() {
  return EPROM::read_uint8_t( addr() + 13 );
}
Option Menu::option(uint8_t n) {
  if ( n < num_options() )  return Option(n + (id * NUM_OPTIONS_PER_MENU));
  else                      return Option(id * NUM_OPTIONS_PER_MENU);
}
void Menu::loop_setup() {
  // print to screen
  //option(selected).title();
}
uint8_t Menu::loop() {
  if ( HW::knob.is_left() || HW::knob.is_right() ) {
    if ( HW::knob.is_left() )
      selected = CONTAIN((int)(selected-1), (int)0, (int)num_options());
    else if ( HW::knob.is_right() )
      selected = CONTAIN((int)(selected+1), (int)0, (int)num_options());

    loop_setup();  // refresh screen
  }
  else if ( HW::knob.is_pressed() ) return selected+1;
  else if ( HW::knob.is_long_pressed() ) {
    selected = 0;
    return NUM_OPTIONS_PER_MENU+1;
  }

  return false;
}
/* :: END MENU :: */



/* :: COLOR :: */
Color::Color() : id(0) {}
Color::Color(uint16_t id) : id(id) {}
uint16_t Color::addr() {
  return ( MAP_COLOR + (id * COLOR_SZ) );
}
String Color::name() { return EPROM::read_text(addr()); }
void Color::set_name(String text) { EPROM::write_text(addr(), text); }
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
String Feature::name() { return EPROM::read_text(addr()); }
void Feature::set_name(String text) { EPROM::write_text(addr(), text); }
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
String Pedal::name() { return EPROM::read_text(addr()); }
void Pedal::set_name(String text) { EPROM::write_text(addr(), text); }
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
Footswitch::Footswitch() : id(0) {}
Footswitch::Footswitch(uint16_t id) { load(id); }

uint16_t Footswitch::addr() {
  return ( MAP_FSW + (id * FSW_SZ) );
}
void Footswitch::load(uint16_t n) {
  id       = n;
  color[0] = EPROM::read_uint8_t ( addr() );
  color[1] = EPROM::read_uint8_t ( addr() + 1 );
  color[2] = EPROM::read_uint8_t ( addr() + 2 );
  data     = EPROM::read_uint16_t( addr() + 3 );
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
Footswitch Preset::footswitches[NUM_FSW_PER_PRESET];

Preset::Preset() : id(0), submenu_id(0), menu(0) {}
Preset::Preset(uint16_t id) : id(id), menu(0) { load(id); }

uint16_t Preset::addr() {
  return ( MAP_PRESET + (id * PRESET_SZ) );
}
String Preset::name() { return EPROM::read_text(addr()); }
void Preset::set_name(String text) { EPROM::write_text(addr(), text); }

Footswitch* Preset::fsw(uint8_t n) {
  return fsw(submenu_id, n);
}
Footswitch* Preset::fsw(uint8_t s, uint8_t n) {
  return &footswitches[n + (submenu_id * NUM_FSW_PER_SUBMENU)];
}
Param Preset::param(uint8_t n) {
  return Param( n + (id * NUM_PARAMS_PER_PRESET), true );
}
void Preset::print_main_screen() {
  //HW::screen.print_nline(0, 0, String(id+1) + ".");
  HW::screen.print_nline(0, 0, String(id+1) + "." + name());
  HW::screen.print_nline(0, 1, " ");
  HW::screen.print(10, 1, "MENU " + String(submenu_id+1));
}

void Preset::load(uint8_t n) {
  id         = n;
  submenu_id = 0;

  for (int i=0; i<NUM_FSW_PER_PRESET; i++)
    footswitches[i].load(i + (id * NUM_FSW_PER_PRESET));
}

uint8_t Preset::settings() {
  switch(nav.e()) {
    case 0: // MAIN
      if ( nav.not_init() ) menu.loop_setup();
      else {
        uint8_t result = menu.loop();
        if ( result ) nav.jump_to(result);
      }
      break;
    case 1: // NAME
    case 2: // PARAMS
    case 3: // RESET

    default: // BACK
      nav.reset();
      return true;
      break;
  };

  return false;
}

/* dont really need these anymore */
Footswitch Preset::get_fsw_from_eeprom(uint8_t n) {
  return get_fsw_from_eeprom(submenu_id, n);
}
Footswitch Preset::get_fsw_from_eeprom(uint8_t s, uint8_t n) {
  return Footswitch(
    n + (id * NUM_FSW_PER_PRESET) +
      (submenu_id * NUM_FSW_PER_SUBMENU)
  );
}

Preset preset;
/* :: END PRESET :: */
