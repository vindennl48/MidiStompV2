/* :: GENERAL DEFINES :: */
#define NUM_CHAN 3  // Color channels, ie. red, green, blue
/* :: END GENERAL DEFINES :: */


/* :: HELPFUL MACROS :: */
#define GET_NIBBLE(input, mask, shift)  ((mask & input) >> shift)

// These help get the start address in eeprom
#define GET_PARENT(start, id, size) (start + (id*size))
#define GET_CHILD(start, parent_id, id, size, num_in_parent) (start + (parent_id*size*num_in_parent) + (id*size))
#define GET_END(start, quantity, size) ((uint16_t)start + ((uint16_t)quantity*(uint16_t)size))

#define GET_ID_FROM_ADDR(list_start, addr, size) ((addr-list_start) == 0 ? (uint16_t)0 : (uint16_t)((addr-list_start)/size))

// Given the local ID of a child, this helps get the absolute ID of the child in the eeprom
// For example: If we have fsw_id of 2, this means the 3rd physical footswitch..
//              however, if we are on thie 3rd preset, 2nd submenu, the absolute ID is actually 38..
//              4 fsw per submenu, 4 submenu per preset, which is 16 fsw per preset.
//              3rd preset is preset_id=2, 16*2 = 32
//              2nd submenu is submenu_id=1, 32+4*1 = 36
//              fsw_id of 2, 36+2 = 38
//              So in the EEPROM, this fsw is the 39th one, absolute fsw_id = 38
#define GET_ABS_CHILD_ID(parent_id, child_id, num_children_in_parent) (parent_id*num_children_in_parent+child_id)
#define GET_ABS_CHILD_ID_2(parent1_id, parent2_id, child_id, num_children_in_parent2, num_parent2_in_parent1) \
  ((num_children_in_parent2*num_parent2_in_parent1*parent1_id) + (num_children_in_parent2*parent2_id) + child_id)
/* :: END HELPFUL MACROS :: */


/* :: OBJECT COUNTS :: */
#define NUM_COLORS                   100
#define NUM_COLORS_PER_FSW           3
#define NUM_PEDALS                   8
#define NUM_FEATURES_PER_PEDAL       32
#define NUM_FEATURES_TOTAL           (NUM_PEDALS * NUM_FEATURES_PER_PEDAL)
#define NUM_PRESETS                  30
#define NUM_PRESET_PARAMS_PER_PRESET 10
#define NUM_PRESET_PARAMS_TOTAL      (NUM_PRESETS * NUM_PRESET_PARAMS_PER_PRESET)
#define NUM_SUBMENUS_PER_PRESET      4
#define NUM_FSW_PER_SUBMENU          4
#define NUM_FSW_PER_PRESET           (NUM_FSW_PER_SUBMENU * NUM_SUBMENUS_PER_PRESET)
#define NUM_FSW_TOTAL                (NUM_FSW_PER_PRESET * NUM_PRESETS)
#define NUM_STATES_PER_FSW           4  // 3 states plus one state for longpress
#define NUM_FSW_PARAMS_PER_STATE     10
#define NUM_FSW_PARAMS_PER_FSW       (NUM_STATES_PER_FSW * NUM_FSW_PARAMS_PER_STATE)
#define NUM_FSW_PARAMS_TOTAL         (NUM_FSW_PARAMS_PER_FSW * NUM_FSW_TOTAL)
#define NUM_MENUS                    20
#define NUM_OPTIONS_PER_MENU         10
#define NUM_OPTIONS_TOTAL            (NUM_MENUS*NUM_OPTIONS_PER_MENU)
/* :: END OBJECT COUNTS :: */


/* :: FUNC BUILDERS:: */
// Takes an address of the object plus the text buffer to
// write the name to.
#define BUILD_OBJ_NAME \
  static void get_name(uint16_t addr, uint8_t i) { \
    eReadBlock( addr, (uint8_t*)text[i], TEXT_SZ ); \
  } \
  static void set_name(uint16_t addr, uint8_t i) { \
    eWriteBlock( addr, (uint8_t*)text[i], TEXT_SZ ); \
  }
// Takes name you want the function to be
//  obj_class of the return value
//  addr of start of struct
//  i is how many bytes to get thru struct to the var you want
#define BUILD_OBJ_VAR(var_name, obj_class, i) \
  static obj_class get_##var_name(uint16_t addr) { \
    return read_data<obj_class>( addr + i ); \
  } \
  static void set_##var_name(uint16_t addr, obj_class new_var) { \
    write_data<obj_class>( &new_var, addr + i ); \
  }
