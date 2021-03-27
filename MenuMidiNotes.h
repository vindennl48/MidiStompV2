#ifndef MENU_MIDI_NOTES_H
#define MENU_MIDI_NOTES_H


#include "hardware.h"
#include "Database.h"
#include "Menu.h"
#include "MidiEdit.h"


#define E_NOTE_SELECT 0
#define E_NOTE_EDIT   1
// MIDI_MAX - Database.h


struct MidiMenuNotes {
  Menu    m;
  Midi    midi;
  uint8_t midi_id = 0;

  String make_midi_str() {
    midi          = GET_MIDI(midi_id);
    String result = String(midi_id) + ")" + midiKind[midi.kind] + " " + String(midi.note);
    return result;
  }

  bool loop() {
    switch(m.e()) {
      case E_NOTE_SELECT:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(0,0, "::EDIT MIDI::");
          HW::screen.print_with_nline(0,1, make_midi_str());
        }
        else if ( HW::knob.is_left() )  {
          if ( midi_id != 0 ) midi_id -= 1; 
          m.jump_to(E_NOTE_SELECT);
        }
        else if ( HW::knob.is_right() ) {
          midi_id += 1;
          if ( midi_id >= MIDI_MAX ) midi_id = MIDI_MAX-1;
          m.jump_to(E_NOTE_SELECT);
        }
        else if ( HW::knob.is_pressed() )      { m.jump_to(E_NOTE_EDIT); }
        else if ( HW::knob.is_long_pressed() ) { return m.back(); }
        break;

      case E_NOTE_EDIT:
        if ( m.not_initialized() ) {}
        else {
          if ( midi_edit.loop(&midi) ) { m.jump_to(E_NOTE_SELECT); }
        }
        break;

      default:
        m.jump_to(0);
    };

    return false;
  }

} menu_midi_notes;



#endif
