#ifdef LOAD_EEPROM
#ifdef RESET_MENUS

memcpy(text[0], "PSET PARAMS ", TEXT_SZ);
Menu::set_name              (MENU_PRESET_PARAMS, TXT_BUF_1);
Menu::set_num_options       (MENU_PRESET_PARAMS, NUM_PRESET_PARAMS_PER_PRESET);
Menu::set_start_addr        (MENU_PRESET_PARAMS, M_PRESET_PARAMS);        // Set this from callback
Menu::set_size              (MENU_PRESET_PARAMS, PRESET_PARAM_SZ);
Menu::set_return_id         (MENU_PRESET_PARAMS, MENU_PRESET);
Menu::set_forward_id        (MENU_PRESET_PARAMS, MENU_PRESET_PARAM);      // This is going to be used
Menu::set_callback_run_id   (MENU_PRESET_PARAMS, F_PRESET_PARAMS_RUN);
Menu::set_callback_setup_id (MENU_PRESET_PARAMS, F_PRESET_PARAMS_SETUP);  // Set start address
Menu::set_callback_save_id  (MENU_PRESET_PARAMS, F_NONE);

memcpy(text[0], "PSET PARAM  ", TEXT_SZ);
Menu::set_name              (MENU_PRESET_PARAM, TXT_BUF_1);
Menu::set_num_options       (MENU_PRESET_PARAM, 3);
Menu::set_start_addr        (MENU_PRESET_PARAM, GET_CHILD(M_OPTIONS, MENU_PRESET_PARAM, 0, OPTION_SZ, NUM_OPTIONS_PER_MENU));
Menu::set_size              (MENU_PRESET_PARAM, OPTION_SZ);
Menu::set_return_id         (MENU_PRESET_PARAM, MENU_PRESET_PARAMS);
Menu::set_forward_id        (MENU_PRESET_PARAM, MENU_MAIN);  // not used, only used in list-loop
Menu::set_callback_run_id   (MENU_PRESET_PARAM, F_NONE);
Menu::set_callback_setup_id (MENU_PRESET_PARAM, F_NONE);
Menu::set_callback_save_id  (MENU_PRESET_PARAM, F_NONE);

  memcpy(text[0], "PEDAL       ", TEXT_SZ);
  Option::set_name        (MENU_PRESET_PARAM, 0, TXT_BUF_1);
  Option::set_result      (MENU_PRESET_PARAM, 0, RESULT_MENU);
  Option::set_menu_id     (MENU_PRESET_PARAM, 0, MENU_PRESET_PARAM_PEDAL);
  Option::set_callback_id (MENU_PRESET_PARAM, 0, F_NONE);

    memcpy(text[0], "PEDALS      ", TEXT_SZ);
    Menu::set_name              (MENU_PRESET_PARAM_PEDAL, TXT_BUF_1);
    Menu::set_num_options       (MENU_PRESET_PARAM_PEDAL, NUM_PEDALS);
    Menu::set_start_addr        (MENU_PRESET_PARAM_PEDAL, M_PEDALS);
    Menu::set_size              (MENU_PRESET_PARAM_PEDAL, PEDAL_SZ);
    Menu::set_return_id         (MENU_PRESET_PARAM_PEDAL, MENU_PRESET_PARAM);
    Menu::set_forward_id        (MENU_PRESET_PARAM_PEDAL, MENU_PRESET_PARAM);  // This is going to be used
    Menu::set_callback_run_id   (MENU_PRESET_PARAM_PEDAL, F_NONE);
    Menu::set_callback_setup_id (MENU_PRESET_PARAM_PEDAL, F_NONE);
    Menu::set_callback_save_id  (MENU_PRESET_PARAM_PEDAL, F_PRESET_PARAM_PEDAL_SAVE);

  memcpy(text[0], "PEDAL PARAM ", TEXT_SZ);
  Option::set_name        (MENU_PRESET_PARAM, 1, TXT_BUF_1);
  Option::set_result      (MENU_PRESET_PARAM, 1, RESULT_MENU);
  Option::set_menu_id     (MENU_PRESET_PARAM, 1, MENU_PRESET_PARAM);
  Option::set_callback_id (MENU_PRESET_PARAM, 1, F_NONE);

  memcpy(text[0], "VELOCITY    ", TEXT_SZ);
  Option::set_name        (MENU_PRESET_PARAM, 2, TXT_BUF_1);
  Option::set_result      (MENU_PRESET_PARAM, 2, RESULT_VALUE_EDIT);
  Option::set_menu_id     (MENU_PRESET_PARAM, 2, MENU_PRESET_PARAM);
  Option::set_callback_id (MENU_PRESET_PARAM, 2, F_NONE);

#endif
#endif
