#ifndef MIDI_EDIT_H
#define MIDI_EDIT_H

// Definitions
#define NUM_KINDS 4

#include <Arduino.h>
#include "Standard.h"
#include "Hardware.h"
#include "MidiEdit.h"

struct MidiEdit {
  static DB::Midi *midi;
  static uint8_t  event;
  static bool     initialized;
  static String   kind[NUM_KINDS];

  static void setup(DB::Midi *midi) {
    initialized    = false;
    MidiEdit::midi = midi;

    HW::screen.clear();
    HW::screen.print(0,0,"Type:");
    HW::screen.print(6,0,MidiEdit::kind[midi->kind]);
    HW::screen.print(0,1,"Note:");
    HW::screen.print(6,1,midi->note);
  }

  static bool loop() {
    switch(event) {
      case 0:
        if ( !initialized ) {
          initialized = true;
        }
        else {
        }
        break;
      case 1:
        if ( !initialized ) {
          initialized = true;
        }
        else {
        }
        break;
    };

    return false;
  }
};

DB::Midi *MidiEdit::midi;
uint8_t  MidiEdit::event           = 0;
bool     MidiEdit::initialized     = false;
String   MidiEdit::kind[NUM_KINDS] = {
  "None",
  "Note",
  "CC",
  "PC/BANK"
};


#endif
