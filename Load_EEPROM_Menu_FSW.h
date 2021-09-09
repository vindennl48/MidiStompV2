#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

address               = MENU_FSW;
option_partition_addr = M_OPTIONS;
num_options_per_menu  = NUM_OPTIONS_PER_MENU;
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "FSW         ", TEXT_SZ);
menu.num_options = 2;
menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
menu.return_addr = MENU_MAIN;
write_data<Menu>(&menu, address);

  address = menu.start_addr + ( 0 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PARAMETERS  ", TEXT_SZ);
  option.result    = RESULT_MENU;
  option.menu_addr = MENU_MAIN;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 1 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PRESS TYPE  ", TEXT_SZ);
  option.result    = RESULT_MENU;
  option.menu_addr = MENU_MAIN;
  write_data<Option>(&option, address);

#endif
#endif
