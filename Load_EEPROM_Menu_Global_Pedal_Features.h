#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

memcpy(text[0], "FEATURES    ", TEXT_SZ);
Menu::set_name              (MENU_FEATURES, TXT_BUF_1);
Menu::set_num_options       (MENU_FEATURES, NUM_PEDALS);
Menu::set_start_addr        (MENU_FEATURES, M_PEDALS);
Menu::set_size              (MENU_FEATURES, PEDAL_SZ);
Menu::set_return_id         (MENU_FEATURES, MENU_GLOBAL);
Menu::set_forward_id        (MENU_FEATURES, MENU_FEATURE);  // This is going to be used
Menu::set_callback_run_id   (MENU_FEATURES, F_NONE);
Menu::set_callback_setup_id (MENU_FEATURES, F_NONE);

memcpy(text[0], "FEATURE     ", TEXT_SZ);
Menu::set_name              (MENU_FEATURE, TXT_BUF_1);
Menu::set_num_options       (MENU_FEATURE, 3);
Menu::set_start_addr        (MENU_FEATURE, GET_CHILD(M_OPTIONS, MENU_FEATURE, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
Menu::set_size              (MENU_FEATURE, OPTION_SZ);
Menu::set_return_id         (MENU_FEATURE, MENU_FEATURES);
Menu::set_forward_id        (MENU_FEATURE, MENU_MAIN);  // not used, only used in list-loop
Menu::set_callback_run_id   (MENU_FEATURE, F_NONE);
Menu::set_callback_setup_id (MENU_FEATURE, F_NONE);

  memcpy(text[0], "NAME        ", TEXT_SZ);
  Option::set_name        (MENU_FEATURE, 0, TXT_BUF_1);
  Option::set_result      (MENU_FEATURE, 0, RESULT_TEXT_EDIT);
  Option::set_menu_id     (MENU_FEATURE, 0, MENU_FEATURE);
  Option::set_callback_id (MENU_FEATURE, 0, F_NONE);

  memcpy(text[0], "TYPE        ", TEXT_SZ);
  Option::set_name        (MENU_FEATURE, 1, TXT_BUF_1);
  Option::set_result      (MENU_FEATURE, 1, RESULT_VALUE_EDIT);
  Option::set_menu_id     (MENU_FEATURE, 1, MENU_FEATURE);
  Option::set_callback_id (MENU_FEATURE, 1, F_NONE);

  memcpy(text[0], "PITCH       ", TEXT_SZ);
  Option::set_name        (MENU_FEATURE, 2, TXT_BUF_1);
  Option::set_result      (MENU_FEATURE, 2, RESULT_VALUE_EDIT);
  Option::set_menu_id     (MENU_FEATURE, 2, MENU_FEATURE);
  Option::set_callback_id (MENU_FEATURE, 2, F_NONE);

#endif
#endif
