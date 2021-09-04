/* :: GENERAL DEFINES :: */
#define NUM_CHAN 3  // Color channels, ie. red, green, blue
/* :: END GENERAL DEFINES :: */


/* :: HELPFUL MACROS :: */
#define GET_NIBBLE(input, mask, shift)  ((mask & input) >> shift)

#define GET_PARENT(start, id, size) (start + (id*size))
#define GET_CHILD(start, parent_id, id, size, num_in_parent) (start + (parent_id*size*num_in_parent) + (id*size))
#define GET_END(start, quantity, size) ((uint16_t)start + ((uint16_t)quantity*(uint16_t)size))
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
/* :: END OBJECT COUNTS :: */


/* :: OBJECT SIZES :: */
#define COLOR_SZ        16
#define PEDAL_SZ        14
#define FEATURE_SZ      15
#define PRESET_SZ       13
#define PRESET_PARAM_SZ 2
#define FSW_SZ          5
#define FSW_PARAM_SZ    2
/* :: END OBJECT SIZES :: */


/* :: EEPROM MAP :: */
#define M_COLORS        0
#define M_PEDALS        GET_END(M_COLORS,        NUM_COLORS,              COLOR_SZ)
#define M_FEATURES      GET_END(M_PEDALS,        NUM_PEDALS,              PEDAL_SZ)
#define M_PRESETS       GET_END(M_FEATURES,      NUM_FEATURES_TOTAL,      FEATURE_SZ)
#define M_PRESET_PARAMS GET_END(M_PRESETS,       NUM_PRESETS,             PRESET_SZ)
#define M_FSW           GET_END(M_PRESET_PARAMS, NUM_PRESET_PARAMS_TOTAL, PRESET_PARAM_SZ)
#define M_FSW_PARAMS    GET_END(M_FSW,           NUM_FSW_TOTAL,           FSW_SZ)
#define M_END           GET_END(M_FSW_PARAMS,    NUM_FSW_PARAMS_TOTAL,    FSW_PARAM_SZ)
/* :: END EEPROM MAP :: */


/* :: FUNC BUILDERS:: */
// i: what text buffer to apply to, 0 or 1
#define BUILD_OBJ_NAME(start, size) \
  static void get_name(uint8_t id, uint8_t i) { \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  } \
  static void set_name(uint8_t id, uint8_t i) { \
    eWriteBlock( GET_PARENT(start, id, size), (uint8_t*)text[i], TEXT_SZ ); \
  }
// i: amount of bytes to get to variable
#define BUILD_OBJ_VARIABLE(var_name, obj_class, start, size, i) \
  static obj_class get_##var_name(uint8_t id) { \
    return read_data<obj_class>( GET_PARENT(start, id, size) + i ); \
  } \
  static void set_##var_name(uint8_t id, obj_class new_var) { \
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
  static uint8_t get_##var_name(uint8_t id) { \
    nib_class result = 0; \
    eReadBlock( GET_PARENT(start, id, size), (uint8_t*)&result, sizeof(nib_class) ); \
    return (result & (bit_mask << num_bits_to_shift)) >> num_bits_to_shift; \
  } \
  static void set_##var_name(uint8_t id, nib_class new_var) { \
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
  BUILD_OBJ_NAME(M_FEATURES, FEATURE_SZ);
  BUILD_OBJ_VARIABLE(type,  uint8_t, M_FEATURES, FEATURE_SZ, 13);
  BUILD_OBJ_VARIABLE(pitch, uint8_t, M_FEATURES, FEATURE_SZ, 14);
};

struct PresetParam {
  // unsigned pedal:4;
  // unsigned feature:5;
  // unsigned velocity:7;
  BUILD_OBJ_VAR_NIBBLE(pedal,    uint16_t, 0b1111,    M_PRESET_PARAMS, PRESET_PARAM_SZ, 12);
  BUILD_OBJ_VAR_NIBBLE(feature,  uint16_t, 0b11111,   M_PRESET_PARAMS, PRESET_PARAM_SZ, 7);
  BUILD_OBJ_VAR_NIBBLE(velocity, uint16_t, 0b1111111, M_PRESET_PARAMS, PRESET_PARAM_SZ, 0);
  // Resets all nibbles
  BUILD_OBJ_VARIABLE(data, uint16_t, M_PRESET_PARAMS, PRESET_PARAM_SZ, 0);
};

struct FswParam {
  // unsigned pedal:4;
  // unsigned feature:5;
  // unsigned velocity:7;
  BUILD_OBJ_VAR_NIBBLE(pedal,    uint16_t, 0b1111,    M_FSW_PARAMS, FSW_PARAM_SZ, 12);
  BUILD_OBJ_VAR_NIBBLE(feature,  uint16_t, 0b11111,   M_FSW_PARAMS, FSW_PARAM_SZ, 7);
  BUILD_OBJ_VAR_NIBBLE(velocity, uint16_t, 0b1111111, M_FSW_PARAMS, FSW_PARAM_SZ, 0);
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
