/* :: GENERAL DEFINES :: */
#define NUM_CHAN 3  // Color channels, ie. red, green, blue
/* :: END GENERAL DEFINES :: */


/* :: HELPFUL MACROS :: */
#define GET_NIBBLE(input, mask, shift)  ((mask & input) >> shift)

// These help get the start address in eeprom
#define GET_PARENT(start, id, size) (start + (id*size))
#define GET_CHILD(start, parent_id, id, size, num_in_parent) (start + (parent_id*size*num_in_parent) + (id*size))
#define GET_END(start, quantity, size) ((uint16_t)start + ((uint16_t)quantity*(uint16_t)size))

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
#define NUM_MENUS                    10
#define NUM_OPTIONS_PER_MENU         10
#define NUM_OPTIONS_TOTAL            (NUM_MENUS*NUM_OPTIONS_PER_MENU)
/* :: END OBJECT COUNTS :: */


/* :: OBJECT SIZES :: */
#define COLOR_SZ        16
#define PEDAL_SZ        14
#define FEATURE_SZ      15
#define PRESET_SZ       13
#define PRESET_PARAM_SZ 2
#define FSW_SZ          5
#define FSW_PARAM_SZ    2
#define MENU_SZ         14
#define OPTION_SZ       13
/* :: END OBJECT SIZES :: */


/* :: EEPROM MAP :: */
#define M_COLORS        0
#define M_PEDALS        GET_END(M_COLORS,        NUM_COLORS,              COLOR_SZ)
#define M_FEATURES      GET_END(M_PEDALS,        NUM_PEDALS,              PEDAL_SZ)
#define M_PRESETS       GET_END(M_FEATURES,      NUM_FEATURES_TOTAL,      FEATURE_SZ)
#define M_PRESET_PARAMS GET_END(M_PRESETS,       NUM_PRESETS,             PRESET_SZ)
#define M_FSW           GET_END(M_PRESET_PARAMS, NUM_PRESET_PARAMS_TOTAL, PRESET_PARAM_SZ)
#define M_FSW_PARAMS    GET_END(M_FSW,           NUM_FSW_TOTAL,           FSW_SZ)
#define M_MENUS         GET_END(M_FSW_PARAMS,    NUM_FSW_PARAMS_TOTAL,    FSW_PARAM_SZ)
#define M_OPTIONS       GET_END(M_MENUS,         NUM_MENUS,               MENU_SZ)
#define M_END           GET_END(M_OPTIONS,       NUM_OPTIONS_TOTAL,       OPTION_SZ)
/* :: END EEPROM MAP :: */


/* :: FUNC BUILDERS:: */
// i: what text buffer to apply to, 0 or 1
#define BUILD_OBJ_NAME(start, size) \
  static void get_name(uint16_t id, uint8_t i) { \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  } \
  static void set_name(uint16_t id, uint8_t i) { \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  }
#define BUILD_OBJ_NAME_1_PARENT(start, size, num_children_in_parent) \
  static void get_name(uint16_t parent_id, uint16_t id, uint8_t i) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  } \
  static void set_name(uint16_t parent_id, uint16_t id, uint8_t i) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  }
// i: amount of bytes to get to variable
#define BUILD_OBJ_VARIABLE(var_name, obj_class, start, size, i) \
  static obj_class get_##var_name(uint16_t id) { \
    return read_data<obj_class>( GET_PARENT(start, id, size) + i ); \
  } \
  static void set_##var_name(uint16_t id, obj_class new_var) { \
    write_data<obj_class>( &new_var, GET_PARENT(start, id, size) + i ); \
  }
#define BUILD_OBJ_VARIABLE_1_PARENT(var_name, obj_class, start, size, i, num_children_in_parent) \
  static obj_class get_##var_name(uint16_t parent_id, uint16_t id) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    return read_data<obj_class>( GET_PARENT(start, id, size) + i ); \
  } \
  static void set_##var_name(uint16_t parent_id, uint16_t id, obj_class new_var) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    write_data<obj_class>( &new_var, GET_PARENT(start, id, size) + i ); \
  }