// Takes name you want the function to be
//  nib_class is obj_class of how many bytes stores the nibble
//  bit_mask of where the nibble is located in the nib_class
//  addr of the start of struct
//  i is how many bytes to get thru struct to the var you want
#define BUILD_OBJ_VAR_NIBBLE(var_name, nib_class, bit_mask, num_bits_to_shift, i) \
  static uint8_t get_##var_name(uint16_t addr) { \
    nib_class result = 0; \
    eReadBlock( (addr + i), (uint8_t*)&result, sizeof(nib_class) ); \
    return (result & (bit_mask << num_bits_to_shift)) >> num_bits_to_shift; \
  } \
  static void set_##var_name(uint16_t addr, nib_class new_var) { \
    nib_class result = 0; \
    eReadBlock( (addr + i), (uint8_t*)&result, sizeof(nib_class) ); \
    result = (result & ~(bit_mask<<num_bits_to_shift)) | (new_var << num_bits_to_shift); \
    eWriteBlock( (addr + i), (uint8_t*)&result, sizeof(nib_class) ); \
  }
/* :: END FUNC BUILDERS:: */


/* :: STRUCTS :: */
struct Color {
  char    name[TEXT_SZ] = "UNTITLED ";
  uint8_t red           = 0;
  uint8_t green         = 0;
  uint8_t blue          = 0;

  BUILD_OBJ_NAME;
  BUILD_OBJ_VAR(red,   uint8_t, 13);
  BUILD_OBJ_VAR(green, uint8_t, 14);
  BUILD_OBJ_VAR(blue,  uint8_t, 15);
};
#define GET_RGB_ADDR(color_addr) \
  read_data<uint8_t>(color_addr+13), \
  read_data<uint8_t>(color_addr+14), \
  read_data<uint8_t>(color_addr+15)
#define GET_RGB(color_id) GET_RGB_ADDR( GET_PARENT(M_COLORS, color_id, sizeof(Color)) )

struct Pedal {
  char    name[TEXT_SZ] = "UNTITLED ";
  uint8_t channel       = 0;

  BUILD_OBJ_NAME;
  BUILD_OBJ_VAR(channel, uint8_t, 13);
};

struct Feature {
  char    name[TEXT_SZ] = "UNTITLED ";
  uint8_t type          = 0;
  uint8_t pitch         = 0;

  BUILD_OBJ_NAME;
  BUILD_OBJ_VAR(type,  uint8_t, 13);
  BUILD_OBJ_VAR(pitch, uint8_t, 14);
};

// For presets and fsw's
struct Parameter {
  union {
    uint16_t data;
    struct {
      unsigned velocity:7;
      unsigned feature:5;
      unsigned pedal:4;
    };
  };

  Parameter() {
    pedal    = NUM_PEDALS;
    feature  = 0;
    velocity = 0;
  }

  BUILD_OBJ_VAR_NIBBLE(pedal,    uint16_t, 0b1111,    12, 0);
  BUILD_OBJ_VAR_NIBBLE(feature,  uint16_t, 0b11111,    7, 0);
  BUILD_OBJ_VAR_NIBBLE(velocity, uint16_t, 0b1111111,  0, 0);

  // Resets all nibbles
  BUILD_OBJ_VAR(data, uint16_t, 0);
};

struct Preset {
  char name[TEXT_SZ] = "UNTITLED ";
  BUILD_OBJ_NAME;
};

#define FSW_MODE_OFF     0  // NONE
#define FSW_MODE_TOGGLE  1  // Press once for on, 2x for off
#define FSW_MODE_CYCLE   2  // Press once for on, 2x for on2, 3x for off
#define FSW_MODE_ONESHOT 3  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_SUBMENU 4  // Change to a different submenu
#define FSW_MODE_PRESET  5  // Change to a different preset
struct Footswitch {
  uint8_t color_id[NUM_COLORS_PER_FSW] = { 0, 1, 3 };

  union {
    struct {
      unsigned mode:3;       // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
                             //   SPECIALTY: 
                             //     4 Switch Submenu,
                             //     5 Jump to preset x,
                             //     6 Switch Preset by n number of presets,
                             //     7 Loop Quantize
      unsigned lp_mode:3;    // 0 OFF, 3 OneShot
                             //   SPECIALTY:
                             //     4 Switch Submenu
                             //     5 Jump to Preset x
                             //     6 Switch Preset by n number of presets,
      unsigned state:2;      // 0 OFF, 1 ON1, 2 ON2
      unsigned press_type:1; // 0 PRESS_TYPE_UP, 1 PRESS_TYPE_DOWN
    };
  };

