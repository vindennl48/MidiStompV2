/*
 * Takes in a Menu object and creates menu from that object.
 * We need the following data to know how to create the menu:
 *   - start_addr of loop
 *   - max number of options in loop
 *   - size of options to iterate over
 *   - what to do once the user selects an option
 *     - If result is another menu, then add the new menu-object
 *       to this menu struct and run again.
 *
 * Another variation is going to be just returning an unsigned int
 * value of what is selected.  This is for FSW Params to select pedal
 * and pedal feature ID's.
 * */

// PRIVATE
#define E_MAIN           0
#define E_TEXT_EDIT      1
#define E_VALUE_EDIT     2
#define E_CONFIRM        3
#define E_COLOR_EDIT     4
#define E_MIDI_TYPE_EDIT 5
// --

struct MenuSystem {
  Nav     n;
  uint16_t  menu_addr = 0;

  uint16_t get_start_addr() {
    if ( alt_start_addr ) return alt_start_addr;
    return Menu::get_start_addr(menu_addr);
  }

  void setup(uint16_t menu_addr, uint8_t custom_title=false) {
    // Reset the navigation helper
    n.reset();

    // Update the menu address
    this->menu_addr = menu_addr;

    // Reset alt_start_addr
    alt_start_addr = 0;

    // If callback_setup_id > 0, Run callback
    uint8_t callback_setup_id = Menu::get_callback_setup_id(menu_addr);
    if ( callback_setup_id ) get_callback( callback_setup_id )();

    // Check parents list if last addr is not in the menu options list
    if ( !IS_IN_LIST(get_start_addr(), Menu::get_num_options(menu_addr), Menu::get_size(menu_addr), GET_ACTIVE_PARENT) ) {
      // If it's not, then set new parent addr as the start_addr of menu struct
      SET_NEW_PARENT(get_start_addr());
    }

    if ( !custom_title ) {
      // Set the first text buffer with the name of the menu
      Menu::get_name(menu_addr, TXT_BUF_1);
    }

    // Write the title of menu to the LCD
    lcd.clear();
    PRINT_NLINE(0,0, "::");
    PRINT(2,0, text[TXT_BUF_1]);
    PRINT(2,1, ">");  // Just in case we need it, if not it will get rewritten
  }

  uint8_t loop() {
    switch(n.e()) {
      case E_MAIN:
        {
          if ( n.not_init() ) {
            // Grab the first 13 bytes to display name, if no name in selected struct, callback must be used
            eReadBlock(GET_ACTIVE_PARENT, (uint8_t*)text[TXT_BUF_2], TEXT_SZ);

            // Check if current parent addr is in M_OPTIONS partition
            if ( !IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
              // If no, print ID# of selection, name of option (if custom) must come from callback
              uint8_t current_id = GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_addr)) + 1;
              PRINT(0,1, "   .");
              if      ( current_id <  10  ) PRINT(2,1, current_id);
              else if ( current_id <  100 ) PRINT(1,1, current_id);
              else                          PRINT(0,1, current_id);
            }

            // If callback_run_id > 0, Run callback
            uint8_t callback_run_id = Menu::get_callback_run_id(menu_addr);
            if ( callback_run_id ) get_callback( callback_run_id )();

            // print TXT_BUF_2 to the LCD screen
            PRINT_NLINE(4,1, text[TXT_BUF_2]);

#ifdef DISPLAY_DEBUG
            DEBUG("alt_start_addr: ", alt_start_addr);
            DEBUG("parents_used:   ", parents_used);
            Serial.print("Parents Active: ");
            for (uint8_t i=0; i<NUM_PARENTS_MAX; i++) {
              Serial.print(String((parents_used & 1<<i) > 0 ? 1 : 0) + ", ");
            }
            Serial.println("");
            Serial.print("Parents Addr: ");
            for (uint8_t i=0; i<NUM_PARENTS_MAX; i++) {
              Serial.print(String(parents[i]) + ", ");
            }
            Serial.println("");
#endif

          }
          else {
            if ( knob.is_left() ) {
              int result = (int)GET_ACTIVE_PARENT - (int)Menu::get_size(menu_addr);
              if ( result >= (int)get_start_addr() ) {
                SET_ACTIVE_PARENT((uint16_t)result);
                n.reinit();
              }
            }
            else if ( knob.is_right() ) {
              uint16_t result = GET_ACTIVE_PARENT + Menu::get_size(menu_addr);
              uint16_t end    = get_start_addr() + Menu::get_num_options(menu_addr) * Menu::get_size(menu_addr);
              if ( result < end ) {
                SET_ACTIVE_PARENT(result);
                n.reinit();
              }
            }
            else if ( knob.is_pressed() ) {
              // If option is in M_OPTIONS partition
              if ( IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
                // If option result is RESULT_MENU
                if ( Option::get_result(GET_ACTIVE_PARENT) == RESULT_MENU ) {
                  // If callback_run_id > 0, Run callback
                  uint8_t callback_id = Option::get_callback_id(GET_ACTIVE_PARENT);
                  if ( callback_id ) get_callback( callback_id )();

                  // Reload MenuSystem with new menu_addr
                  uint16_t new_menu_addr = Option::get_menu_addr(GET_ACTIVE_PARENT);
                  if ( new_menu_addr == MENU_MAIN ) return true;
                  setup( new_menu_addr );
                }
                else if ( Option::get_result(GET_ACTIVE_PARENT) == RESULT_TEXT_EDIT ) {
                  n.jump_to(E_TEXT_EDIT);
                }
                else if ( Option::get_result(GET_ACTIVE_PARENT) == RESULT_COLOR_EDIT ) {
                  n.jump_to(E_COLOR_EDIT);
                }
                else if ( Option::get_result(GET_ACTIVE_PARENT) == RESULT_CONFIRM ) {
                  n.jump_to(E_CONFIRM);
                }
                else {
                  n.jump_to(E_VALUE_EDIT);
                }
              }
              else {
                // If callback_setup_id > 0, Run callback
                uint16_t callback_save_id = Menu::get_callback_save_id(menu_addr);
                if ( callback_save_id ) {
                  uint8_t result = get_callback( callback_save_id )();
                  if ( result == CS_VALUE_EDIT_JUMP ) n.jump_to(E_VALUE_EDIT);
                  else setup( Menu::get_forward_addr(menu_addr) );
                }
                else {
                  setup( Menu::get_forward_addr(menu_addr) );
                }
              }
            }
            else if ( knob.is_long_pressed() ) {
              deactivate_active_parent();
              uint16_t return_addr = Menu::get_return_addr(menu_addr);
              if ( return_addr == MENU_MAIN ) return true;
              setup( return_addr );
            }
          }
        }
        break;

