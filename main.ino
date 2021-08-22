#include "Includes.h"

#ifndef ALT_PROGRAM
#ifndef RESET_EEP_PROGRAM

// Definitions
#define E_MAIN         0
#define E_SETTINGS     1
#define E_FSW_SETTINGS 2


// Variables
// preset_id and preset_submenu are in includes.h
Menu     m;
MenuHost *mh_p = nullptr;

void setup() {
  HW::setup();

  // Load up preset and footswitches from eeprom

  preset_p  = new Preset;
  fsw_p     = new Footswitch[NUM_FSW_PER_PRESET];

  *preset_p = DB::preset_at(preset_id);
  for (int i=0; i<NUM_FSW_PER_PRESET; i++)
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
        HW::screen.print(10,1, String("MENU ") + String(preset_submenu+1));

        // Setup footswitches
        for (int i=0; i<NUM_FSW; i++) {
          int j = (NUM_FSW * preset_submenu) + i;

          HW::btns.at(i)->set_press_type(fsw_p[j].press_type);
          HW::leds.at(i)->set( DB::color_at( fsw_p[j].colors[fsw_p[j].state] ) );
        }
      }

      else {
        for (int i=0; i<NUM_FSW; i++) {
          int j = (NUM_FSW * preset_submenu) + i;

          if ( HW::btns.at(i)->is_pressed() ) {
            fsw_p[j].increase_state();
            HW::leds.at(i)->set( DB::color_at( fsw_p[j].colors[fsw_p[j].state] ) );
          }
          else if ( HW::btns.at(i)->is_long_pressed() ) {}
        }

        if ( HW::knob.is_long_pressed() ) m.jump_to(E_SETTINGS);
      }
      break;

    case E_SETTINGS:
      if ( m.not_initialized() ) {
        mh_p = new MenuHost;
        mh_p->setup(EEP_SUBMENU_PRESET);
        HW::leds.set(0,0,0);
      }
      else {
        if ( mh_p->loop() ) {
          m.jump_to(E_MAIN);
          CLRPTR(mh_p);
        }
        else {
          if ( mh_p->m.e() == 0 ) { // If on Preset Menu
            for (int i=0; i<NUM_FSW; i++) {
              int j = (NUM_FSW * preset_submenu) + i;

              if ( HW::btns.at(i)->is_pressed() ) {
                fsw_selected       = j;
                fsw_selected_state = fsw_p[j].state;
                m.jump_to(E_FSW_SETTINGS);
              }
            }
          }
        }
      }
      break;

    case E_FSW_SETTINGS:
      if ( m.not_initialized() ) {
        *mh_p = MenuHost();
        mh_p->setup(EEP_SUBMENU_FSW);
        mh_p->change_title( String( "FSW" + String(fsw_selected+1) + " S" + String(fsw_selected_state+1) + " M" + String(preset_submenu+1) ).c_str() );

        HW::leds.set(0,0,0);
        HW::leds.at(fsw_selected)->set( DB::color_at( fsw_p[fsw_selected].colors[fsw_selected_state] ) );
      }
      else {
        if ( mh_p->loop() ) {
          m.jump_to(E_MAIN);
          CLRPTR(mh_p);
        }
        else {
          if ( mh_p->m.e() == 0 ) { // If on Preset Menu
            for (int i=0; i<NUM_FSW; i++) {
              int j = (NUM_FSW * preset_submenu) + i;

              if ( HW::btns.at(i)->is_pressed() ) {
                if ( fsw_selected == j ) {
                  fsw_selected_state = ROTATE(fsw_selected_state+1, 0, 3);
                }
                else {
                  fsw_selected       = j;
                  fsw_selected_state = fsw_p[j].state;
                }
                m.reinitialize();
              }
            }
          }
        }
      }
      break;
  };

}

#undef E_MAIN
#undef E_SETTINGS
#undef E_FSW_SETTINGS

#endif
#endif


#ifdef ALT_PROGRAM
/* For testing random stuff */

Menu m;  // NEEDED

void setup() {
  HW::setup();  // NEEDED
  HW::screen.clear();

  pedal_param_p  = new PedalParam();
  /*memcpy(pedal_p->name, "ADAM        ", STR_LEN_MAX);*/
  /*pedal_p->channel = 10;*/
  /*DB::pedal_save(0, pedal_p);*/
}

void loop() {
  HW::loop();  // NEEDED

  if ( m.not_initialized() ) {
    for (int i=0; i<10; i++) {
      *pedal_param_p = DB::preset_param_at(preset_id, i);
      HW::screen.print(0,0, "pedal");
      HW::screen.print(0,1, "param");

      HW::screen.print(15,0, pedal_param_p->pedal);
      HW::screen.print(15,1, pedal_param_p->param);

      delay(1000);
    }
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
  HW::screen.clear();
  HW::screen.print(0,0, "DONE!");
  HW::screen.print(0,1, String("LAST SECT:") + String(EEP_START_OPTS));

#ifndef EEP_RESET
  HW::screen.clear();
  HW::screen.print(0,0, "FORGOT EEP_RESET");
#endif
}

void loop() {}
#endif
