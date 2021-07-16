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
};


/*  :: PARAMETER :: */
struct Param {
  // 14 bytes
  char name[STR_LEN_MAX] = "UNTITLED";

  union {
    struct {
      unsigned type:1;
      unsigned pitch:7;
    };
  };

  Param() {
    this->type  = 0;
    this->pitch = 0;
  }
};


/*  :: PEDAL :: */
struct Pedal {
  // 14 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t channel           = 0;
  // 16 params
};


/*  :: FOOTSWITCH :: */
struct Footswitch {
  // 8 bytes
  uint8_t colors[NUM_STATES] = { 0, 1, 2 };

  // States of footswitch
  union {
    struct {
      unsigned mode:4;   // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
      unsigned state:4;  // 0 OFF,    1 ON1,   2 ON2
    };
  };

  // Pedal Param = PP
  union PP {
    struct {
      unsigned pedal:3;
      unsigned param:5;
      unsigned velocity:8;
    };
  } output[NUM_STATES] = { 0 };

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
};


/*  :: PRESET :: */
struct Preset {
  // 14 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  boolean is_dirty          = false;
  // 4 footswitches
  // 1 main footswitch menu + 3 footswitch sub-menus
};

struct MenuItem { char data[STR_LEN_MAX]; };

/* :: DATABASE STRUCT :: */
struct DB {
  static Color color_at(     uint8_t id)                                        { return get_data<Color>(                EEPROM_START_COLORS + sizeof(Color) * id ); }
  static void  color_save(   uint8_t id, Color new_obj)                         { return set_data<Color>(      &new_obj, EEPROM_START_COLORS + sizeof(Color) * id ); }

  static Pedal pedal_at(     uint8_t id)                                        { return get_data<Pedal>(                EEPROM_START_PEDALS + sizeof(Pedal) * id ); }
  static void  pedal_save(   uint8_t id, Pedal new_obj)                         { return set_data<Pedal>(      &new_obj, EEPROM_START_PEDALS + sizeof(Pedal) * id ); }

  static Preset preset_at(    uint8_t id)                                        { return get_data<Preset>(               EEPROM_START_PRESETS + sizeof(Preset) * id ); }
  static void  preset_save(   uint8_t id, Preset new_obj)                        { return set_data<Preset>(     &new_obj, EEPROM_START_PRESETS + sizeof(Preset) * id ); }

  static Param param_at(     uint8_t parent_id, uint8_t id)                     { return get_data<Param>(                EEPROM_START_PARAMS + sizeof(Param) * EEPROM_NUM_PARAMS * parent_id + sizeof(Param) * id ); }
  static void param_save(    uint8_t parent_id, uint8_t id, Param new_obj)      { return set_data<Param>(      &new_obj, EEPROM_START_PARAMS + sizeof(Param) * EEPROM_NUM_PARAMS * parent_id + sizeof(Param) * id ); }

  static Footswitch fsw_at(uint8_t parent_id, uint8_t id)                     { return get_data<Footswitch>(           EEPROM_START_FSW + sizeof(Footswitch) * EEPROM_NUM_FSW * parent_id + sizeof(Footswitch) * id ); }
  static void fsw_save(    uint8_t parent_id, uint8_t id, Footswitch new_obj) { return set_data<Footswitch>( &new_obj, EEPROM_START_FSW + sizeof(Footswitch) * EEPROM_NUM_FSW * parent_id + sizeof(Footswitch) * id ); }

  // Menu just saves the # of MenuItems for each menu
  // Each menu has 10 reserved spots for MenuItems, however,
  // you do not need to use all of the spots.
  static uint8_t menu_at(       uint8_t id)                  { return get_data<uint8_t>(           EEPROM_START_MENUS + id ); }
  static void    menu_save(     uint8_t id, uint8_t new_obj) { return set_data<uint8_t>( &new_obj, EEPROM_START_MENUS + id ); }

  static void menu_item_at(uint8_t menu_id, uint8_t id, char *menu_item) { eReadBlock( EEPROM_START_MENUS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id, (uint8_t*)menu_item, STR_LEN_MAX ); }
  //static void    menu_item_save(uint8_t menu_id, uint8_t id, uint8_t new_obj) { return set_data<uint8_t>( &new_obj, EEPROM_START_MENUS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id ); }

  static void text_at(char *text, uint8_t id)                { eeprom_read_block( text, (void*)( EEPROM_START_MENUS + STR_LEN_MAX * id ), STR_LEN_MAX ); }
  static void text_save(char *text, uint8_t id)              { eeprom_write_block((const void*)text, (void*)(EEPROM_START_MENUS + (STR_LEN_MAX * id)), STR_LEN_MAX); }
};


/*  :: RESET EEPROM :: */
void reset_eeprom() {
#ifdef CODING_RESET

  {
    Color color;
    for (int i=0; i<EEPROM_NUM_COLORS; i++) set_data<Color>( &color, EEPROM_START_COLORS + (sizeof(Color) * i) );
  }

  {
    Pedal pedal;
    for (int i=0; i<EEPROM_NUM_PEDALS; i++) set_data<Pedal>( &pedal, EEPROM_START_PEDALS + (sizeof(Pedal) * i) );
  }

  {
    Param param;
    for (int i=0; i<EEPROM_NUM_PARAMS; i++) set_data<Param>( &param, EEPROM_START_PARAMS + (sizeof(Param) * i) );
  }

  {
    Footswitch fsw;
    for (int i=0; i<EEPROM_NUM_FSW; i++) set_data<Footswitch>( &fsw, EEPROM_START_FSW + (sizeof(Footswitch) * i) );
  }

  {
    Preset preset;
    for (int i=0; i<EEPROM_NUM_PRESETS; i++) set_data<Preset>( &preset, EEPROM_START_PRESETS + (sizeof(Preset) * i) );
  }

  {
    uint8_t menu_options = 7;
    set_data<uint8_t>(&menu_options, EEPROM_START_MENUS + 0);
    menu_options = 4;
    set_data<uint8_t>(&menu_options, EEPROM_START_MENUS + 1);
    menu_options = 4;
    set_data<uint8_t>(&menu_options, EEPROM_START_MENUS + 2);
    menu_options = 3;
    set_data<uint8_t>(&menu_options, EEPROM_START_MENUS + 3);
  }

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
      char pedal_menu[10][STR_LEN_MAX] = {
        "NAME",
        "CHANNEL",
        "PARAMS",
        "RESET"
      };
      char color_menu[10][STR_LEN_MAX] = {
        "NAME",
        "VALUES",
        "RESET"
      };
    } save_opts;

    set_data<SaveOpts>(&save_opts, EEPROM_START_OPTS);
  }
#endif
}
/*  :: END RESET EEPROM :: */


#endif
