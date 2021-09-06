#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

memcpy(text[0], "COLORS      ", TEXT_SZ);
Menu::set_name              (MENU_COLORS, TXT_BUF_1);
Menu::set_num_options       (MENU_COLORS, NUM_COLORS);
Menu::set_start_addr        (MENU_COLORS, M_COLORS);
Menu::set_size              (MENU_COLORS, COLOR_SZ);
Menu::set_return_id         (MENU_COLORS, MENU_GLOBAL);
Menu::set_forward_id        (MENU_COLORS, MENU_COLOR);  // This is going to be used
Menu::set_callback_run_id   (MENU_COLORS, F_COLORS);
Menu::set_callback_setup_id (MENU_COLORS, F_NONE);
Menu::set_callback_save_id  (MENU_COLORS, F_NONE);

memcpy(text[0], "COLOR       ", TEXT_SZ);
Menu::set_name              (MENU_COLOR, TXT_BUF_1);
Menu::set_num_options       (MENU_COLOR, 2);
Menu::set_start_addr        (MENU_COLOR, GET_CHILD(M_OPTIONS, MENU_COLOR, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
Menu::set_size              (MENU_COLOR, OPTION_SZ);
Menu::set_return_id         (MENU_COLOR, MENU_COLORS);
Menu::set_forward_id        (MENU_COLOR, MENU_MAIN);  // not used, only used in list-loop
Menu::set_callback_run_id   (MENU_COLOR, F_NONE);
Menu::set_callback_setup_id (MENU_COLOR, F_NONE);
Menu::set_callback_save_id  (MENU_COLOR, F_NONE);

  memcpy(text[0], "NAME        ", TEXT_SZ);
  Option::set_name        (MENU_COLOR, 0, TXT_BUF_1);
  Option::set_result      (MENU_COLOR, 0, RESULT_TEXT_EDIT);
  Option::set_menu_id     (MENU_COLOR, 0, MENU_COLOR);
  Option::set_callback_id (MENU_COLOR, 0, F_NONE);

  memcpy(text[0], "VALUE       ", TEXT_SZ);
  Option::set_name        (MENU_COLOR, 1, TXT_BUF_1);
  Option::set_result      (MENU_COLOR, 1, RESULT_COLOR_EDIT);
  Option::set_menu_id     (MENU_COLOR, 1, MENU_COLOR);
  Option::set_callback_id (MENU_COLOR, 1, F_NONE);

#endif
#endif
