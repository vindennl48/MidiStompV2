#ifndef MENU_DEVICES_H
#define MENU_DEVICES_H

#include "Hardware.h"
#include "Database.h"
#include "Menu.h"
#include "TextEdit.h"

#define E_DEVICE_SELECT 0
#define E_DEVICE_NAME   1
#define E_DEVICE_PARAMS 2
#define E_DEVICE_RESET  3
#define E_BACK          4

struct MenuDevices {
  Menu    m;
  Device  device;
  uint8_t device_id = 0;

  String make_device_str() {
    device        = GET_DEVICE(device_id);
    String result = String(device_id) + ")" + device.get_name();
    return result;
  }

  bool loop() {
    switch(m.e()) {
      case E_DEVICE_SELECT:
        if ( m.not_initialized() ) {
          HW::screen.clear();
          HW::screen.print(0,0,"::DEVICE::");
          HW::screen.print(0,1,make_device_str());
        }
        else if ( HW::knob.is_left() )  {
          if ( device_id != 0 ) device_id -= 1; 
          m.jump_to(E_DEVICE_SELECT);
        }
        else if ( HW::knob.is_right() ) {
          device_id += 1;
          if ( device_id >= DEVICE_MAX ) device_id = DEVICE_MAX-1;
          m.jump_to(E_DEVICE_SELECT);
        }
        else if ( HW::knob.is_pressed() )      { m.jump_to(E_DEVICE_NAME); }
        else if ( HW::knob.is_long_pressed() ) { return m.back(); }
        break;

      case E_DEVICE_NAME:
        if ( m.is_active() ) {
          if ( m.not_initialized() ) { TextEdit::setup(device.get_name()); }
          else if ( TextEdit::loop() ) {
            device.set_name(TextEdit::get_text());
            SET_DEVICE(&device);
            m.jump_to(E_DEVICE_NAME);
          }
        }
        else if ( m.not_initialized() ) {
          HW::screen.clear();
          HW::screen.print(0,0,"::" + device.get_name());
          HW::screen.print(0,1," >NAME");
        }
        else if ( HW::knob.is_right() )   { m.jump_to(E_DEVICE_PARAMS); }
        else if ( HW::knob.is_pressed() ) { m.activate(); }
        break;

      case E_DEVICE_PARAMS:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  NAME");
          HW::screen.print_with_nline(0,1," >PARAMS");
        }
        else if ( HW::knob.is_left() )  { m.jump_to(E_DEVICE_NAME); }
        else if ( HW::knob.is_right() ) { m.jump_to(E_DEVICE_RESET); }
        break;

      case E_DEVICE_RESET:
        if ( m.is_active() ) {
          if ( m.not_initialized() ) {
            HW::screen.clear();
            HW::screen.print(0,0,"::" + device.get_name());
            HW::screen.print(0,1,"RESET DEVICE?");
          }
          else if ( HW::knob.is_pressed() )      {
            Device new_device;
            new_device.id = device.id;
            SET_DEVICE(&new_device);
            m.jump_to(E_DEVICE_SELECT);
          }
          else if ( HW::knob.is_long_pressed() ) { m.jump_to(E_DEVICE_RESET); }
        }
        else if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  PARAMS");
          HW::screen.print_with_nline(0,1," >RESET");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_DEVICE_PARAMS); }
        else if ( HW::knob.is_right() )   { m.jump_to(E_BACK); }
        else if ( HW::knob.is_pressed() ) { m.activate(); }
        break;

      case E_BACK:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  RESET");
          HW::screen.print_with_nline(0,1," >BACK");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_DEVICE_RESET); }
        else if ( HW::knob.is_pressed() ) { m.jump_to(E_DEVICE_SELECT); }
        break;

      default:
        m.jump_to(E_DEVICE_SELECT);
    };

    return false;
  }

} menu_devices;
uint8_t menuDevices() { return menu_devices.loop(); }

#undef E_DEVICE_SELECT
#undef E_DEVICE_NAME
#undef E_DEVICE_PARAMS
#undef E_DEVICE_RESET
#undef E_BACK

#endif
