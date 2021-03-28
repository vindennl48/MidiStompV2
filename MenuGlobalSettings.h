#ifndef MENU_GLOBAL_SETTINGS_H
#define MENU_GLOBAL_SETTINGS_H


#include "Hardware.h"
#include "Menu.h"
#include "MenuMidiNotes.h"
#include "MenuDevices.h"


/* :: GLOBAL SETTINGS :: */
#define E_DEVICES       0
#define E_MIDI_NOTES    1
#define E_COLORS        2
#define E_FACTORY_RESET 3
#define E_BACK          4

struct MenuGlobalSettings {
  Menu m;

  bool loop() {
    switch(m.e()) {
      case E_DEVICES:
        if ( m.is_active() ) {
          if ( menu_devices.loop() ) { m.jump_to(E_DEVICES); }
        }
        else if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"::GBL SETTINGS::");
          HW::screen.print_with_nline(0,1,"> DEVICES");
        }
        else if ( HW::knob.is_right() ) { m.jump_to(E_MIDI_NOTES); }
        else if ( HW::knob.is_pressed() ) { m.activate(); }
        break;

      case E_MIDI_NOTES:
        if ( m.is_active() ) {
          if ( menu_midi_notes.loop() ) { m.jump_to(E_MIDI_NOTES); }
        }
        else if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  DEVICES");
          HW::screen.print_with_nline(0,1,"> MIDI NOTES");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_DEVICES); }
        else if ( HW::knob.is_right() )   { m.jump_to(E_COLORS); }
        else if ( HW::knob.is_pressed() ) { m.activate(); }
        break;

      case E_COLORS:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  MIDI NOTES");
          HW::screen.print_with_nline(0,1,"> COLORS");
        }
        else if ( HW::knob.is_left() )  { m.jump_to(E_MIDI_NOTES); }
        else if ( HW::knob.is_right() ) { m.jump_to(E_FACTORY_RESET); }
        break;

      case E_FACTORY_RESET:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  COLORS");
          HW::screen.print_with_nline(0,1,"> FACTORY RESET");
        }
        else if ( HW::knob.is_left() )  { m.jump_to(E_COLORS); }
        else if ( HW::knob.is_right() ) { m.jump_to(E_BACK); }
        break;

      case E_BACK:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"  FACTORY RESET");
          HW::screen.print_with_nline(0,1,"> BACK");
        }
        else if ( HW::knob.is_left() )    { m.jump_to(E_FACTORY_RESET); }
        else if ( HW::knob.is_pressed() ) { return m.back(); }
        break;

      default:
        m.jump_to(0);
    };

    return false;
  }

} menu_global_settings;

#undef E_DEVICES
#undef E_MIDI_NOTES
#undef E_COLORS
#undef E_FACTORY_RESET
#undef E_BACK
/* :: END GLOBAL SETTINGS :: */

#endif
