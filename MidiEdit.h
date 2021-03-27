#ifndef MIDI_EDIT_H
#define MIDI_EDIT_H

// Definitions
#define NUM_KINDS 4

#include <Arduino.h>
#include "Standard.h"
#include "Hardware.h"
#include "Database.h"

struct MidiEdit {
  static Midi    *midi;
  static uint8_t event;
  static bool    initialize;

  static void setup(Midi *midi) {
    initialize = false;

    HW::screen.print_with_nline(0,0,"Type:");
    HW::screen.print(6,0,midiKind[midi->kind]);
    HW::screen.print_with_nline(0,1,"Note:");
    HW::screen.print(6,1,midi->note);
  }

  static bool loop() {
    switch(event) {
      case 0:
        if ( !initialize ) {
          initialize = true;
          break;
        }

        if ( HW::knob.is_long_pressed() ) {
          initialize = false;
          return true;
        }
        break;
    };

    return false;
  }
};

Midi    *MidiEdit::midi;
uint8_t  MidiEdit::event      = 0;
bool     MidiEdit::initialize = false;

#endif
