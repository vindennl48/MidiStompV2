#ifndef MENU_SETTINGS_H
#define MENU_SETTINGS_H

#include "Hardware.h"
#include "MenuGlobalSettings.h"

// Definitions
#define E_NAME            0
#define E_BPM             1
#define E_SWITCHES        2
#define E_GLOBAL_SETTINGS 3
#define E_BACK            4

struct MenuSettings {
  static uint8_t event;
  static uint8_t initialize;
  static uint8_t active;

  static bool loop() {
    switch(event) {
      case E_NAME:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"::SETTINGS::");
          HW::screen.print_with_nline(0,1,"> NAME");
          initialize = true;
          break;
        }

        if ( HW::knob.is_right() ) {
          event      = E_BPM;
          initialize = false;
        }

        break;

      case E_BPM:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  NAME");
          HW::screen.print_with_nline(0,1,"> BPM");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_NAME;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_SWITCHES;
          initialize = false;
        }

        break;

      case E_SWITCHES:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  BPM");
          HW::screen.print_with_nline(0,1,"> SWITCHES");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_BPM;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_GLOBAL_SETTINGS;
          initialize = false;
        }

        break;

      case E_GLOBAL_SETTINGS:
        if ( active ) {
          if ( MenuGlobalSettings::loop() ) {
            event      = E_NAME;
            initialize = false;
            active     = false;
            return true;
          }
          break;
        }
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  SWITCHES");
          HW::screen.print_with_nline(0,1,"> GBL SETTINGS");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_SWITCHES;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_BACK;
          initialize = false;
        }
        else if ( HW::knob.is_pressed() ) {
          initialize = false;
          active     = true;
        }

        break;

      case E_BACK:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  GBL SETTINGS");
          HW::screen.print_with_nline(0,1,"> BACK");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_GLOBAL_SETTINGS;
          initialize = false;
        }
        else if ( HW::knob.is_pressed() ) {
          event      = E_NAME;
          initialize = false;
          return true;
        }

        break;
    };

    return false;
  }

};


uint8_t MenuSettings::event      = 0;
uint8_t MenuSettings::initialize = false;
uint8_t MenuSettings::active     = false;

#undef E_NAME
#undef E_BPM
#undef E_SWITCHES
#undef E_GLOBAL_SETTINGS
#undef E_BACK

#endif
