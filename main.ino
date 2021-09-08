#include "Includes.h"

#ifndef ALT_PROGRAM
#ifndef LOAD_EEPROM

// PRIVATE
#define E_SETUP        0
#define E_RESET_SCREEN 1
#define E_MAIN         2
#define E_SETTINGS     3
#define E_FSW_SETTINGS 4
// --

Nav n;

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  switch(n.e()) {
    case E_SETUP:
      {
        // First thing we have to do is load up the preset address in parents
        clear_all_parents();
        SET_NEW_PARENT( GET_PARENT(M_PRESETS, preset_id, sizeof(Preset)) );

        // Next, we have to load the footswitches
        uint16_t start_fsw_addr = GET_CHILD(M_FSW, preset_id, 0, sizeof(Footswitch), NUM_FSW_PER_PRESET );
        for (uint16_t i=start_fsw_addr, j=0; j<NUM_FSW_PER_PRESET; i+=sizeof(Footswitch), j++) {
          fsw[j] = read_data<Footswitch>(i);
        }

        // Reset the submenu
        submenu_id = 0;

        n.jump_to(E_RESET_SCREEN);
      }
      break;

    case E_RESET_SCREEN:
        // Lastly, lets reset the main screen
        lcd.clear();
        Preset::get_name(parents[0], TXT_BUF_1);
        PRINT(0,0, text[TXT_BUF_1]);
        PRINT(0,1, String("P.") + String( GET_ID_FROM_ADDR(M_PRESETS, parents[0], sizeof(Preset))+1 ));
        PRINT(10,1, String("MENU ") + String(submenu_id+1));

        n.jump_to(E_MAIN);
      break;

    case E_MAIN:
      if ( n.not_init() ) {
        // Setup Buttons for Footswitches
        for (uint8_t i=submenu_id*NUM_FSW_PER_SUBMENU, j=0; j<NUM_FSW_PER_SUBMENU; i++, j++) {
          btns[j].set_press_type(fsw[i].press_type);
          if ( fsw[i].mode != FSW_MODE_OFF ) {
            // need to load selected FSW colors
            /*leds[j].set();*/
          }
          else {
            leds[j].set(0,0,0);
          }
        }
      }
      else {
        for (uint8_t i=0; i<NUM_FSW_PER_SUBMENU; i++) {
          if ( btns[i].is_pressed() ) {}
          else if ( btns[i].is_long_pressed() ) {}
        }

        if ( knob.is_long_pressed() ) {
          n.jump_to(E_SETTINGS);
        }
        else if ( knob.is_left() ) {}
        else if ( knob.is_right() ) {}
      }
      break;

    case E_SETTINGS:
      if ( n.not_init() ) {
        menu.setup(MENU_PRESET);
      }
      else {
        if ( menu.loop() ) n.jump_to(E_RESET_SCREEN);
      }
      break;
  };

}

#undef E_SETUP
#undef E_RESET_SCREEN
#undef E_MAIN
#undef E_SETTINGS
#undef E_FSW_SETTINGS

#endif
#endif
