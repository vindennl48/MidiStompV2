#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

// Loop thru available pedals to edit
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "PEDALS      ", TEXT_SZ);
menu.num_options  = NUM_PEDALS;
menu.start_addr   = M_PEDALS;
menu.size         = sizeof(Pedal);
menu.return_addr  = MENU_GLOBAL;
menu.forward_addr = MENU_PEDAL;
write_data<Menu>(&menu, MENU_PEDALS);

  address               = MENU_PEDAL;
  option_partition_addr = M_OPTIONS;
  num_options_per_menu  = NUM_OPTIONS_PER_MENU;
  menu = Menu();
  //-------------------------------------------------------------------------------- 
  memcpy(menu.name, "PEDAL       ", TEXT_SZ);
  menu.num_options = 3;
  menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
  menu.return_addr = MENU_PEDALS;
  write_data<Menu>(&menu, address);

    address = menu.start_addr + ( 0 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "NAME        ", TEXT_SZ);
    option.result    = RESULT_TEXT_EDIT;
    option.menu_addr = MENU_PEDAL;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 1 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "FEATURES    ", TEXT_SZ);
    option.menu_addr = MENU_FEATURES;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 2 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "CHANNEL     ", TEXT_SZ);
    option.result    = RESULT_VALUE_EDIT;
    option.menu_addr = MENU_PEDAL;
    write_data<Option>(&option, address);

#endif
#endif
