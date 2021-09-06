#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

memcpy(text[0], "PRESET      ", TEXT_SZ);
Menu::set_name              (MENU_PRESET, TXT_BUF_1);
Menu::set_num_options       (MENU_PRESET, 3);
Menu::set_start_addr        (MENU_PRESET, GET_CHILD(M_OPTIONS, MENU_PRESET, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
Menu::set_size              (MENU_PRESET, OPTION_SZ);
Menu::set_return_id         (MENU_PRESET, MENU_MAIN);
Menu::set_forward_id        (MENU_PRESET, MENU_MAIN); // not used, only used in list-loops
Menu::set_callback_run_id   (MENU_PRESET, F_NONE);
Menu::set_callback_setup_id (MENU_PRESET, F_NONE);

  memcpy(text[0], "NAME        ", TEXT_SZ);
  Option::set_name        (MENU_PRESET, 0, TXT_BUF_1);
  Option::set_result      (MENU_PRESET, 0, RESULT_TEXT_EDIT);
  Option::set_menu_id     (MENU_PRESET, 0, MENU_PRESET);
  Option::set_callback_id (MENU_PRESET, 0, F_NONE);

  memcpy(text[0], "PARAMS      ", TEXT_SZ);
  Option::set_name        (MENU_PRESET, 1, TXT_BUF_1);
  Option::set_result      (MENU_PRESET, 1, RESULT_MENU);
  Option::set_menu_id     (MENU_PRESET, 1, MENU_MAIN);
  Option::set_callback_id (MENU_PRESET, 1, F_NONE);

  memcpy(text[0], "GLOBAL      ", TEXT_SZ);
  Option::set_name        (MENU_PRESET, 2, TXT_BUF_1);
  Option::set_result      (MENU_PRESET, 2, RESULT_MENU);
  Option::set_menu_id     (MENU_PRESET, 2, MENU_GLOBAL);
  Option::set_callback_id (MENU_PRESET, 2, F_NONE);

#endif
#endif
