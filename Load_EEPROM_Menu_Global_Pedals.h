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


// memcpy(text[0], "PEDALS      ", TEXT_SZ);
// Menu::set_name              (MENU_PEDALS, TXT_BUF_1);
// Menu::set_num_options       (MENU_PEDALS, NUM_PEDALS);
// Menu::set_start_addr        (MENU_PEDALS, M_PEDALS);
// Menu::set_size              (MENU_PEDALS, PEDAL_SZ);
// Menu::set_return_id         (MENU_PEDALS, MENU_GLOBAL);
// Menu::set_forward_id        (MENU_PEDALS, MENU_PEDAL);  // This is going to be used
// Menu::set_callback_run_id   (MENU_PEDALS, F_NONE);
// Menu::set_callback_setup_id (MENU_PEDALS, F_NONE);
// Menu::set_callback_save_id  (MENU_PEDALS, F_NONE);
// 
// memcpy(text[0], "PEDAL       ", TEXT_SZ);
// Menu::set_name              (MENU_PEDAL, TXT_BUF_1);
// Menu::set_num_options       (MENU_PEDAL, 3);
// Menu::set_start_addr        (MENU_PEDAL, GET_CHILD(M_OPTIONS, MENU_PEDAL, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
// Menu::set_size              (MENU_PEDAL, OPTION_SZ);
// Menu::set_return_id         (MENU_PEDAL, MENU_PEDALS);
// Menu::set_forward_id        (MENU_PEDAL, MENU_MAIN);  // not used, only used in list-loop
// Menu::set_callback_run_id   (MENU_PEDAL, F_NONE);
// Menu::set_callback_setup_id (MENU_PEDAL, F_NONE);
// Menu::set_callback_save_id  (MENU_PEDAL, F_NONE);
// 
//   memcpy(text[0], "NAME        ", TEXT_SZ);
//   Option::set_name        (MENU_PEDAL, 0, TXT_BUF_1);
//   Option::set_result      (MENU_PEDAL, 0, RESULT_TEXT_EDIT);
//   Option::set_menu_id     (MENU_PEDAL, 0, MENU_PEDAL);
//   Option::set_callback_id (MENU_PEDAL, 0, F_NONE);
// 
//   memcpy(text[0], "FEATURES    ", TEXT_SZ);
//   Option::set_name        (MENU_PEDAL, 1, TXT_BUF_1);
//   Option::set_result      (MENU_PEDAL, 1, RESULT_MENU);
//   Option::set_menu_id     (MENU_PEDAL, 1, MENU_FEATURES);
//   Option::set_callback_id (MENU_PEDAL, 1, F_NONE);
// 
//   memcpy(text[0], "CHANNEL     ", TEXT_SZ);
//   Option::set_name        (MENU_PEDAL, 2, TXT_BUF_1);
//   Option::set_result      (MENU_PEDAL, 2, RESULT_VALUE_EDIT);
//   Option::set_menu_id     (MENU_PEDAL, 2, MENU_PEDAL);
//   Option::set_callback_id (MENU_PEDAL, 2, F_NONE);

#endif
#endif