      case E_TEXT_EDIT:
        if ( n.not_init() ) {
          text_edit.setup();
        }
        else {
          if ( text_edit.loop() ) {
            // Go to the next menu item selected by this option
            uint16_t new_menu_addr = Option::get_menu_addr(GET_ACTIVE_PARENT);
            if ( new_menu_addr == MENU_MAIN ) return true;
            setup( new_menu_addr );
          }
        }
        break;

      case E_VALUE_EDIT:
        {
          uint16_t new_menu_addr;

          if ( n.not_init() ) {
            if ( !IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
              value_edit.setup(RESULT_VALUE_EDIT);
            }
            else {
              value_edit.setup( Option::get_result(GET_ACTIVE_PARENT) );
            }
          }
          else {
            if ( value_edit.loop() ) {
              // Go to the next menu item selected by this option
              if ( !IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
                // go back to the same menu if it wasnt an option struct
                new_menu_addr = menu_addr;
              }
              else {
                new_menu_addr = Option::get_menu_addr(GET_ACTIVE_PARENT);
                if ( new_menu_addr == MENU_MAIN ) return true;
              }
              setup( new_menu_addr );
            }
          }
        }
        break;

      case E_CONFIRM:
        {
          if ( n.not_init() ) {
            confirm.setup();
          }
          else {
            uint8_t result = confirm.loop();

            if ( result ) {
              if ( result == LTRUE ) {
                // If callback_run_id > 0, Run callback
                uint8_t callback_id = Option::get_callback_id(GET_ACTIVE_PARENT);
                if ( callback_id ) get_callback( callback_id )();
              }

              // Reload MenuSystem with new menu_addr
              uint16_t new_menu_addr = Option::get_menu_addr(GET_ACTIVE_PARENT);
              if ( new_menu_addr == MENU_MAIN ) return true;
              setup( new_menu_addr );
            }
          }
        }
        break;

      case E_COLOR_EDIT:
        {
          if ( n.not_init() ) {
            color_edit.setup();
          }
          else {
            if ( color_edit.loop() ) {
              uint16_t new_menu_addr = Option::get_menu_addr(GET_ACTIVE_PARENT);
              if ( new_menu_addr == MENU_MAIN ) return true;
              setup( new_menu_addr );
            }
          }
        }
        break;
    };
    
    return false;
  }
} menu;

#undef E_MAIN
#undef E_TEXT_EDIT
#undef E_VALUE_EDIT
#undef E_CONFIRM
#undef E_COLOR_EDIT
#undef E_MIDI_TYPE_EDIT
