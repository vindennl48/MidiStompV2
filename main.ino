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

  *preset_p = DB::preset_at(sel_preset_id);
  for (int i=0; i<NUM_FSW_PER_PRESET; i++)
    fsw_p[i] = DB::fsw_at(sel_preset_id, i);
}

void loop() {
  HW::loop();

  switch( m.e() ) {
    case E_MAIN:
      if ( m.not_initialized() ) {
        // Setup screen
        HW::screen.clear();
        HW::screen.print(0,0, preset_p->name);
        HW::screen.print(0,1, String("P.")+String(sel_preset_id+1));
        HW::screen.print(10,1, String("MENU ") + String(sel_preset_submenu_id+1));

        // Setup footswitches
        for (int i=0; i<NUM_FSW; i++) {
          int j = (NUM_FSW * sel_preset_submenu_id) + i;

          HW::btns.at(i)->set_press_type(fsw_p[j].press_type);
          if ( fsw_p[j].mode != FSW_MODE_OFF ) {
            HW::leds.at(i)->set( DB::color_at( fsw_p[j].colors[fsw_p[j].state] ) );
          }
          else {
            HW::leds.at(i)->set(0,0,0);
          }
        }
      }
      else {
        for (int i=0; i<NUM_FSW; i++) {
          int j = (NUM_FSW * sel_preset_submenu_id) + i;

          if ( HW::btns.at(i)->is_pressed() ) {
            switch( fsw_p[j].mode ) {
              case FSW_MODE_OFF:
                break;

              case FSW_MODE_SUBMENU:
                if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
                *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + j, 0);

                sel_preset_submenu_id = pedal_param_p->velocity;

                CLRPTR(pedal_param_p);
                m.jump_to(E_MAIN);
                break;

              case FSW_MODE_PRESET:
                break;

              default:
                fsw_p[j].increase_state();
                HW::leds.at(i)->set( DB::color_at( fsw_p[j].colors[fsw_p[j].state] ) );
                break;
            };
          }
          else if ( HW::btns.at(i)->is_long_pressed() ) {
            switch( fsw_p[j].lp_mode ) {
              case FSW_MODE_OFF:
                break;

              case FSW_MODE_SUBMENU:
                HW::screen.flash();

                if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
                *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + j, 3);

                sel_preset_submenu_id = pedal_param_p->velocity;

                CLRPTR(pedal_param_p);
                m.jump_to(E_MAIN);
                break;

              default:
                HW::screen.flash();
                break;
            };
          }
        }

        if      ( HW::knob.is_long_pressed() ) { m.jump_to(E_SETTINGS); }
        else if ( HW::knob.is_left() || HW::knob.is_right() ) {
          if      ( HW::knob.is_left() )  sel_preset_id = CONTAIN(sel_preset_id-1, 0, EEP_NUM_PRESETS-1);
          else if ( HW::knob.is_right() ) sel_preset_id = CONTAIN(sel_preset_id+1, 0, EEP_NUM_PRESETS-1);

          // RELOAD NEW PRESET
          *preset_p = DB::preset_at(sel_preset_id);
          for (int i=0; i<NUM_FSW_PER_PRESET; i++)
            fsw_p[i] = DB::fsw_at(sel_preset_id, i);

          // Reset submenu
          sel_preset_submenu_id = 0;

          m.jump_to(E_MAIN);
        }
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
              int j = (NUM_FSW * sel_preset_submenu_id) + i;

              if ( HW::btns.at(i)->is_pressed() ) {
                sel_fsw_id       = j;
                sel_fsw_state_id = fsw_p[j].state;
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
        mh_p->change_title( String( "FSW" + String(sel_fsw_id+1-(NUM_FSW*sel_preset_submenu_id)) + " S" + String(sel_fsw_state_id+1) + " M" + String(sel_preset_submenu_id+1) ).c_str() );

        HW::leds.set(0,0,0);
        HW::leds.at( sel_fsw_id-(NUM_FSW*sel_preset_submenu_id) )->set( DB::color_at( fsw_p[sel_fsw_id].colors[sel_fsw_state_id] ) );
      }
      else {
        if ( mh_p->loop() ) {
          m.jump_to(E_MAIN);
          CLRPTR(mh_p);
        }
        else {
          if ( mh_p->m.e() == 0 ) { // If on Preset Menu
            for (int i=0; i<NUM_FSW; i++) {
              int j = (NUM_FSW * sel_preset_submenu_id) + i;

              if ( HW::btns.at(i)->is_pressed() ) {
                if ( sel_fsw_id == j ) {
                  sel_fsw_state_id = ROTATE(sel_fsw_state_id+1, 0, 3);
                }
                else {
                  sel_fsw_id       = j;
                  sel_fsw_state_id = fsw_p[j].state;
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

Menu m; // NEEDED

void setup() {
  HW::setup();  // NEEDED
  HW::screen.clear();

  value_edit_p = new ValueEdit(0,0,127);
}

void loop() {
  HW::loop();  // NEEDED

  switch(m.e()) {
    case 0:
      if ( value_edit_p->loop() ) m.jump_to(1);
      break;

    case 1:
      if ( m.not_initialized() ) {
        HW::screen.clear();
        HW::screen.print(0,0, "VALUE");
        HW::screen.print(0,1, String(value_edit_p->get_result()));
        delay(5000);
        m.jump_to(0);
      }
      break;
  };
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
  HW::screen.print(0,1, String("LAST SECT:") + String(EEP_END_EEPROM));

#ifndef EEP_RESET
  HW::screen.clear();
  HW::screen.print(0,0, "FORGOT EEP_RESET");
#endif
}

void loop() {}
#endif