  Footswitch() {
    mode       = FSW_MODE_TOGGLE;
    lp_mode    = FSW_MODE_OFF;
    state      = 0;
    press_type = PRESS_TYPE_UP;
  }

  void increase_state() {
    state += 1;
    if ( mode == FSW_MODE_CYCLE ) {
      if ( state >= 3 ) state = 0;
    }
    else if ( mode == FSW_MODE_ONESHOT ) {
      state = 0;
    }
    else if ( FSW_MODE_TOGGLE && state >= 2 ) state = 0;
  }

  void run_long_press() {
    if ( lp_mode > 0 ) {
      flash();
    }
  }

//  void save(uint8_t preset_id, uint8_t submenu_id, uint8_t fsw_id) {
//    return write_data<Footswitch>( this, GET_CHILD(M_FSW, preset_id, submenu_id*NUM_FSW_PER_SUBMENU+fsw_id, sizeof(Footswitch), NUM_FSW_PER_PRESET) );
//  }
//
//  // STATIC
//  static Footswitch get(uint8_t preset_id, uint8_t submenu_id, uint8_t fsw_id) {
//    return read_data<Footswitch>( GET_CHILD(M_FSW, preset_id, submenu_id*NUM_FSW_PER_SUBMENU+fsw_id, sizeof(Footswitch), NUM_FSW_PER_PRESET) );
//  }
} fsw[NUM_FSW_PER_PRESET];

struct FSW_Settings {
  uint8_t id;
  uint8_t state;
} fsw_settings;

#define RESULT_MENU                0
#define RESULT_CONFIRM             1
#define RESULT_TEXT_EDIT           2
#define RESULT_VALUE_EDIT          3
#define RESULT_COLOR_EDIT          4
#define RESULT_FSW_MODE_EDIT       5
#define RESULT_FSW_PRESS_TYPE_EDIT 6
struct Option {
  char     name[TEXT_SZ]     = "UNTITLED    ";
  uint8_t  result            = RESULT_MENU;
  uint16_t menu_addr         = 0;
  uint8_t  callback_id       = 0;

  BUILD_OBJ_NAME;
  BUILD_OBJ_VAR(result,      uint8_t,  13);
  BUILD_OBJ_VAR(menu_addr,   uint16_t, 14);
  BUILD_OBJ_VAR(callback_id, uint8_t,  16);
};


#define MENU_MAIN                 0
#define MENU_PRESET               (M_MENUS +  0 * sizeof(Menu))
#define MENU_PRESET_PARAMS        (M_MENUS +  1 * sizeof(Menu))
#define MENU_PRESET_PARAM         (M_MENUS +  2 * sizeof(Menu))
#define MENU_PRESET_PARAM_PEDAL   (M_MENUS +  3 * sizeof(Menu))
#define MENU_PRESET_PARAM_FEATURE (M_MENUS +  4 * sizeof(Menu))
#define MENU_GLOBAL               (M_MENUS +  5 * sizeof(Menu))
#define MENU_PEDALS               (M_MENUS +  6 * sizeof(Menu))
#define MENU_PEDAL                (M_MENUS +  7 * sizeof(Menu))
#define MENU_COLORS               (M_MENUS +  8 * sizeof(Menu))
#define MENU_COLOR                (M_MENUS +  9 * sizeof(Menu))
#define MENU_FEATURES             (M_MENUS + 10 * sizeof(Menu))
#define MENU_FEATURE              (M_MENUS + 11 * sizeof(Menu))
#define MENU_FSW                  (M_MENUS + 12 * sizeof(Menu))
#define MENU_FSW_PARAMS           (M_MENUS + 13 * sizeof(Menu))
#define MENU_FSW_PARAM            (M_MENUS + 14 * sizeof(Menu))
#define MENU_FSW_COLOR            (M_MENUS + 15 * sizeof(Menu))
#define MENU_FSW_LONGPRESS        (M_MENUS + 16 * sizeof(Menu))
struct Menu {
  char     name[TEXT_SZ]     = "UNTITLED    ";
  uint8_t  num_options       = 0;
  uint16_t start_addr        = 0;
  uint8_t  size              = sizeof(Option);
  uint16_t return_addr       = 0;
  uint16_t forward_addr      = 0;
  uint8_t  callback_setup_id = 0;
  uint8_t  callback_run_id   = 0;
  uint8_t  callback_save_id  = 0;

