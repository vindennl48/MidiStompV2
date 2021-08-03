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
} *pedal_param_p = nullptr;

/*  :: FOOTSWITCH :: */
struct Footswitch {
  // 8 bytes
  //PedalParams output[NUM_STATES] = { 0 };
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
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t is_dirty          = false;
  // 4 footswitches
  // 1 main footswitch menu + 3 footswitch sub-menus
  // 10 pedal params on preset load
} *preset_p = nullptr;


/*  :: MENU STRUCTS :: */
/* MenuOption 0 is always going to be a dummy option (impossible to select) */
struct MenuOption {
  char text[STR_LEN_MAX];

  union {
    struct {
      unsigned type:2;    // 0=DUMMY, 1=SUBMENU, 2=FUNCTION, 3=FUNC THEN SUBMENU
      unsigned value:8;   // submenu or function id to call
      unsigned value2:8;  // value is function call, value2 is submenu (only in type 3)
    };
  };

  MenuOption(const char text[STR_LEN_MAX], uint8_t type, uint8_t value=0, uint8_t value2=0) {
    strcpy(this->text, text);
    this->type   = type;
    this->value  = value;
    this->value2 = value2;
  }
  MenuOption() {}  // For pointers
};


struct SubMenu {
  char    title[STR_LEN_MAX];
  uint8_t num_options;

  SubMenu(const char title[STR_LEN_MAX], uint8_t num_options) {
    strcpy(this->title, title);
    this->num_options = num_options;
  }
  SubMenu() {}  // For pointers
};
/*  :: END MENU STRUCTS :: */



/* :: DATABASE STRUCT :: */
struct DB {
  EEP_FUNC(color,  Color,   EEP_START_COLORS);
  EEP_FUNC(pedal,  Pedal,   EEP_START_PEDALS);
  EEP_FUNC(preset, Preset,  EEP_START_PRESETS);
  //EEP_FUNC(menu,   uint8_t, EEP_START_MENUS);

  EEP_FUNC(sub_menu, SubMenu, EEP_START_MENUS);
  EEP_FUNC_EXTEND(menu_option, MenuOption, EEP_START_OPTS, NUM_MENU_ITEMS);

  EEP_FUNC_EXTEND(param, Param,      EEP_START_PARAMS, EEP_NUM_PARAMS);
  EEP_FUNC_EXTEND(fsw,   Footswitch, EEP_START_FSW,    EEP_NUM_FSW);

  static void menu_item_at(uint8_t menu_id, uint8_t id, char *menu_item) { eReadBlock( EEP_START_OPTS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id, (uint8_t*)menu_item, STR_LEN_MAX ); }
  //static void    menu_item_save(uint8_t menu_id, uint8_t id, uint8_t new_obj) { return set_data<uint8_t>( &new_obj, EEP_START_MENUS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id ); }

  static char letter_at(uint8_t id) { return get_data<char>( EEP_START_LETTERS + id ); }
  //static void text_at(char *text, uint8_t id)                { eeprom_read_block( text, (void*)( EEP_START_MENUS + STR_LEN_MAX * id ), STR_LEN_MAX ); }
  //static void text_save(char *text, uint8_t id)              { eeprom_write_block((const void*)text, (void*)(EEP_START_MENUS + (STR_LEN_MAX * id)), STR_LEN_MAX); }
};



#endif
