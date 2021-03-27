#ifndef MENU_SETTINGS_H
#define MENU_SETTINGS_H


#include "Hardware.h"
#include "MenuGlobalSettings.h"


#define E_NAME            0
#define E_BPM             1
#define E_SWITCHES        2
#define E_GLOBAL_SETTINGS 3
#define E_BACK            4


struct MenuSettings {
  Menu m;

  bool loop() {
    switch(m.e()) {
      case E_NAME:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"::SETTINGS::");
          HW::screen.print_with_nline(0,1,"> NAME");
        }
        else if ( HW::knob.is_right() ) { m.jump_to(E_BPM); }
        break;

      case E_BPM:
        if ( m.not_initialized()) {
          HW::screen.print_with_nline(0,0,"  NAME");
          HW::screen.print_with_nline(0,1,"> BPM");
        }
        else if ( HW::knob.is_left() )  { m.jump_to(E_NAME); }
        else if ( HW::knob.is_right() ) { m.jump_to(E_SWITCHES); }
        break;

      case E_SWITCHES:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  BPM");
          HW::screen.print_with_nline(0,1,"> SWITCHES");
        }
        else if ( HW::knob.is_left() )  { m.jump_to(E_BPM); }
        else if ( HW::knob.is_right() ) { m.jump_to(E_GLOBAL_SETTINGS); }
        break;

      case E_GLOBAL_SETTINGS:
        if ( m.is_active() ) {
          if ( menu_global_settings.loop() ) { m.jump_to(E_GLOBAL_SETTINGS); }
        }
        else if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  SWITCHES");
          HW::screen.print_with_nline(0,1,"> GBL SETTINGS");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_SWITCHES); }
        else if ( HW::knob.is_right() )   { m.jump_to(E_BACK); }
        else if ( HW::knob.is_pressed() ) { m.activate(); }
        break;

      case E_BACK:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  GBL SETTINGS");
          HW::screen.print_with_nline(0,1,"> BACK");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_GLOBAL_SETTINGS); }
        else if ( HW::knob.is_pressed() ) { return m.back(); }
        break;

      default:
        m.jump_to(0);
    };

    return false;
  }

} menu_settings;


#undef E_NAME
#undef E_BPM
#undef E_SWITCHES
#undef E_GLOBAL_SETTINGS
#undef E_BACK


#endif