#define BUILD_OBJ_VARIABLE_2_PARENT(var_name, obj_class, start, size, i, num_children_in_parent2, num_parent2_in_parent1 ) \
  static obj_class get_##var_name(uint16_t parent1_id, uint16_t parent2_id, uint16_t id) { \
    id = GET_ABS_CHILD_ID_2(parent1_id, parent2_id, id, num_children_in_parent2, num_parent2_in_parent1); \
    return read_data<obj_class>( GET_PARENT(start, id, size) + i ); \
  } \
  static void set_##var_name(uint16_t parent1_id, uint16_t parent2_id, uint16_t id, obj_class new_var) { \
    id = GET_ABS_CHILD_ID_2(parent1_id, parent2_id, id, num_children_in_parent2, num_parent2_in_parent1); \
    write_data<obj_class>( &new_var, GET_PARENT(start, id, size) + i ); \
  }
// nib_obj: object type that will be pulled from eeprom before getting nibble, ie:
//          if nibble is stored in a uint16_t
// nib_class: class type to retrieve from eeprom, ie. uint8_t/uint16_t
// bit_mask: binary of bits to keep.  ie top 4 least significant bits of a uint16_t is 0b1111.
//           The num_bits_to_shift will shift this mask up to the correct location
// start: start address in eeprom of struct type
// size: size of struct that contains this nibble (used to find address in eeprom of nibble)
// num_bits_to_shift: the number of bits to shift the bit_mask to get to the proper nibble location,
//                    ie. if 4 least significant bits of uint16_t, this will be 12
#define BUILD_OBJ_VAR_NIBBLE(var_name, nib_class, bit_mask, start, size, num_bits_to_shift) \
  static uint8_t get_##var_name(uint16_t id) { \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    return (result & (bit_mask << num_bits_to_shift)) >> num_bits_to_shift; \
  } \
  static void set_##var_name(uint16_t id, nib_class new_var) { \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    result = (result & ~(bit_mask<<num_bits_to_shift)) | (new_var << num_bits_to_shift); \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
  }
#define BUILD_OBJ_VAR_NIBBLE_1_PARENT(var_name, nib_class, bit_mask, start, size, num_bits_to_shift, num_children_in_parent) \
  static uint8_t get_##var_name(uint16_t parent_id, uint16_t id) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    return (result & (bit_mask << num_bits_to_shift)) >> num_bits_to_shift; \
  } \
  static void set_##var_name(uint16_t parent_id, uint16_t id, nib_class new_var) { \
    id = GET_ABS_CHILD_ID(parent_id, id, num_children_in_parent); \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    result = (result & ~(bit_mask<<num_bits_to_shift)) | (new_var << num_bits_to_shift); \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
  }
#define BUILD_OBJ_VAR_NIBBLE_2_PARENT(var_name, nib_class, bit_mask, start, size, num_bits_to_shift, num_children_in_parent2, num_parent2_in_parent1) \
  static uint8_t get_##var_name(uint16_t parent1_id, uint16_t parent2_id, uint16_t id) { \
    id = GET_ABS_CHILD_ID_2(parent1_id, parent2_id, id, num_children_in_parent2, num_parent2_in_parent1); \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    return (result & (bit_mask << num_bits_to_shift)) >> num_bits_to_shift; \
  } \
  static void set_##var_name(uint16_t parent1_id, uint16_t parent2_id, uint16_t id, nib_class new_var) { \
    id = GET_ABS_CHILD_ID_2(parent1_id, parent2_id, id, num_children_in_parent2, num_parent2_in_parent1); \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    result = (result & ~(bit_mask<<num_bits_to_shift)) | (new_var << num_bits_to_shift); \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
  }
/* :: END FUNC BUILDERS:: */


/* :: STRUCTS :: */
struct Color {
  BUILD_OBJ_NAME(M_COLORS, COLOR_SZ);
  BUILD_OBJ_VARIABLE(red,   uint8_t, M_COLORS, COLOR_SZ, 13);
  BUILD_OBJ_VARIABLE(green, uint8_t, M_COLORS, COLOR_SZ, 14);
  BUILD_OBJ_VARIABLE(blue,  uint8_t, M_COLORS, COLOR_SZ, 15);
};

struct Pedal {
  BUILD_OBJ_NAME(M_PEDALS, PEDAL_SZ);
  BUILD_OBJ_VARIABLE(channel, uint8_t, M_PEDALS, PEDAL_SZ, 13);
};

