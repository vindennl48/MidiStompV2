#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

address               = MENU_PRESET;
option_partition_addr = M_OPTIONS;
num_options_per_menu  = NUM_OPTIONS_PER_MENU;
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "PRESET      ", TEXT_SZ);
menu.num_options     = 3;
menu.start_addr      = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
menu.return_addr     = MENU_MAIN;
write_data<Menu>(&menu, address);

  address = menu.start_addr + ( 0 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "NAME        ", TEXT_SZ);
  option.result    = RESULT_TEXT_EDIT;
  option.menu_addr = MENU_PRESET;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 1 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PARAMS      ", TEXT_SZ);
  option.menu_addr = MENU_PRESET_PARAMS;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 2 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "GLOBAL      ", TEXT_SZ);
  option.menu_addr = MENU_GLOBAL;
  write_data<Option>(&option, address);

#endif
#endif
