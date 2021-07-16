#include "Includes.h"

// Definitions
#define E_MAIN     0
#define E_SETTINGS 1


// Variables
// Preset and fsw are in includes.h
Menu    m;
uint8_t submenu = 0;

void setup() {
  HW::setup();

  // Load up preset and footswitches from eeprom
  reset_eeprom();
  /*load_preset();*/

  fsw[submenu][2].mode = FSW_MODE_CYCLE;
  strcpy(preset.name, "PCORE       ");
}

void loop() {
  HW::loop();

  switch( m.e() ) {
    case E_MAIN:
      if ( m.not_initialized() ) {
        // Setup screen
        HW::screen.clear();
        HW::screen.print(0,0, preset.name);
        HW::screen.print(10,1, "MENU 1");

        // Setup footswitches
        for (int i=0; i<NUM_FSW; i++) {
          if ( fsw[submenu][i].mode == FSW_MODE_ONESHOT ) HW::btns.at(i)->set_press_type(PRESS_TYPE_DOWN);
          else                                   HW::btns.at(i)->set_press_type(PRESS_TYPE_UP);

          HW::leds.at(i)->set( DB::color_at( fsw[submenu][i].colors[fsw[submenu][i].state] ) );
        }
      }

      else {
        for (int i=0; i<NUM_FSW; i++) {
          if ( HW::btns.at(i)->is_pressed() ) {
            fsw[submenu][i].increase_state();
            HW::leds.at(i)->set( DB::color_at( fsw[submenu][i].colors[fsw[submenu][i].state] ) );
          }
          else if ( HW::btns.at(i)->is_long_pressed() ) {}
        }

        if ( HW::knob.is_long_pressed() ) m.jump_to(E_SETTINGS);
      }
      break;

    case E_SETTINGS:
      if ( Settings::loop() ) m.jump_to(E_MAIN);
      break;
  };

}

#undef E_MAIN
#undef E_SETTINGS




// Brainstorm

#ifdef BRAINSTORM

// To start out our eeprom journey, we will use the internal 1,024 bytes.
// This will eventually switch to the 65,536 bytes eeprom chip.

EEPROM Map

Colors:    Amount:14 | Unit Size:16 | Size:224 | Start:0
Pedals:    Amount:2  | Unit Size:14 | Size:28  | Start:225
Params:    Amount:20 | Unit Size:14 | Size:280 | Start:254
FSwitches: Amount:32 | Unit Size:8  | Size:256 | Start:535
Presets:   Amount:2  | Unit Size:14 | Size:28  | Start:792
Menu Itms: Amount:15 | Unit Size:13 | Size:195 | Start:821 End:1016

#endif
