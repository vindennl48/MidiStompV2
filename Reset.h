#ifndef RESET_H
#define RESET_H


void reset_eeprom() {
#ifdef EEP_RESET

  #ifdef EEP_RESET_COLORS
  {
    HW::screen.print_with_nline(0,1, "> COLORS");
    Color color;
    for (int i=0; i<EEP_NUM_COLORS; i++) {
      set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * i) );
      HW::screen.print_with_nline(10,1, String(i));
    }

    color.r = 255; color.g = 0; color.b = 0;
    memcpy(color.name, "RED         ", STR_LEN_MAX);
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 0) );

    color.r = 0; color.g = 255; color.b = 0;
    memcpy(color.name, "GREEN       ", STR_LEN_MAX);
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 1) );

    color.r = 0; color.g = 0; color.b = 255;
    memcpy(color.name, "BLUE        ", STR_LEN_MAX);
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 2) );

    color.r = 255; color.g = 255; color.b = 0;
    memcpy(color.name, "YELLOW      ", STR_LEN_MAX);
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 3) );

    color.r = 255; color.g = 0; color.b = 255;
    memcpy(color.name, "PURPLE      ", STR_LEN_MAX);
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 4) );
  }
  #endif

  #ifdef EEP_RESET_PEDALS
  {
    HW::screen.print_with_nline(0,1, "> PEDALS");
    pedal_p = new Pedal;
    for (int i=0; i<EEP_NUM_PEDALS; i++) {
      DB::pedal_save(i, pedal_p);
      HW::screen.print_with_nline(9,1, String(i));
    }
    CLRPTR(pedal_p);
  }
  #endif

  #ifdef EEP_RESET_PEDAL_PARAMS
  {
    HW::screen.print_with_nline(0,1, "> PDL PARAMS");
    param_p = new Param;
    for (int i=0; i<EEP_NUM_PARAMS; i++) {
      DB::param_save_single(i, param_p);
      HW::screen.print_with_nline(13,1, String(i));
    }
    CLRPTR(param_p);
  }
  #endif

  #ifdef EEP_RESET_FSW
  {
    HW::screen.print_with_nline(0,1, "> FSW");
    fsw_p = new Footswitch;
    for (int i=0; i<EEP_NUM_FSW; i++) {
      DB::fsw_save_single(i, fsw_p);
      HW::screen.print_with_nline(6,1, String(i));
    }
    CLRPTR(fsw_p);
  }
  #endif

  #ifdef EEP_RESET_FSW_PARAMS
  {
    HW::screen.print_with_nline(0,1, "> FSWPRM");
    pedal_param_p = new PedalParam;
    for (int i=0; i<EEP_NUM_FSW_PARAMS; i++) {
      DB::fsw_param_save_single(i, pedal_param_p);
      HW::screen.print_with_nline(9,1, String(i));
    }
    CLRPTR(pedal_param_p);
  }
  #endif

  #ifdef EEP_RESET_PRESETS
  {
    HW::screen.print_with_nline(0,1, "> PRESETS");
    preset_p = new Preset;
    for (int i=0; i<EEP_NUM_PRESETS; i++) {
      DB::preset_save(i, preset_p);
      HW::screen.print_with_nline(10,1, String(i));
    }
    CLRPTR(preset_p);
  }
  #endif

  #ifdef EEP_RESET_PRESET_PARAMS
  {
    HW::screen.print_with_nline(0,1, "> PRSTPRMS");
    pedal_param_p = new PedalParam;
    for (int i=0; i<EEP_NUM_PRESET_PARAMS; i++) {
      DB::preset_param_save_single(i, pedal_param_p);
      HW::screen.print_with_nline(11,1, String(i));
    }
    CLRPTR(pedal_param_p);
  }
  #endif

  #ifdef EEP_RESET_MENUS
  {
    HW::screen.print_with_nline(0,1, "> MENUS");
    SubMenu    sub_menu;
    MenuOption menu_option[NUM_MENU_OPTIONS];
    uint8_t    menu_id     = 0;
    uint8_t    num_options = NUM_MENU_OPTIONS;

    menu_id     = EEP_SUBMENU_PRESET;
    num_options = 7;
    sub_menu = SubMenu("PRESET", num_options);
    menu_option[0] = MenuOption("",       MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("SAVE",   MENU_TYPE_FUNCTION,     F_SUBMENU_PRESET_SAVE);
    menu_option[2] = MenuOption("NAME",   MENU_TYPE_FUNCTION,     F_SUBMENU_PRESET_NAME);
    menu_option[3] = MenuOption("PARAMS", MENU_TYPE_FUNC_AND_SUB, F_SUBMENU_PRESET_PARAMS, EEP_SUBMENU_PARAM);
    menu_option[4] = MenuOption("COPY",   MENU_TYPE_FUNCTION,     F_SUBMENU_PRESET_COPY);
    menu_option[5] = MenuOption("RESET",  MENU_TYPE_FUNCTION,     F_SUBMENU_PRESET_RESET);
    menu_option[6] = MenuOption("GLOBAL", MENU_TYPE_SUB_MENU, EEP_SUBMENU_GLOBAL);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_GLOBAL;
    num_options = 4;
    sub_menu = SubMenu("GLOBAL", num_options);
    menu_option[0] = MenuOption("",       MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("PEDALS", MENU_TYPE_FUNC_AND_SUB, F_SUBMENU_PEDALS, EEP_SUBMENU_PEDAL);
    menu_option[2] = MenuOption("COLORS", MENU_TYPE_FUNC_AND_SUB, F_SUBMENU_COLORS, EEP_SUBMENU_COLOR);
    menu_option[3] = MenuOption("RESET",  MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_PARAM;
    num_options = 5;
    sub_menu    = SubMenu("PARAM", num_options);
    menu_option[0] = MenuOption("",            MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("PEDAL",       MENU_TYPE_FUNCTION, F_SUBMENU_PRESET_PARAM_PEDAL);
    menu_option[2] = MenuOption("PEDAL PARAM", MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("VELOCITY",    MENU_TYPE_FUNCTION, F_SUBMENU_PRESET_PARAM_VELOCITY);
    menu_option[4] = MenuOption("RESET",       MENU_TYPE_FUNCTION, F_SUBMENU_PRESET_PARAM_RESET);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_PEDAL;
    num_options = 5;
    sub_menu    = SubMenu("PEDAL", num_options);
    menu_option[0] = MenuOption("",        MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("NAME",    MENU_TYPE_FUNCTION,     F_SUBMENU_PEDAL_NAME);
    menu_option[2] = MenuOption("PARAMS",  MENU_TYPE_FUNC_AND_SUB, F_SUBMENU_PEDAL_PARAMS, EEP_SUBMENU_PEDAL_PARAM);
    menu_option[3] = MenuOption("CHANNEL", MENU_TYPE_FUNCTION,     F_SUBMENU_PEDAL_CHAN);
    menu_option[4] = MenuOption("RESET",   MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_PEDAL_PARAM;
    num_options = 5;
    sub_menu    = SubMenu("PEDAL PARAM", num_options);
    menu_option[0] = MenuOption("",      MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("NAME",  MENU_TYPE_FUNCTION, F_SUBMENU_PEDAL_PARAM_NAME);
    menu_option[2] = MenuOption("TYPE",  MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("PITCH", MENU_TYPE_DUMMY);
    menu_option[4] = MenuOption("RESET", MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_FSW;
    num_options = 6;
    sub_menu    = SubMenu("FSW", num_options);
    menu_option[0] = MenuOption("",           MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("TYPE",       MENU_TYPE_DUMMY);
    menu_option[2] = MenuOption("COLOR",      MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("SHORTPRESS", MENU_TYPE_DUMMY);
    menu_option[4] = MenuOption("LONGPRESS",  MENU_TYPE_DUMMY);
    menu_option[5] = MenuOption("RESET",      MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = EEP_SUBMENU_COLOR;
    num_options = 4;
    sub_menu    = SubMenu("COLOR", num_options);
    menu_option[0] = MenuOption("",      MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("NAME",  MENU_TYPE_FUNCTION, F_SUBMENU_COLOR_NAME);
    menu_option[2] = MenuOption("VALUE", MENU_TYPE_FUNCTION, F_SUBMENU_COLOR_EDIT);
    menu_option[3] = MenuOption("RESET", MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

  }
  #endif

  #ifdef EEP_RESET_LETTERS
  {
    HW::screen.print_with_nline(0,1, "> LETTERS");
    struct Alphabet {
      char letters[EEP_NUM_LETTERS_MAX] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789-_";
    } alphabet;
    set_data<Alphabet>(&alphabet, EEP_START_LETTERS);
  }
  #endif

#endif
}

#endif
