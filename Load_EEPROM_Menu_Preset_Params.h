#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

// Loop thru available preset params to edit from the selected preset
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "PRST PARAMS ", TEXT_SZ);
menu.num_options       = NUM_PRESET_PARAMS_PER_PRESET;
menu.start_addr        = 0;                     // need to set this in callback
menu.size              = sizeof(Parameter);
menu.return_addr       = MENU_PRESET;
menu.forward_addr      = MENU_PRESET_PARAM;
menu.callback_setup_id = F_PRESET_PARAMS_SETUP; // setting alt_start_addr here
menu.callback_run_id   = F_PRESET_PARAMS_RUN;   // setting alt_start_addr here
write_data<Menu>(&menu, MENU_PRESET_PARAMS);

  address               = MENU_PRESET_PARAM;
  option_partition_addr = M_OPTIONS;
  num_options_per_menu  = NUM_OPTIONS_PER_MENU;
  menu = Menu();
  //-------------------------------------------------------------------------------- 
  memcpy(menu.name, "PRST PARAM  ", TEXT_SZ);
  menu.num_options = 3;
  menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
  menu.return_addr = MENU_PRESET_PARAMS;
  write_data<Menu>(&menu, address);

    address = menu.start_addr + ( 0 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "PEDAL       ", TEXT_SZ);
    option.result    = RESULT_MENU;
    option.menu_addr = MENU_PRESET_PARAM_PEDAL;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 1 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "FEATURE     ", TEXT_SZ);
    option.result    = RESULT_MENU;
    option.menu_addr = MENU_PRESET_PARAM_FEATURE;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 2 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "VELOCITY    ", TEXT_SZ);
    option.result    = RESULT_VALUE_EDIT;
    option.menu_addr = MENU_PRESET_PARAM;
    write_data<Option>(&option, address);

    // MENU 0, PEDAL CHOOSE
      // Loop thru available pedals
      menu = Menu();
      //-------------------------------------------------------------------------------- 
      memcpy(menu.name, "PEDALS      ", TEXT_SZ);
      menu.num_options      = NUM_PEDALS;
      menu.start_addr       = M_PEDALS;
      menu.size             = sizeof(Pedal);
      menu.return_addr      = MENU_PRESET_PARAM;
      menu.forward_addr     = MENU_PRESET_PARAM;
      menu.callback_save_id = F_PRESET_PARAM_PEDAL_SAVE;
      write_data<Menu>(&menu, MENU_PRESET_PARAM_PEDAL);

    // FEATURE CHOOSE
      // Loop thru available pedals
      menu = Menu();
      //-------------------------------------------------------------------------------- 
      memcpy(menu.name, "FEATURES    ", TEXT_SZ);
      menu.num_options       = NUM_FEATURES_PER_PEDAL;
      menu.start_addr        = M_FEATURES;  // Need to set from callback
      menu.size              = sizeof(Feature);
      menu.return_addr       = MENU_PRESET_PARAM;
      menu.forward_addr      = MENU_PRESET_PARAM;
      menu.callback_setup_id = F_PRESET_PARAM_FEATURE_SETUP;
      menu.callback_save_id  = F_PRESET_PARAM_FEATURE_SAVE;
      write_data<Menu>(&menu, MENU_PRESET_PARAM_FEATURE);

#endif
#endif
