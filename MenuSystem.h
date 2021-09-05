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

struct MenuSystem {
  Nav     n;
  uint8_t menu_id = 0;

  void setup(uint8_t menu_id) {
    // Reset the navigation helper
    n.reset();

    // Update the menu id
    this->menu_id = menu_id;

    // Check parents list if last addr is not in the menu options list
    if ( !IS_IN_LIST(Menu::get_start_addr(menu_id), Menu::get_num_options(menu_id), Menu::get_size(menu_id), GET_ACTIVE_PARENT) ) {
      // If it's not, then set new parent addr as the start_addr of menu struct
      SET_NEW_PARENT(Menu::get_start_addr(menu_id));
    }

    // Set the first text buffer with the name of the menu
    Menu::get_name(menu_id, TXT_BUF_1);

    // Need some way to loop this until callback returns true
      // If callback_setup_id > 0, Run callback
      if ( Menu::get_callback_setup_id(menu_id) )
        get_callback(Menu::get_callback_setup_id(menu_id))();

    // Write the title of menu to the LCD
    PRINT_NLINE(0,0, "::");
    PRINT(2,0, text[TXT_BUF_1]);
  }

  uint8_t loop() {
    if ( n.not_init() ) {
      // Check if current parent addr is in M_OPTIONS partition
      if ( IS_IN_PARTITION_OPTIONS(GET_ACTIVE_PARENT) ) {
        // If yes, copy the name of the option to TXT_BUF_2
        Option::get_name(menu_id, GET_ID_FROM_ADDR(Menu::get_start_addr(menu_id), GET_ACTIVE_PARENT, OPTION_SZ), (uint8_t)TXT_BUF_2);
        // and print carrot selector >
        PRINT_NLINE(2,1, ">");
      }
      else {
        // If no, print ID# of selection, name of option must come from callback
        PRINT_NLINE(0,1, GET_ID_FROM_ADDR(Menu::get_start_addr(menu_id), GET_ACTIVE_PARENT, OPTION_SZ)+1);
        PRINT(3,1, ".");
      }

      // If callback_run_id > 0, Run callback
      if ( Menu::get_callback_run_id(menu_id) )
        get_callback(Menu::get_callback_run_id(menu_id))();

      // print TXT_BUF_2 to the LCD screen
      PRINT_NLINE(4,1, text[TXT_BUF_2]);
    }
    else {
      if ( knob.is_left() ) {
      }
      else if ( knob.is_right() ) {
      }
      else if ( knob.is_pressed() ) {
      }
      else if ( knob.is_long_pressed() ) {
      }
    }
    
    return false;
  }
} menu;
