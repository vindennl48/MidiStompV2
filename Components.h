#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>
#include "Helpers.h"

/* EEPROM MAP */
#define NUM_PRESETS             20
#define NUM_COLORS              50
#define NUM_PEDALS              8
#define NUM_FEATURES_PER_PEDAL  32
#define NUM_FEATURES            (NUM_PEDALS*NUM_FEATURES_PER_PEDAL)
#define NUM_PARAMS_PER_PRESET   10
#define NUM_SUBMENUS_PER_PRESET 4
#define NUM_FSW_PER_SUBMENU     4
#define NUM_FSW_PER_PRESET      (NUM_SUBMENUS_PER_PRESET*NUM_FSW_PER_SUBMENU)
#define NUM_FSW                 (NUM_FSW_PER_PRESET*NUM_PRESETS)
#define NUM_STATES_PER_FSW      4  // 3 plus 1 for Long Press
#define NUM_PARAMS_PER_STATE    (NUM_PARAMS_PER_PRESET)
#define NUM_PARAMS_PER_FSW      (NUM_PARAMS_PER_STATE*NUM_STATES_PER_FSW)

#define MAP_COLOR        10
#define MAP_PRESET       (MAP_COLOR        + (NUM_COLORS            * COLOR_SZ)   + 1)
#define MAP_PEDAL        (MAP_PRESET       + (NUM_PRESETS           * PRESET_SZ)  + 1)
#define MAP_FEATURE      (MAP_PEDAL        + (NUM_PEDALS            * PEDAL_SZ)   + 1)
#define MAP_FSW          (MAP_FEATURE      + (NUM_FEATURES          * FEATURE_SZ) + 1)
#define MAP_PRESET_PARAM (MAP_FSW          + (NUM_FSW               * FSW_SZ)     + 1)
#define MAP_PARAM        (MAP_PRESET_PARAM + (NUM_PARAMS_PER_PRESET * PARAM_SZ)   + 1)
/* END EEPROM MAP */


#define COLOR_SZ 16
struct Color : ObjName {
  uint16_t id;

  Color();
  Color(uint16_t);

  uint16_t addr();                    // Get the eeprom addr of current
  uint8_t  at(uint8_t);               // Select color channel 1-3/RGB
  void     set_at(uint8_t, uint8_t);  // Set color channel 1-3/RGB
};


#define FEATURE_SZ 15
struct Feature : ObjName {
  uint16_t id;

  Feature();
  Feature(uint16_t);

  uint16_t addr();              // Get the eeprom addr of current
  uint8_t  type();              // Get type for current Feature
  void     set_type(uint8_t);   // Set type for current Feature
  uint8_t  pitch();             // Get pitch for current Feature
  void     set_pitch(uint8_t);  // Set pitch for current Feature
};

#define PEDAL_SZ 14
struct Pedal : ObjName {
  uint16_t id;

  Pedal();
  Pedal(uint16_t);

  uint16_t addr();               // Get the eeprom addr of current
  uint8_t  channel();            // Get chan for current pedal
  void     set_channel(uint8_t); // Change chan of Pedal midi output
  Feature  feature(uint8_t);     // Select feature of pedal 1-32
};

#define PARAM_SZ 2
struct Param {
  uint16_t id;
  uint8_t  is_preset;

  union {
    uint16_t data;
    struct {
      unsigned d_velocity:7;
      unsigned d_feature:5;
      unsigned d_pedal_id:4;
    };
  };

  Param();
  Param(uint16_t, uint8_t);

  uint16_t addr();                // Get the eeprom addr of current
  void     save();                // Saves all the nibbles at once
  Pedal    pedal();               // Get pedal for current Param
  void     set_pedal(Pedal);      // Set pedal for current Param
  Feature  feature();             // Get Feature for current Param
  void     set_feature(Feature);  // Set Feature for current Param
  uint8_t  velocity();            // Get Velocity for current Param
  void     set_velocity(uint8_t); // Set Velocity for current Param
  void     send_midi();           // Send midi for current Param
};

#define FSW_SZ           5
#define FSW_MODE_OFF     0  // NONE
#define FSW_MODE_TOGGLE  1  // Press once for on, 2x for off
#define FSW_MODE_CYCLE   2  // Press once for on, 2x for on2, 3x for off
#define FSW_MODE_ONESHOT 3  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_SUBMENU 4  // Change to a different submenu
#define FSW_MODE_PRESET  5  // Change to a different preset
struct Footswitch {
  uint16_t id;
  uint8_t  color[3];
  //uint8_t  color[3] = { 0, 1, 3 };

  union {
    uint16_t data;
    struct {
      unsigned d_mode:3;       // 0 OFF, 1 Toggle, 2 Cycle, 3 OneShot
                               //   SPECIALTY: 
                               //     4 Switch Submenu,
                               //     5 Jump to preset x,
                               //     6 Switch Preset by n number of presets,
                               //     7 Loop Quantize
      unsigned d_lp_mode:3;    // 0 OFF, 3 OneShot
                               //   SPECIALTY:
                               //     4 Switch Submenu
                               //     5 Jump to Preset x
                               //     6 Switch Preset by n number of presets,
      unsigned d_state:2;      // 0 OFF, 1 ON1, 2 ON2
      unsigned d_press_type:1; // 0 PRESS_TYPE_UP, 1 PRESS_TYPE_DOWN
    };
  };

  Footswitch();
  Footswitch(uint16_t);

  uint16_t addr();                  // Get the eeprom addr of current
  void     setup();                 // setup for creation
  Param    param(uint8_t);          // Get param with state assumed
  Param    param(uint8_t, uint8_t); // Get param with providing state
  Param    lp_param(uint8_t);       // Get param from long press

  uint8_t mode();                   // Get mode
  void    set_mode(uint8_t);        // Set mode
  uint8_t lp_mode();                // Get lp_mode
  void    set_lp_mode(uint8_t);     // Set lp_mode
  uint8_t press_type();             // Get press_type
  void    set_press_type(uint8_t);  // Set press_type
  void    save();                   // save all the nibbles at once

  void update_state();  // run when fsw is pressed
  void send_midi();     // Send midi for current state
  void lp_send_midi();  // Send midi for current state
}; // extern footswitches[NUM_FSW_PER_PRESET];

#define PRESET_SZ 13
struct Preset : ObjName {
  uint16_t id;
  uint8_t  submenu_id;

  Preset();
  Preset(uint16_t);

  uint16_t addr();                    // Get the eeprom addr of current
  Footswitch* fsw(uint8_t);           // Get fsw from RAM with state assumed
  Footswitch* fsw(uint8_t, uint8_t);  // Get fsw from RAM with providing state

  // Get fsw from eeprom with state assumed
  Footswitch get_fsw_from_eeprom(uint8_t);
  // Get fsw from eeprom with providing state
  Footswitch get_fsw_from_eeprom(uint8_t, uint8_t);
};

#endif
