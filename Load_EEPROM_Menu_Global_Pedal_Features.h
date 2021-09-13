#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

// Loop thru available pedals to edit
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "FEATURES    ", TEXT_SZ);
menu.num_options       = NUM_FEATURES_PER_PEDAL;
menu.start_addr        = M_FEATURES;  // Need to set in callback
menu.size              = sizeof(Feature);
menu.return_addr       = MENU_PEDAL;
menu.forward_addr      = MENU_FEATURE;
menu.callback_setup_id = F_FEATURES_SETUP; // setting alt_start_addr here
write_data<Menu>(&menu, MENU_FEATURES);

  address               = MENU_FEATURE;
  option_partition_addr = M_OPTIONS;
  num_options_per_menu  = NUM_OPTIONS_PER_MENU;
  menu = Menu();
  //-------------------------------------------------------------------------------- 
  memcpy(menu.name, "FEATURE     ", TEXT_SZ);
  menu.num_options = 3;
  menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
  menu.return_addr = MENU_FEATURES;
  write_data<Menu>(&menu, address);

    address = menu.start_addr + ( 0 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "NAME        ", TEXT_SZ);
    option.result    = RESULT_TEXT_EDIT;
    option.menu_addr = MENU_FEATURE;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 1 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "TYPE        ", TEXT_SZ);
    option.result    = RESULT_MIDI_TYPE_EDIT;
    option.menu_addr = MENU_FEATURE;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 2 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "PITCH       ", TEXT_SZ);
    option.result    = RESULT_VALUE_EDIT;
    option.menu_addr = MENU_FEATURE;
    write_data<Option>(&option, address);


#endif
#endif
