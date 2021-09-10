#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

address               = MENU_FSW;
option_partition_addr = M_OPTIONS;
num_options_per_menu  = NUM_OPTIONS_PER_MENU;
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "FSW         ", TEXT_SZ);
menu.num_options       = 5;
menu.start_addr        = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
menu.return_addr       = MENU_MAIN;
menu.callback_setup_id = F_FSW_SETUP;
write_data<Menu>(&menu, address);

  address = menu.start_addr + ( 0 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PARAMETERS  ", TEXT_SZ);
  option.result    = RESULT_MENU;
  option.menu_addr = MENU_FSW;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 1 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "LONGPRESS   ", TEXT_SZ);
  option.result    = RESULT_MENU;
  option.menu_addr = MENU_FSW;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 2 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "COLOR       ", TEXT_SZ);
  option.result    = RESULT_MENU;
  option.menu_addr = MENU_FSW_COLOR;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 3 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "FSW MODE    ", TEXT_SZ);
  option.result    = RESULT_FSW_MODE_EDIT;
  option.menu_addr = MENU_FSW;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 4 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PRESS TYPE  ", TEXT_SZ);
  option.result    = RESULT_FSW_PRESS_TYPE_EDIT;
  option.menu_addr = MENU_FSW;
  write_data<Option>(&option, address);


// MENU 0, PEDAL CHOOSE
// Loop thru available pedals
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "COLORS      ", TEXT_SZ);
menu.num_options       = NUM_COLORS;
menu.start_addr        = M_COLORS;
menu.size              = sizeof(Color);
menu.return_addr       = MENU_FSW;
menu.forward_addr      = MENU_FSW;
menu.callback_setup_id = F_FSW_COLOR_SETUP;
menu.callback_run_id   = F_COLORS;
menu.callback_save_id  = F_FSW_COLOR_SAVE;
write_data<Menu>(&menu, MENU_FSW_COLOR);

#endif
#endif
