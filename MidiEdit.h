#ifndef MIDI_EDIT_H
#define MIDI_EDIT_H

// Definitions
#define NUM_KINDS 4

#include "Hardware.h"
#include "Menu.h"

#define E_SELECT      0
#define E_CHANGE_TYPE 1
#define E_CHANGE_NOTE 2

#define C_TYPE   0
#define C_NOTE   1
#define C_SAVE   2
#define C_CANCEL 3

struct MidiEdit {
  Menu m;
  uint8_t cursor = 0;

  void cursor_up()   { cursor += 1; if ( cursor > 3 ) cursor = 3; }
  void cursor_down() { if ( cursor > 0 ) cursor -= 1; }
  void set_cursor() {
    switch(cursor) {
      case C_TYPE:
        HW::screen.set_cursor(5,0);
        break;
      case C_NOTE:
        HW::screen.set_cursor(5,1);
        break;
      case C_SAVE:
        HW::screen.set_cursor(15,0);
        break;
      case C_CANCEL:
        HW::screen.set_cursor(15,1);
        break;
    };
  }

  bool loop(Midi *midi) {
    switch(m.e()) {
      case E_SELECT:
        if ( m.not_initialized() ) {
          HW::screen.blink(true);
          HW::screen.highlight(true);

          HW::screen.clear();
          HW::screen.print(0,0,"TYPE:" + midi->get_kind_str());
          HW::screen.print(12,0,"SAVE");
          HW::screen.print(0,1,"NOTE:" + String(midi->note));
          HW::screen.print(10,1,"CANCEL");

          set_cursor();
        }
        else if ( HW::knob.is_left() )         { cursor_down(); m.jump_to(E_SELECT); }
        else if ( HW::knob.is_right() )        { cursor_up();   m.jump_to(E_SELECT); }
        else if ( HW::knob.is_pressed() )      {
          if      ( cursor == C_TYPE )   m.jump_to(E_CHANGE_TYPE);
          else if ( cursor == C_NOTE )   m.jump_to(E_CHANGE_NOTE);
          else if ( cursor == C_SAVE )   { SET_MIDI(midi); return m.back(); }
          else if ( cursor == C_CANCEL ) return m.back();
        }
        else if ( HW::knob.is_long_pressed() ) { return m.back(); }
        break;

      case E_CHANGE_TYPE:
        if ( m.not_initialized() ) {
          HW::screen.blink(false);
          HW::screen.print_with_nline(0,0,"TYPE:" + midi->get_kind_str());
          HW::screen.print(12,0,"SAVE");
          set_cursor();
        }
        else if ( HW::knob.is_left() )    { midi->kind_down(); m.jump_to(E_CHANGE_TYPE); }
        else if ( HW::knob.is_right() )   { midi->kind_up(); m.jump_to(E_CHANGE_TYPE); }
        else if ( HW::knob.is_pressed() ) { m.jump_to(E_SELECT); }
        break;

      case E_CHANGE_NOTE:
        if ( m.not_initialized() ) {
          HW::screen.blink(false);
          HW::screen.print_with_nline(0,1,"NOTE:" + String(midi->note));
          HW::screen.print(10,1,"CANCEL");
          set_cursor();
        }
        else if ( HW::knob.is_left() )    { midi->note_down(); m.jump_to(E_CHANGE_NOTE); }
        else if ( HW::knob.is_right() )   { midi->note_up(); m.jump_to(E_CHANGE_NOTE); }
        else if ( HW::knob.is_pressed() ) { m.jump_to(E_SELECT); }
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
