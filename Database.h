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
  char     name[STR_LEN_MAX] = "UNTITLED";
  unsigned channel:4;
  // 32 params

  Pedal() { channel = 0; }

} *pedal_p = nullptr;

// Pedal Param = PP
union PedalParam {
  // 2 bytes
  struct {
    unsigned pedal:3;
    unsigned param:5;
    unsigned velocity:7;
  };
} *pedal_param_p = nullptr;

/*  :: FOOTSWITCH :: */
struct Footswitch {
/* Outline of Features
 *   - Activated by single press OR press and hold
 *     - Activate when button is pressed down (quicker reaction)
 *       will prevent press-and-hold feature
 *     - Otherwise, activate when button is pressed then released
 *   - When activated, up to 5 MIDI notes will be sent.
 *     A different set of 5 notes get sent depending on the state.
 *     (Up to 3 states)
 *   - 4 Modes
 *     - OFF:     Button is not in use
 *     - TOGGLE:  Button will switch between state 0 and state 1
 *     - CYCLE:   Button will switch between state 0, 1, and 2
 *     - ONESHOT: Button will only send out first bank of 5 MIDI notes
 *                on every press.
 *   - There is also a press-and-hold option to release 5 extra MIDI notes
 *     This is only available when the FSW activates after press down and release.
 *   - SPECIALTY FUNCTIONS
 *     - Instead of sending MIDI notes, alternatively, we can perform some special functions
 *       - SWITCH PRESET: This can either switch to a specific preset instantly, OR, can
 *                        jump to the next/next 10/next 20/previous/previous 10/ previous 20.
 *                        This number of jumps can be set in the first pedal_param value.
 *       - SWITCH SUBMENU: This allows switching submenus within the same preset.  The
 *                         submenu number is determined by the first pedal_param value.
 *       - LOOP QUANTIZE: Requires MIDI clock input; When pressing a FSW, this waits for
 *                        the next down-beat on the MIDI clock before sending out a MIDI
 *                        message to a looper pedal to start.  Essentially mimics quantize.
 * */

  uint8_t colors[NUM_STATES] = { 0, 1, 2 };

  // States of footswitch
  union {
    struct {
      unsigned press_type:1; // 0 PRESS_TYPE_DOWN, 1 PRESS_TYPE_UP
      unsigned mode:3;       // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
                             //   SPECIALTY: 
                             //     4 Switch Submenu,
                             //     5 Jump to preset x,
                             //     6 Switch Preset by n number of presets,
                             //     7 Loop Quantize
      unsigned state:2;      // 0 OFF, 1 ON1, 2 ON2
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
/* Outline of Features
 *   - Display Preset Name
 *   - Display Active Preset Submenu
 *   - On Preset Load, Send out up to 5(*) MIDI notes. (* might need more..)
 *   - Have 4 FSW and maintain their status / settings
 *   - Has 4 submenus of 4 FSW for added flexibility.
 *     (Essentially, each preset has 16 FSW to choose from)
 * */

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
  EEP_FUNC_EXTEND(param, Param,      EEP_START_PARAMS, NUM_PEDAL_PARAMS);

  EEP_FUNC(preset, Preset,  EEP_START_PRESETS);
  EEP_FUNC_EXTEND(preset_param, PedalParam, EEP_START_PRESET_PARAMS, NUM_PRESET_PARAMS);

  EEP_FUNC_EXTEND(fsw,   Footswitch, EEP_START_FSW,    (NUM_FSW*NUM_SUB_MENUS));
  EEP_FUNC_EXTEND(fsw_param,   PedalParam, EEP_START_FSW_PARAMS, (NUM_PARAMS_PER_FSW*(NUM_STATES+1)));

  EEP_FUNC(sub_menu, SubMenu, EEP_START_MENUS);
  EEP_FUNC_EXTEND(menu_option, MenuOption, EEP_START_OPTS, NUM_MENU_ITEMS);

  static void menu_item_at(uint8_t menu_id, uint8_t id, char *menu_item) { eReadBlock( EEP_START_OPTS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id, (uint8_t*)menu_item, STR_LEN_MAX ); }
  //static void    menu_item_save(uint8_t menu_id, uint8_t id, uint8_t new_obj) { return set_data<uint8_t>( &new_obj, EEP_START_MENUS + STR_LEN_MAX * NUM_MENU_ITEMS * menu_id + STR_LEN_MAX * id ); }

  static char letter_at(uint8_t id) { return get_data<char>( EEP_START_LETTERS + id ); }
  //static void text_at(char *text, uint8_t id)                { eeprom_read_block( text, (void*)( EEP_START_MENUS + STR_LEN_MAX * id ), STR_LEN_MAX ); }
  //static void text_save(char *text, uint8_t id)              { eeprom_write_block((const void*)text, (void*)(EEP_START_MENUS + (STR_LEN_MAX * id)), STR_LEN_MAX); }
};



#endif
