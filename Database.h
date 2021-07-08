#ifndef DATABASE_H
#define DATABASE_H

/*  :: TEMPLATES :: */
template <typename T>
T get_data(uint16_t start) {
  T data;

  eeprom_read_block(
    (void*)&data,
    (void*)start,
    sizeof(T)
  );
  return data;
}

template <typename T>
void set_data(T *data, uint16_t start) {
  eeprom_write_block(
    (const void*)data,
    (void*)start,
    sizeof(T)
  );
}
/*  :: END TEMPLATES :: */


void get_data(char* phrase, uint16_t start) {
  eeprom_read_block(
    phrase,
    (void*)start,
    STR_LEN_MAX
  );
}
#define GET_TEXT(phrase, id) get_data(phrase, EEPROM_START_MENUS+(STR_LEN_MAX*id))


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
#define GET_COLOR(id) get_data<Color>(EEPROM_START_COLORS+(sizeof(Color)*id))
#define SET_COLOR(id, color) set_data<Color>(&color, EEPROM_START_COLORS+(sizeof(Color)*id))


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
  uint8_t colors[NUM_STATES]     = { 0, 1, 2 };
  uint8_t velocities[NUM_STATES] = { 0 };

  // States of footswitch
  union {
    struct {
      unsigned mode:4;   // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
      unsigned state:4;  // 0 OFF,    1 ON1,   2 ON2
    };
  };

  // Pedal Param = PP
  union {
    struct {
      unsigned pedal:3;
      unsigned param:5;
    };
  };

  Footswitch() {
    this->mode  = FSW_MODE_TOGGLE;
    this->state = 0;
    this->pedal = 0;
    this->param = 0;
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



/*  :: RESET EEPROM :: */
void reset_eeprom() {
//  {
//    Color color;
//    for (int i=0; i<EEPROM_NUM_COLORS; i++) set_data<Color>( &color, EEPROM_START_COLORS + (sizeof(Color) * i) );
//  }

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
    char word[STR_LEN_MAX] = "SETTINGS";
    //set_data<char[STR_LEN_MAX]>( word, EEPROM_START_MENUS + (sizeof(word) * 0) );
    eeprom_write_block((const void*)word, (void*)(EEPROM_START_MENUS + (STR_LEN_MAX * 0)), STR_LEN_MAX);

    strcpy(word, "PRESET NAME");
    //word = "PRESET NAME";
    //set_data<char[STR_LEN_MAX]>( word, EEPROM_START_MENUS + (sizeof(word) * 1) );
    eeprom_write_block((const void*)word, (void*)(EEPROM_START_MENUS + (STR_LEN_MAX * 1)), STR_LEN_MAX);
  }

  /*for (int i=0; i<EEPROM_NUM_START_MENUS; i++) save_to_eeprom(*color, EEPROM_START_START_MENUS + (sizeof(char[13])*i) );*/
}
/*  :: END RESET EEPROM :: */









/* :: MIDI :: */
// #define MIDI_KIND_MAX 3
// #define MIDI_NOTE_MAX 128
// const String midiKind[] = { "NOTE", "CC", "PC" };
// struct Midi {
//   uint8_t id = 0, kind = 0, note = 0;  
//   void   kind_up()      { kind += 1; if ( kind >= MIDI_KIND_MAX ) kind = MIDI_KIND_MAX-1; }
//   void   kind_down()    { if ( kind > 0 ) kind -= 1; }
//   void   note_up()      { note += 1; if ( note >= MIDI_NOTE_MAX ) note = MIDI_NOTE_MAX-1; }
//   void   note_down()    { if ( note > 0 ) note -= 1; }
//   String get_kind_str() { return midiKind[kind]; }
//   void   set_kind(uint8_t new_kind) { if ( new_kind < MIDI_KIND_MAX ) kind = new_kind; }
// };
// #define MIDI_MAX       10
// #define MIDI_SHIFT     4
// #define SET_MIDI(midi) set_data<Midi>(midi, MIDI_MAX, MIDI_SHIFT)
// #define GET_MIDI(id)   get_data<Midi>(id,   MIDI_MAX, MIDI_SHIFT)
// /* :: END MIDI :: */
// 
// 
// /* :: DEVICE :: */
// struct Device {
// private:
//   char name[CHAR_LEN] = "UNTITLED       ";
// public:
//   uint8_t id      = 0;
//   uint8_t channel = 0;
// 
//   void   set_name(String new_name) { new_name.toCharArray(name, CHAR_LEN); }
//   String get_name()                { return String(name); }
// 
//   struct parameter {
//   private:
//     char name[CHAR_LEN] = "PARAM          ";
//   public:
//     uint8_t midi_id = 0;
// 
//     void   set_name(String new_name) { new_name.toCharArray(name, CHAR_LEN); }
//     String get_name()                { return String(name); }
//   } params[10];
// };
// #define DEVICE_MAX         4
// #define DEVICE_SHIFT       ( ( sizeof(Midi) * MIDI_MAX ) + MIDI_SHIFT )
// #define SET_DEVICE(device) set_data<Device>(device, DEVICE_MAX, DEVICE_SHIFT)
// #define GET_DEVICE(id)     get_data<Device>(id,     DEVICE_MAX, DEVICE_SHIFT)
/* :: END DEVICE :: */


/* :: COLOR :: */
// struct Color {
//   uint8_t id = 0;
// 
//   union {
//     uint16_t data = 0;
//     struct{
//       unsigned r:4;
//       unsigned g:4;
//       unsigned b:4;
//     };
//   };
// };
// #define COLOR_MAX        4
// #define COLOR_SHIFT      ( ( sizeof(Device) * DEVICE_MAX ) + DEVICE_SHIFT )
// #define SET_COLOR(color) set_data<Color>(color, COLOR_MAX, COLOR_SHIFT)
// #define GET_COLOR(id)    get_data<Color>(id,    COLOR_MAX, COLOR_SHIFT)
/* :: END COLOR :: */


/* :: SUBMENU :: */
// struct SubMenu {
//   uint8_t    id = 0;
//   //Footswitch fsw[4];
// };
// #define SUBMENU_MAX          2
// #define SUBMENU_SHIFT        ( ( sizeof(Color) * COLOR_MAX ) + COLOR_SHIFT )
// #define SET_SUBMENU(submenu) set_data<SubMenu>(submenu, SUBMENU_MAX, SUBMENU_SHIFT)
// #define GET_SUBMENU(id)      get_data<SubMenu>(id,      SUBMENU_MAX, SUBMENU_SHIFT)
/* :: END SUBMENU :: */


/* :: PRESET :: */
// struct Preset {
// private:
//   char name[CHAR_LEN] = "UNTITLED       ";
// public:
//   uint8_t id         = 0;
//   uint8_t submenu_id = 0;
//   //MidiOut midi_out[10];
// 
//   void   set_name(String new_name) { new_name.toCharArray(name, CHAR_LEN); }
//   String get_name()                { return String(name); }
// };
// #define PRESET_MAX         1
// #define PRESET_SHIFT       ( ( sizeof(SubMenu) * SUBMENU_MAX ) + SUBMENU_SHIFT )
// #define SET_PRESET(preset) set_data<Preset>(preset, PRESET_MAX, PRESET_SHIFT)
// #define GET_PRESET(id)     get_data<Preset>(id,     PRESET_MAX, PRESET_SHIFT)
/* :: END PRESET :: */


#endif
