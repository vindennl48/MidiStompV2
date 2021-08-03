#include "Includes.h"

#ifndef ALT_PROGRAM
#ifndef RESET_EEP_PROGRAM

// Definitions
#define E_MAIN     0
#define E_SETTINGS 1


// Variables
// preset_id and fsw_submenu_id are in includes.h
Menu     m;
MenuHost *mh_p = nullptr;

void setup() {
  HW::setup();

  // Load up preset and footswitches from eeprom

  preset_p  = new Preset;
  fsw_p     = new Footswitch[NUM_FSW*NUM_SUB_MENUS];

  *preset_p = DB::preset_at(preset_id);
  for (int i=0; i<(NUM_FSW*NUM_SUB_MENUS); i++)
    fsw_p[i] = DB::fsw_at(preset_id, i);
}

void loop() {
  HW::loop();

  switch( m.e() ) {
    case E_MAIN:
      if ( m.not_initialized() ) {
        // Setup screen
        HW::screen.clear();
        HW::screen.print(0,0, preset_p->name);
        HW::screen.print(10,1, String("MENU ") + String(fsw_submenu_id+1));

        // Setup footswitches
        for (int i=0; i<NUM_FSW; i++) {
          if ( fsw_p[(NUM_FSW*fsw_submenu_id)+i].mode == FSW_MODE_ONESHOT ) HW::btns.at(i)->set_press_type(PRESS_TYPE_DOWN);
          else                                   HW::btns.at(i)->set_press_type(PRESS_TYPE_UP);

          HW::leds.at(i)->set( DB::color_at( fsw_p[(NUM_FSW*fsw_submenu_id)+i].colors[fsw_p[(NUM_FSW*fsw_submenu_id)+i].state] ) );
        }
      }

      else {
        for (int i=0; i<NUM_FSW; i++) {
          if ( HW::btns.at(i)->is_pressed() ) {
            fsw_p[(NUM_FSW*fsw_submenu_id)+i].increase_state();
            HW::leds.at(i)->set( DB::color_at( fsw_p[(NUM_FSW*fsw_submenu_id)+i].colors[fsw_p[(NUM_FSW*fsw_submenu_id)+i].state] ) );
          }
          else if ( HW::btns.at(i)->is_long_pressed() ) {}
        }

        if ( HW::knob.is_long_pressed() ) m.jump_to(E_SETTINGS);
      }
      break;

    case E_SETTINGS:
      if ( m.not_initialized() ) {
        mh_p = new MenuHost(0);
        mh_p->setup();
      }
      else {
        if ( mh_p->loop() ) {
          m.jump_to(E_MAIN);
          CLRPTR(mh_p);
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
MenuHost mh(0);

void setup() {
  HW::setup();
  mh.setup();
}

void loop() {
  HW::loop();
  mh.loop();
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
  HW::screen.clear();
  HW::screen.print(0,0, "DONE!");

#ifndef EEP_RESET
  HW::screen.clear();
  HW::screen.print(0,0, "FORGOT EEP_RESET");
#endif
}

void loop() {}
#endif