struct Feature {
  BUILD_OBJ_NAME_1_PARENT(M_FEATURES, FEATURE_SZ, NUM_FEATURES_PER_PEDAL);
  BUILD_OBJ_VARIABLE_1_PARENT(type,  uint8_t, M_FEATURES, FEATURE_SZ, 13, NUM_FEATURES_PER_PEDAL);
  BUILD_OBJ_VARIABLE_1_PARENT(pitch, uint8_t, M_FEATURES, FEATURE_SZ, 14, NUM_FEATURES_PER_PEDAL);
};

struct PresetParam {
  // unsigned pedal:4;
  // unsigned feature:5;
  // unsigned velocity:7;
  BUILD_OBJ_VAR_NIBBLE_1_PARENT(pedal,    uint16_t, 0b1111,    M_PRESET_PARAMS, PRESET_PARAM_SZ, 12, NUM_PRESET_PARAMS_PER_PRESET);
  BUILD_OBJ_VAR_NIBBLE_1_PARENT(feature,  uint16_t, 0b11111,   M_PRESET_PARAMS, PRESET_PARAM_SZ, 7 , NUM_PRESET_PARAMS_PER_PRESET);
  BUILD_OBJ_VAR_NIBBLE_1_PARENT(velocity, uint16_t, 0b1111111, M_PRESET_PARAMS, PRESET_PARAM_SZ, 0 , NUM_PRESET_PARAMS_PER_PRESET);
  // Resets all nibbles
  BUILD_OBJ_VARIABLE(data, uint16_t, M_PRESET_PARAMS, PRESET_PARAM_SZ, 0);
};

struct FswParam {
  // unsigned pedal:4;
  // unsigned feature:5;
  // unsigned velocity:7;
  BUILD_OBJ_VAR_NIBBLE_2_PARENT(pedal,    uint16_t, 0b1111,    M_FSW_PARAMS, FSW_PARAM_SZ, 12, NUM_FSW_PER_SUBMENU, NUM_SUBMENUS_PER_PRESET);
  BUILD_OBJ_VAR_NIBBLE_2_PARENT(feature,  uint16_t, 0b11111,   M_FSW_PARAMS, FSW_PARAM_SZ, 7 , NUM_FSW_PER_SUBMENU, NUM_SUBMENUS_PER_PRESET);
  BUILD_OBJ_VAR_NIBBLE_2_PARENT(velocity, uint16_t, 0b1111111, M_FSW_PARAMS, FSW_PARAM_SZ, 0 , NUM_FSW_PER_SUBMENU, NUM_SUBMENUS_PER_PRESET);
  // Resets all nibbles
  BUILD_OBJ_VARIABLE(data, uint16_t, M_FSW_PARAMS, FSW_PARAM_SZ, 0);
};

struct Preset {
  BUILD_OBJ_NAME(M_PRESETS, PRESET_SZ);
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

  void save(uint8_t preset_id, uint8_t submenu_id, uint8_t fsw_id) {
    return write_data<Footswitch>( this, GET_CHILD(M_FSW, preset_id, submenu_id*NUM_FSW_PER_SUBMENU+fsw_id, FSW_SZ, NUM_FSW_PER_PRESET) );
  }

  // STATIC
  static Footswitch get(uint8_t preset_id, uint8_t submenu_id, uint8_t fsw_id) {
    return read_data<Footswitch>( GET_CHILD(M_FSW, preset_id, submenu_id*NUM_FSW_PER_SUBMENU+fsw_id, FSW_SZ, NUM_FSW_PER_PRESET) );
  }
};

/* :: END STRUCTS :: */


/* :: MENU STRUCTS :: */
#define MENU_MAIN          0
#define MENU_PRESET        1
#define MENU_PRESET_PARAMS 2
#define MENU_PRESET_PARAM  3
#define MENU_GLOBAL        4
struct Menu {
  // Variables we need
  //   - number of options
  //   - start address of options
  //   - size inbetween options
  // On complete, selected option returns:
  //   - either editor or another menu
  //   - number of options
  //   - start address of options
  //   - size inbetween options
  // Also create menus for the ListLoop, we can store the vars
  // for start address, size, and num options there

  // Need a global var to store the section of eeprom that we are trying to edit

