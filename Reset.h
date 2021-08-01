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
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 0) );

    color.r = 0; color.g = 255; color.b = 0;
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 1) );

    color.r = 0; color.g = 0; color.b = 255;
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 2) );

    color.r = 255; color.g = 255; color.b = 0;
    set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * 3) );

    color.r = 255; color.g = 0; color.b = 255;
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

  #ifdef EEP_RESET_MENUS
  {
    HW::screen.print_with_nline(0,1, "> MENUS");
    SubMenu    sub_menu;
    MenuOption menu_option[NUM_MENU_OPTIONS];
    uint8_t    menu_id     = 0;
    uint8_t    num_options = NUM_MENU_OPTIONS;

    menu_id     = 0;
    num_options = 7;
    sub_menu = SubMenu("PRESET", num_options);
    menu_option[0] = MenuOption("",       MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("SAVE",   MENU_TYPE_DUMMY);
    menu_option[2] = MenuOption("NAME",   MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("PARAMS", MENU_TYPE_FUNC_AND_SUB, /*FUNC ID*/ 0, /*SUBMENU ID*/ 2);
    menu_option[4] = MenuOption("COPY",   MENU_TYPE_DUMMY);
    menu_option[5] = MenuOption("RESET",  MENU_TYPE_DUMMY);
    menu_option[6] = MenuOption("GLOBAL", MENU_TYPE_SUB_MENU, 1);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = 1;
    num_options = 4;
    sub_menu = SubMenu("GLOBAL", num_options);
    menu_option[0] = MenuOption("",       MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("PEDALS", MENU_TYPE_DUMMY);
    menu_option[2] = MenuOption("COLORS", MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("RESET",  MENU_TYPE_DUMMY);
    DB::sub_menu_save(menu_id, &sub_menu);
    for (int i=0; i<num_options; i++) DB::menu_option_save(menu_id, i, &menu_option[i]);

    menu_id     = 2;
    num_options = 4;
    sub_menu = SubMenu("PARAM", num_options);
    menu_option[0] = MenuOption("",       MENU_TYPE_DUMMY);
    menu_option[1] = MenuOption("CHANGE", MENU_TYPE_DUMMY);
    menu_option[2] = MenuOption("VALUE",  MENU_TYPE_DUMMY);
    menu_option[3] = MenuOption("RESET",  MENU_TYPE_DUMMY);
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

//  #ifdef EEP_RESET_OPTS
//  {
//    struct SaveOpts {
//      char main_menu[10][STR_LEN_MAX] = {
//        "SETTINGS",
//        "SAVE",
//        "NAME",
//        "PARAMS",
//        "COPY",
//        "RESET",
//        "GLOBAL"
//      };
//      char global_menu[10][STR_LEN_MAX] = {
//        "GLOBAL",
//        "PEDALS",
//        "COLORS",
//        "RESET"
//      };
//      char fsw_menu[10][STR_LEN_MAX] = {
//        "FSW",
//        "TYPE",
//        "COLOR",
//        "SHORT PRESS",
//        "LONG PRESS",
//        "RESET"
//      };
//      char pedal_menu[10][STR_LEN_MAX] = {
//        "NAME",
//        "CHANNEL",
//        "PARAMS",
//        "RESET"
//      };
//      char color_menu[10][STR_LEN_MAX] = {
//        "COLOR",
//        "NAME",
//        "VALUES",
//        "RESET"
//      };
//    } save_opts;
//
//    set_data<SaveOpts>(&save_opts, EEP_START_OPTS);
//  }
//  #endif
#endif
}

#endif
