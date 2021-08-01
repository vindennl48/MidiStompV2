#ifndef DATABASE_H
#define DATABASE_H


/*  :: COLOR :: */
struct Color {
  // 16 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t r,g,b;

  Color() {
    this->r = 255;
    this->g = 0;
    this->b = 0;
  }
} *color_p = nullptr;


/*  :: PARAMETER :: */
struct Param {
  // 14 bytes
  char name[STR_LEN_MAX] = "UNTITLED";

  union {
    struct {
      unsigned type:3;   // 0=NONE, 1=Note, 2=CC, 3=PC
      unsigned pitch:7;
    };
  };

  Param() {
    this->type  = 0;
    this->pitch = 0;
  }
} *param_p = nullptr;


/*  :: PEDAL :: */
struct Pedal {
  // 14 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t channel           = 0;
  // 16 params
} *pedal_p = nullptr;

// Pedal Param = PP
union PedalParam {
  unsigned param_type:3;   // 0=OFF, 1=PEDAL, 2=SUBMENU, 3=PRESET
  struct {
    unsigned reserved1:3;
    unsigned special:8;    // 0=NONE, 1=PRESET++, 2=PRESET--, 3=PRESET+=20, 4=PRESET-=20
    unsigned param_value:8;
  };
  struct {
    unsigned reserved2:3;
    unsigned pedal:3;
    unsigned param:5;
    unsigned velocity:8;
  };
};
typedef PedalParam PedalParams[NUM_PARAMS_PER_FSW];

/*  :: FOOTSWITCH :: */
struct Footswitch {
  // 8 bytes
  PedalParams output[NUM_STATES] = { 0 };
  uint8_t     colors[NUM_STATES] = { 0, 1, 2 };

  // States of footswitch
  union {
    struct {
      unsigned mode:4;   // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
      unsigned state:4;  // 0 OFF,    1 ON1,   2 ON2
    };
  };

  Footswitch() {
    this->mode  = FSW_MODE_TOGGLE;
    this->state = 0;
  }

  void increase_state() {
    state += 1;
    if ( mode == FSW_MODE_CYCLE ) {
      if ( state >= 3 ) state = 0;
    }
    else if ( state >= 2 ) state = 0;
  }
} *fsw_p = nullptr;


/*  :: PRESET :: */
struct Preset {
  // 14 bytes
  PedalParams params            = {0};
  char        name[STR_LEN_MAX] = "UNTITLED";
  uint8_t     is_dirty          = false;
  // 4 footswitches
  // 1 main footswitch menu + 3 footswitch sub-menus
} *preset_p = nullptr;

/* :: DATABASE STRUCT :: */
struct DB {
  EEP_FUNC(color,  Color,   EEP_START_COLORS);
  EEP_FUNC(pedal,  Pedal,   EEP_START_PEDALS);
  EEP_FUNC(preset, Preset,  EEP_START_PRESETS);
  EEP_FUNC(menu,   uint8_t, EEP_START_MENUS);

  EEP_FUNC_EXTEND(param, Param,      EEP_START_PARAMS, EEP_NUM_PARAMS);
  EEP_FUNC_EXTEND(fsw,   Footswitch, EEP_START_FSW,    EEP_NUM_FSW);

  static void menu_item_at(uint8_t menu_id, uint8_t id, char *menu_item) { eReadBlock( EEP_START_OPTS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id, (uint8_t*)menu_item, STR_LEN_MAX ); }
  //static void    menu_item_save(uint8_t menu_id, uint8_t id, uint8_t new_obj) { return set_data<uint8_t>( &new_obj, EEP_START_MENUS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id ); }

  static char letter_at(uint8_t id) { return get_data<char>( EEP_START_LETTERS + id ); }
  //static void text_at(char *text, uint8_t id)                { eeprom_read_block( text, (void*)( EEP_START_MENUS + STR_LEN_MAX * id ), STR_LEN_MAX ); }
  //static void text_save(char *text, uint8_t id)              { eeprom_write_block((const void*)text, (void*)(EEP_START_MENUS + (STR_LEN_MAX * id)), STR_LEN_MAX); }
};


/*  :: RESET EEPROM :: */
void reset_eeprom() {
#ifdef EEP_RESET

  #ifdef EEP_RESET_COLORS
  {
    Color color;
    for (int i=0; i<EEP_NUM_COLORS; i++) set_data<Color>( &color, EEP_START_COLORS + (sizeof(Color) * i) );

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
    pedal_p = new Pedal;
    for (int i=0; i<EEP_NUM_PEDALS; i++) DB::pedal_save(i, pedal_p);
    CLRPTR(pedal_p);
  }
  #endif

  #ifdef EEP_RESET_FSW
  {
    param_p = new Param;
    for (int i=0; i<EEP_NUM_PARAMS; i++) DB::param_save_single(i, param_p);
    CLRPTR(param_p);
  }
  #endif

  #ifdef EEP_RESET_FSW
  {
    fsw_p = new Footswitch;
    for (int i=0; i<EEP_NUM_FSW; i++) DB::fsw_save_single(i, fsw_p);
    CLRPTR(fsw_p);
  }
  #endif

  #ifdef EEP_RESET_PRESETS
  {
    preset_p = new Preset;
    for (int i=0; i<EEP_NUM_PRESETS; i++) DB::preset_save(i, preset_p);
    CLRPTR(preset_p);
  }
  #endif

  #ifdef EEP_RESET_MENUS
  {
    uint8_t menu_options = 7;
    set_data<uint8_t>(&menu_options, EEP_START_MENUS + 0);
    menu_options = 4;
    set_data<uint8_t>(&menu_options, EEP_START_MENUS + 1);
    menu_options = 6;
    set_data<uint8_t>(&menu_options, EEP_START_MENUS + 2);
    menu_options = 4;
    set_data<uint8_t>(&menu_options, EEP_START_MENUS + 3);
    menu_options = 3;
    set_data<uint8_t>(&menu_options, EEP_START_MENUS + 4);
  }
  #endif

  #ifdef EEP_RESET_LETTERS
  {
    struct Alphabet {
      char letters[EEP_NUM_LETTERS_MAX] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789-_";
    } alphabet;
    set_data<Alphabet>(&alphabet, EEP_START_LETTERS);
  }
  #endif

  #ifdef EEP_RESET_OPTS
  {
    struct SaveOpts {
      char main_menu[10][STR_LEN_MAX] = {
        "SETTINGS",
        "SAVE",
        "NAME",
        "PARAMS",
        "COPY",
        "RESET",
        "GLOBAL"
      };
      char global_menu[10][STR_LEN_MAX] = {
        "GLOBAL",
        "PEDALS",
        "COLORS",
        "RESET"
      };
      char fsw_menu[10][STR_LEN_MAX] = {
        "FSW",
        "TYPE",
        "COLOR",
        "SHORT PRESS",
        "LONG PRESS",
        "RESET"
      };
      char pedal_menu[10][STR_LEN_MAX] = {
        "NAME",
        "CHANNEL",
        "PARAMS",
        "RESET"
      };
      char color_menu[10][STR_LEN_MAX] = {
        "COLOR",
        "NAME",
        "VALUES",
        "RESET"
      };
    } save_opts;

    set_data<SaveOpts>(&save_opts, EEP_START_OPTS);
  }
  #endif
#endif
}
/*  :: END RESET EEPROM :: */


#endif
