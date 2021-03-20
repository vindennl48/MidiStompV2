#ifndef MENU_MIDI_NOTES_H
#define MENU_MIDI_NOTES_H

#include "hardware.h"
#include "Database.h"

// Definitions
#define E_NOTE_SELECT  0
#define E_NOTE_EDIT    1

struct MenuMidiNotes {
  static uint8_t event;
  static uint8_t initialize;
  static uint8_t midi_id;
  static Midi    midi;

  static bool loop() {
    switch(event) {
      case E_NOTE_SELECT:
        if ( !initialize ) {
          initialize = true;

          midi        = GET_MIDI(midi_id);
          String ID   = String(midi_id) + ")";
          String kind = midiKind[midi.kind];
          String note = String(midi.note);
          HW::screen.print_with_nline(0,0, "::EDIT MIDI::");
          HW::screen.print_with_nline(0,1, ID + kind + " " + note);
          break;
        }

        if ( HW::knob.is_long_pressed() ) {
          initialize = false;
          return true;
        }
        break;

      case E_NOTE_EDIT:
        break;
    };

    return false;
  }
};

uint8_t MenuMidiNotes::event      = 0;
uint8_t MenuMidiNotes::initialize = false;
uint8_t MenuMidiNotes::midi_id    = 0;
Midi    MenuMidiNotes::midi;

#endif
