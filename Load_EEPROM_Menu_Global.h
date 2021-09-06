#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

address               = MENU_GLOBAL;
option_partition_addr = M_OPTIONS;
num_options_per_menu  = NUM_OPTIONS_PER_MENU;
menu = Menu();
//-------------------------------------------------------------------------------- 
memcpy(menu.name, "GLOBAL      ", TEXT_SZ);
menu.num_options = 2;
menu.start_addr  = option_partition_addr + ( GET_ID_FROM_ADDR(M_MENUS, address, sizeof(Menu)) * num_options_per_menu * sizeof(Option) );
menu.return_addr = MENU_PRESET;
write_data<Menu>(&menu, address);

  address = menu.start_addr + ( 0 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "PEDALS      ", TEXT_SZ);
  option.menu_addr = MENU_GLOBAL;
  write_data<Option>(&option, address);

  address = menu.start_addr + ( 1 * sizeof(Option) );
  option = Option();
  //-------------------------------------------------------------------------------- 
  memcpy(option.name, "COLORS      ", TEXT_SZ);
  option.menu_addr = MENU_GLOBAL;
  write_data<Option>(&option, address);

// memcpy(text[0], "GLOBAL      ", TEXT_SZ);
// Menu::set_name              (MENU_GLOBAL, TXT_BUF_1);
// Menu::set_num_options       (MENU_GLOBAL, 2);
// Menu::set_start_addr        (MENU_GLOBAL, GET_CHILD(M_OPTIONS, MENU_GLOBAL, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
// Menu::set_size              (MENU_GLOBAL, OPTION_SZ);
// Menu::set_return_id         (MENU_GLOBAL, MENU_PRESET);
// Menu::set_forward_id        (MENU_GLOBAL, MENU_MAIN); // not used, only used in list-loops
// Menu::set_callback_run_id   (MENU_GLOBAL, F_NONE);
// Menu::set_callback_setup_id (MENU_GLOBAL, F_GLOBAL);
// Menu::set_callback_save_id  (MENU_GLOBAL, F_NONE);
// 
//   memcpy(text[0], "PEDALS      ", TEXT_SZ);
//   Option::set_name        (MENU_GLOBAL, 0, TXT_BUF_1);
//   Option::set_result      (MENU_GLOBAL, 0, RESULT_MENU);
//   Option::set_menu_id     (MENU_GLOBAL, 0, MENU_PEDALS);
//   Option::set_callback_id (MENU_GLOBAL, 0, F_NONE);
// 
//   memcpy(text[0], "COLORS      ", TEXT_SZ);
//   Option::set_name        (MENU_GLOBAL, 1, TXT_BUF_1);
//   Option::set_result      (MENU_GLOBAL, 1, RESULT_MENU);
//   Option::set_menu_id     (MENU_GLOBAL, 1, MENU_COLORS);
//   Option::set_callback_id (MENU_GLOBAL, 1, F_NONE);

#endif
#endif
