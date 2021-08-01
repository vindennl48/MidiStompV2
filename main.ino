#include "Includes.h"

#ifndef ALT_PROGRAM
#ifndef RESET_EEP_PROGRAM

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
  /*load_preset();*/

  for (int i=0; i<4; i++) {
    fsw[submenu][i].mode = FSW_MODE_CYCLE;
    fsw[submenu][i].colors[0] = 0;
    fsw[submenu][i].colors[1] = 1;
    fsw[submenu][i].colors[2] = 2;
  }

  fsw[submenu][2].colors[2] = 3;
  fsw[submenu][3].colors[2] = 4;

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
      if ( m.not_initialized() ) {
        settings_p = new Settings;
      }
      else {
        if ( settings_p->loop() ) {
          m.jump_to(E_MAIN);
          CLRPTR(settings_p);
        }
      }
      break;
  };

}

#undef E_MAIN
#undef E_SETTINGS

#endif
#endif


#ifdef ALT_PROGRAM
/* For testing random stuff */

Menu     m;
ListLoop list_loop;
/*char name[STR_LEN_MAX] = "MITCH";*/

void setup() {
  HW::setup();
}

void loop() {
  HW::loop();

  if ( m.not_initialized() ) {
    list_loop.reset(EEP_START_COLORS, sizeof(Color), "COLORS", 100);
  }
  else {
    if ( list_loop.loop() ) m.reinitialize();
  }
}

#endif

#ifdef RESET_EEP_PROGRAM
/* For resetting the EEPROM */

void setup() {
  HW::setup();

  /*// RESET EEPROM*/
  HW::screen.clear();
  HW::screen.print(0,0, "RESETTING..");
  reset_eeprom();
  HW::screen.print_with_nline(0,0, "DONE!");
}

void loop() {}
#endif
