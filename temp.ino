#include "Includes.h"

// Definitions
#define E_MAIN     0
#define E_SETTINGS 1

char phrase[STR_LEN_MAX];
uint8_t x = 1;
uint8_t menu[7] = {
  EEPROM_TEXT_SETTINGS,
  EEPROM_TEXT_SAVE,
  EEPROM_TEXT_NAME,
  EEPROM_TEXT_PARAMS,
  EEPROM_TEXT_COPY,
  EEPROM_TEXT_RESET,
  EEPROM_TEXT_GLOBAL
};


// Variables
Menu m;

Preset     preset;
Footswitch fsw[NUM_FSW];

void setup() {
  HW::setup();

  // Load up preset and footswitches from eeprom
  /*reset_eeprom();*/
  /*load_preset();*/

  fsw[2].mode = FSW_MODE_CYCLE;
}

void loop() {
  HW::loop();

  switch( m.e() ) {
    case E_MAIN:
      if ( m.not_initialized() ) {
        // Setup screen
        HW::screen.clear();
        HW::screen.print(0,0, preset.name);

        // Setup footswitches
        for (int i=0; i<NUM_FSW; i++) {
          if ( fsw[i].mode == FSW_MODE_ONESHOT ) HW::btns.at(i)->set_press_type(PRESS_TYPE_DOWN);
          else                                   HW::btns.at(i)->set_press_type(PRESS_TYPE_UP);

          HW::leds.at(i)->set( DB::color_at( fsw[i].colors[fsw[i].state] ) );
        }
      }

      else {
        for (int i=0; i<NUM_FSW; i++) {
          if ( HW::btns.at(i)->is_pressed() ) {
            fsw[i].increase_state();
            HW::leds.at(i)->set( DB::color_at( fsw[i].colors[fsw[i].state] ) );
          }
          else if ( HW::btns.at(i)->is_long_pressed() ) {}
        }

        if ( HW::knob.is_long_pressed() ) m.jump_to(E_SETTINGS);
      }
      break;

    case E_SETTINGS:
      if ( m.not_initialized() ) {
        for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);

        DB::text_at(phrase, (x-1));
        HW::screen.clear();
        if ( x == 1 )  HW::screen.print(0,0, "::");
        else           HW::screen.print(0,0, "  ");
        HW::screen.print(2,0, phrase);

        DB::text_at(phrase, x);
        HW::screen.print(0,1, ">");
        HW::screen.print(2,1, phrase);
      }
      else {
        if      ( HW::knob.is_left()  ) { x = CONTAIN(x-1, 1, 6); m.reinitialize(); }
        else if ( HW::knob.is_right() ) { x = CONTAIN(x+1, 1, 6); m.reinitialize(); }
        else if ( HW::knob.is_long_pressed() ) { x = 1; m.jump_to(E_MAIN); }
      }
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
