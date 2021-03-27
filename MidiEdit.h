#ifndef MIDI_EDIT_H
#define MIDI_EDIT_H

// Definitions
#define NUM_KINDS 4

#include "Hardware.h"
#include "Menu.h"

#define E_SELECT      0
#define E_CHANGE_TYPE 1
#define E_CHANGE_NOTE 2

struct MidiEdit {
  Menu m;

  bool loop(Midi *midi) {
    switch(m.e()) {
      case E_SELECT:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0,"Type:");
          HW::screen.print(6,0,midiKind[midi->kind]);
          HW::screen.print_with_nline(0,1,"Note:");
          HW::screen.print(6,1,midi->note);
        }
        else if ( HW::knob.is_long_pressed() ) { return m.back(); }
        break;

      default:
        m.jump_to(0);
    };

    return false;
  }

} midi_edit;


#undef E_SELECT
#undef E_CHANGE_TYPE
#undef E_CHANGE_NOTE


#endif
