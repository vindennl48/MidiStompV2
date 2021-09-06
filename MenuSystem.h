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
#define E_MAIN      0
#define E_TEXT_EDIT 1
// --

struct MenuSystem {
  Nav     n;
  uint8_t  menu_id = 0;

  uint16_t get_start_addr() {
    if ( alt_start_addr ) return alt_start_addr;
    return Menu::get_start_addr(menu_id);
  }

  void setup(uint8_t menu_id) {
    // Reset the navigation helper
    n.reset();

    // Update the menu id
    this->menu_id = menu_id;

    // Reset alt_start_addr
    alt_start_addr = 0;

    // Need some way to loop this until callback returns true
      // If callback_setup_id > 0, Run callback
      if ( Menu::get_callback_setup_id(menu_id) )
        get_callback(Menu::get_callback_setup_id(menu_id))();

    // Check parents list if last addr is not in the menu options list
    if ( !IS_IN_LIST(get_start_addr(), Menu::get_num_options(menu_id), Menu::get_size(menu_id), GET_ACTIVE_PARENT) ) {
      // If it's not, then set new parent addr as the start_addr of menu struct
      SET_NEW_PARENT(get_start_addr());
    }

    // Set the first text buffer with the name of the menu
    Menu::get_name(menu_id, TXT_BUF_1);

    // Write the title of menu to the LCD
    lcd.clear();
    PRINT_NLINE(0,0, "::");
    PRINT(2,0, text[TXT_BUF_1]);
    PRINT(2,1, ">");  // Just in case we need it, if not it will get rewritten
  }

  uint8_t loop() {
    switch(n.e()) {
      case E_MAIN:
        if ( n.not_init() ) {
          // Grab the first 13 bytes to display name, if no name in selected struct, callback must be used
          eReadBlock(GET_ACTIVE_PARENT, (uint8_t*)text[TXT_BUF_2], TEXT_SZ);

          // Check if current parent addr is in M_OPTIONS partition
          if ( !IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
            // If no, print ID# of selection, name of option (if custom) must come from callback
            uint8_t current_id = GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))+1;
            PRINT(0,1, "   .");
            if      ( current_id <  10  ) PRINT(2,1, current_id);
            else if ( current_id <  100 ) PRINT(1,1, current_id);
            else                          PRINT(0,1, current_id);
          }

          // If callback_run_id > 0, Run callback
          if ( Menu::get_callback_run_id(menu_id) )
            get_callback(Menu::get_callback_run_id(menu_id))();

          // print TXT_BUF_2 to the LCD screen
          PRINT_NLINE(4,1, text[TXT_BUF_2]);
        }
        else {
          if ( knob.is_left() ) {
            if ( GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id)) > 0 ) {
              SET_ACTIVE_PARENT(GET_ACTIVE_PARENT - Menu::get_size(menu_id));
              n.reinit();
            }
          }
          else if ( knob.is_right() ) {
            if ( GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))+(uint8_t)1 < Menu::get_num_options(menu_id) ) {
              SET_ACTIVE_PARENT(GET_ACTIVE_PARENT + Menu::get_size(menu_id));
              n.reinit();
            }
          }
          else if ( knob.is_pressed() ) {
            // If option is in M_OPTIONS partition
            if ( IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
              uint8_t option_id = GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id));

              // If option result is RESULT_MENU
              if ( Option::get_result(menu_id, option_id) == RESULT_MENU ) {
                // If callback_run_id > 0, Run callback
                if ( Option::get_callback_id(menu_id, GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))) )
                  get_callback( Option::get_callback_id(menu_id, GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))) )();

                // Reload MenuSystem with new menu_id
                setup( Option::get_menu_id(menu_id, GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))) );
              }
              else if ( Option::get_result(menu_id, option_id) == RESULT_TEXT_EDIT ) {
                n.jump_to(E_TEXT_EDIT);
              }
            }
            else {
              // We need to resort to the Menu struct's forward_id to know what menu to navigate to
              setup( Menu::get_forward_id(menu_id) );
            }
          }
          else if ( knob.is_long_pressed() ) {
            deactivate_active_parent();
            if ( Menu::get_return_id(menu_id) == MENU_MAIN ) return true;
            setup( Menu::get_return_id(menu_id) );
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
            setup( Option::get_menu_id(menu_id, GET_ID_FROM_ADDR(get_start_addr(), GET_ACTIVE_PARENT, Menu::get_size(menu_id))) );
          }
        }
        break;
    };
    
    return false;
  }
} menu;

#undef E_MAIN
#undef E_TEXT_EDIT