  BUILD_OBJ_NAME(M_MENUS, MENU_SZ);
  BUILD_OBJ_VARIABLE(num_options,    uint8_t,  M_MENUS, MENU_SZ, 13);
  BUILD_OBJ_VARIABLE(start_addr,     uint16_t, M_MENUS, MENU_SZ, 14);
  BUILD_OBJ_VARIABLE(size,           uint8_t,  M_MENUS, MENU_SZ, 16);
  BUILD_OBJ_VARIABLE(menu_return_id, uint8_t,  M_MENUS, MENU_SZ, 17); // gives the ID of the menu to return to

  // For list-loop selection, we need to know what menu to go to after
  BUILD_OBJ_VARIABLE(menu_forward_id, uint8_t,  M_MENUS, MENU_SZ, 19);

  // callback id to run every time we switch between options, ie. for changing the LED
  // colors when switching between color choices
  BUILD_OBJ_VARIABLE(callback_id,    uint8_t,  M_MENUS, MENU_SZ, 18);

  // need var to know if we are in a standard menu with standard options or
  // if we are in a list-loop and need a different action on the way out
  //   - ListLoop
  //     - Object eeprom address selected goes in global var
  //     - need a var in the menu object to know what menu to jump to next
};

#define RESULT_MENU       0
#define RESULT_CONFIRM    1
#define RESULT_TEXT_EDIT  2
#define RESULT_VALUE_EDIT 3
#define RESULT_COLOR_EDIT 4
#define RESULT_MIDI_EDIT  5

#define CALL_NONE 0
struct Option {
  BUILD_OBJ_NAME_1_PARENT(M_OPTIONS, OPTION_SZ, NUM_OPTIONS_PER_MENU);

  // menu, confirm, textEdit, valueEdit, colorEdit, midiEdit, ColorSelect, PedalSelect, PedalParamSelect.. ?
  BUILD_OBJ_VARIABLE_1_PARENT(result,      uint8_t, M_OPTIONS, OPTION_SZ, 13, NUM_OPTIONS_PER_MENU);
  // menu id of next menu item
  BUILD_OBJ_VARIABLE_1_PARENT(menu_id,     uint8_t, M_OPTIONS, OPTION_SZ, 14, NUM_OPTIONS_PER_MENU);
  // callback id to run on selection of this option, before switching to next menu
  BUILD_OBJ_VARIABLE_1_PARENT(callback_id, uint8_t, M_OPTIONS, OPTION_SZ, 15, NUM_OPTIONS_PER_MENU);
};
/* :: END MENU STRUCTS :: */



#ifdef NOTES
- Need 2 parents
uint16_t parent[2] = { 0 };

- What do we know for TextEdit:
  - ALL texts that we are going to be editing are the first 13 bytes of a struct
  - SO if we do have the start location of a struct and we enter into a textEdit,
    it will ALWAYS edit the 13 bytes at the start location.

- What do we know for ValueEdit:
  - We will have the eeprom start address for the struct
  - We can add a variable to the menu option to add bytes to the start address to get
    the location of the byte we are trying to edit.. ie:
      - Select pedal, this puts start address in global parent variable
      - Scroll thru pedal settings menu and select CHANNEL option
      - This option has an extra variable that tells the menu function this channel
        variable is at the 13th byte of the pedal struct.
      - When clicked, parent 2 variable is filled with the location of byte to be edited
      - ValueEdit opens and edits the selected struct's variable

- ColorEdit
  - We will set the parent address as the first byte for the 3 channels
  - The color edit will pull in the 3 bytes from that address and edit those

- MidiEdit (CBOBOX)
  - Same thing as the ColorEdit, except the options will be stored in the editor as
    F("NOTE"), F("CC"), F("PC"), etc.  This macro stores the strings in the Arduino
    eeprom on the chip to reduce program size.
  - When that option is selected, its corrolated integer value is stored at the 
    eeprom address.

- Color/Pedal/PedalParam Select
  - If the option is selected in the menu options, this will be hard-coded in the
    menu function.  If Color is selected, it will iterate thru the color choices and
    return the ID of the color selected.  This ID will be written into the byte of
    the eeprom address globally recorded.
  - These select menus will start on the number that is already selected,  If none is
    selected, then it starts on 0.

- Preset Param Edit
  - When in the preset menu, if you select 'PARAMS', we need a callback function to
    find the eeprom address of the first PresetParam to start looping from.

- Have the parent field as the start address of the object so..
  when you enter the Preset menu and select the 'name' option,
  the program takes the option text and sets that as the title 

- looping through pedals
  - once we select a pedal, that pedal number is set as the first parent
  - 


#endif