  BUILD_OBJ_NAME;
  BUILD_OBJ_VAR(num_options,       uint8_t,  13);
  BUILD_OBJ_VAR(start_addr,        uint16_t, 14);
  BUILD_OBJ_VAR(size,              uint8_t,  16);
  BUILD_OBJ_VAR(return_addr,       uint16_t, 17);
  BUILD_OBJ_VAR(forward_addr,      uint16_t, 19);
  BUILD_OBJ_VAR(callback_setup_id, uint8_t,  21);
  BUILD_OBJ_VAR(callback_run_id,   uint8_t,  22);
  BUILD_OBJ_VAR(callback_save_id,  uint8_t,  23);
};
/* :: END STRUCTS :: */


/* :: EEPROM MAP :: */
#define M_COLORS        0
#define M_PEDALS        GET_END(M_COLORS,        NUM_COLORS,              sizeof(Color))
#define M_FEATURES      GET_END(M_PEDALS,        NUM_PEDALS,              sizeof(Pedal))
#define M_PRESETS       GET_END(M_FEATURES,      NUM_FEATURES_TOTAL,      sizeof(Feature))
#define M_PRESET_PARAMS GET_END(M_PRESETS,       NUM_PRESETS,             sizeof(Preset))
#define M_FSW           GET_END(M_PRESET_PARAMS, NUM_PRESET_PARAMS_TOTAL, sizeof(Parameter))
#define M_FSW_PARAMS    GET_END(M_FSW,           NUM_FSW_TOTAL,           sizeof(Footswitch))
#define M_MENUS         GET_END(M_FSW_PARAMS,    NUM_FSW_PARAMS_TOTAL,    sizeof(Parameter))
#define M_OPTIONS       GET_END(M_MENUS,         NUM_MENUS,               sizeof(Menu))
#define M_END           GET_END(M_OPTIONS,       NUM_OPTIONS_TOTAL,       sizeof(Option))
/* :: END EEPROM MAP :: */


/* :: EEPROM MACROS :: */
#define IS_IN_PARTITION(part_start, part_end, address) ((part_start<=address && address<part_end) ? true : false)
#define IS_IN_LIST(start_addr, num_items, size, address) ((start_addr<=address && address<=(start_addr+(num_items*size))) ? true : false)
#define IS_IN_PARTITION_COLORS(address)        IS_IN_PARTITION(M_COLORS,        M_PEDALS,        address)
#define IS_IN_PARTITION_PEDALS(address)        IS_IN_PARTITION(M_PEDALS,        M_FEATURES,      address)
#define IS_IN_PARTITION_FEATURES(address)      IS_IN_PARTITION(M_FEATURES,      M_PRESETS,       address)
#define IS_IN_PARTITION_PRESETS(address)       IS_IN_PARTITION(M_PRESETS,       M_PRESET_PARAMS, address)
#define IS_IN_PARTITION_PRESET_PARAMS(address) IS_IN_PARTITION(M_PRESET_PARAMS, M_FSW,           address)
#define IS_IN_PARTITION_FSW(address)           IS_IN_PARTITION(M_FSW,           M_FSW_PARAMS,    address)
#define IS_IN_PARTITION_FSW_PARAMS(address)    IS_IN_PARTITION(M_FSW_PARAMS,    M_MENUS,         address)
#define IS_IN_PARTITION_MENUS(address)         IS_IN_PARTITION(M_MENUS,         M_OPTIONS,       address)
#define IS_IN_PARTITION_OPTIONS(address)       IS_IN_PARTITION(M_OPTIONS,       M_END,           address)

// Get active parent that is not an option struct
// Cant put it earlier since we need the above macros
uint8_t get_active_parent_id_not_option() {
  // This function gets the newest parent that is not an option struct
  // Used for finding the newest object to edit
  // Cant make this in Standard.h, need macros above
  uint8_t result = 0;
  for (uint8_t i=0; i<=GET_ACTIVE_PARENT_ID; i++) {
    result = GET_ACTIVE_PARENT_ID-i;
    if ( !IS_IN_PARTITION_OPTIONS(parents[result]) )
      return result;
  }
  return 0;
}
#define GET_ACTIVE_PARENT_ID_NOT_OPTION get_active_parent_id_not_option()
#define GET_ACTIVE_PARENT_NOT_OPTION    parents[GET_ACTIVE_PARENT_ID_NOT_OPTION]
/* :: ENDEEPROM MACROS :: */
