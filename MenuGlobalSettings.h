#ifndef MENU_GLOBAL_SETTINGS_H
#define MENU_GLOBAL_SETTINGS_H

#include "Hardware.h"

// Definitions
#define E_DEVICES       0
#define E_MIDI_NOTES    1
#define E_COLORS        2
#define E_FACTORY_RESET 3
#define E_BACK          4


struct MenuGlobalSettings {
  static uint8_t event;
  static uint8_t initialize;
  static uint8_t active;

  static bool loop() {
    switch(event) {
      case E_DEVICES:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"::GBL SETTINGS::");
          HW::screen.print_with_nline(0,1,"> DEVICES");
          initialize = true;
          break;
        }

        if ( HW::knob.is_right() ) {
          event      = E_MIDI_NOTES;
          initialize = false;
        }

        break;

      case E_MIDI_NOTES:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  DEVICES");
          HW::screen.print_with_nline(0,1,"> MIDI NOTES");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_DEVICES;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_COLORS;
          initialize = false;
        }

        break;

      case E_COLORS:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  MIDI NOTES");
          HW::screen.print_with_nline(0,1,"> COLORS");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_MIDI_NOTES;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_FACTORY_RESET;
          initialize = false;
        }

        break;

      case E_FACTORY_RESET:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  COLORS");
          HW::screen.print_with_nline(0,1,"> FACTORY RESET");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_COLORS;
          initialize = false;
        }
        else if ( HW::knob.is_right() ) {
          event      = E_BACK;
          initialize = false;
        }

        break;

      case E_BACK:
        if ( !initialize ) {
          HW::screen.print_with_nline(0,0,"  FACTORY RESET");
          HW::screen.print_with_nline(0,1,"> BACK");
          initialize = true;
          break;
        }

        if ( HW::knob.is_left() ) {
          event      = E_FACTORY_RESET;
          initialize = false;
        }
        else if ( HW::knob.is_pressed() ) {
          event      = E_DEVICES;
          initialize = false;
          return true;
        }

        break;
    };

    return false;
  }

};


uint8_t MenuGlobalSettings::event      = 0;
uint8_t MenuGlobalSettings::initialize = false;
uint8_t MenuGlobalSettings::active     = false;


#undef E_DEVICES
#undef E_MIDI_NOTES
#undef E_COLORS
#undef E_FACTORY_RESET
#undef E_BACK

#endif
