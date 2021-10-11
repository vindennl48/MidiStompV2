#include "Main_Events.h"
#include "Nav.h"
#include "Hardware.h"
#include "Components.h"

uint8_t is_change_preset = false;

void e_main(Nav *n) {
  if ( n->not_init() ) {
    preset.print_main_screen();
    preset.update_colors();
    if ( is_change_preset ) HW::screen.print(15, 0, "<");
  }
  else {

    // ENTER SETTINGS
    if ( HW::knob.is_pressed() || HW::knob.is_long_pressed() ) {
      if ( HW::knob.is_pressed() ) {
        is_change_preset = true;
        n->jump_to(E_MAIN);
      }
      if ( HW::knob.is_long_pressed() ) {
        if ( is_change_preset ) {
          is_change_preset = false;
          n->jump_to(E_MAIN);
        }
        else n->jump_to(E_SETTINGS);
      }
    }

    // CHANGE PRESETS
    else if ( (HW::knob.is_left() || HW::knob.is_right()) & is_change_preset ) {
      uint8_t new_id = preset.id;
      if ( HW::knob.is_left() ) {
        new_id = CONTAIN((int)(preset.id-1), (int)0, (int)NUM_PRESETS-1);
      }
      if ( HW::knob.is_right() ) {
        new_id = CONTAIN((int)(preset.id+1), (int)0, (int)NUM_PRESETS-1);
      }

      if ( new_id != preset.id ) {
        preset.load(new_id);
        n->jump_to(E_MAIN);
      }
    }

    else {

      // FSW PRESS
      for (int i=0; i<NUM_BTNS; i++) {
        if ( HW::btns[i].is_pressed() ) {
          if ( preset.fsw(i)->mode() == FSW_MODE_SUBMENU ) {
            n->jump_to(E_MAIN);  // Reset
          }
          else if ( preset.fsw(i)->mode() == FSW_MODE_PRESET ) {
            n->jump_to(E_MAIN);  // Reset
          }
          else {
            preset.fsw(i)->update_state();
            preset.update_colors();
          }
        }
        else if ( HW::btns[i].is_long_pressed() ) {
          if ( preset.fsw(i)->lp_mode() == FSW_MODE_SUBMENU ) {
            n->jump_to(E_MAIN);  // Reset
          }
          else if ( preset.fsw(i)->lp_mode() == FSW_MODE_PRESET ) {
            n->jump_to(E_MAIN);  // Reset
          }
          else {
            preset.fsw(i)->update_state();
            preset.update_colors();
          }
        }
      }

    }
  }
}
