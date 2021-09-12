#ifdef LOAD_EEPROM
#ifdef RESET_MENUS


// Loop thru available pedals to edit
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "COLORS      ", TEXT_SZ);
menu.num_options     = NUM_COLORS;
menu.start_addr      = M_COLORS;
menu.size            = sizeof(Color);
menu.return_addr     = MENU_GLOBAL;
menu.forward_addr    = MENU_COLOR;
menu.callback_run_id = F_COLORS;
write_data<Menu>(&menu, MENU_COLORS);

  address               = MENU_COLOR;
  option_partition_addr = M_OPTIONS;
  num_options_per_menu  = NUM_OPTIONS_PER_MENU;
  menu = Menu();
  //-------------------------------------------------------------------------------- 
  memcpy(menu.name, "COLOR       ", TEXT_SZ);
  menu.num_options = 2;
  menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
  menu.return_addr = MENU_COLORS;
  write_data<Menu>(&menu, address);

    address = menu.start_addr + ( 0 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "NAME        ", TEXT_SZ);
    option.result    = RESULT_TEXT_EDIT;
    option.menu_addr = MENU_COLOR;
    write_data<Option>(&option, address);

    address = menu.start_addr + ( 1 * sizeof(Option) );
    option = Option();
    //-------------------------------------------------------------------------------- 
    memcpy(option.name, "VALUE       ", TEXT_SZ);
    option.result    = RESULT_COLOR_EDIT;
    option.menu_addr = MENU_COLOR;
    write_data<Option>(&option, address);

#endif
#endif
