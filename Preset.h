#ifndef PRESET_H
#define PRESET_H

#define NUM_PEDAL_PARAMS 20
#define NUM_FSW          4
#define NUM_STATES       3

#define STR_LEN     12
#define STR_LEN_MAX STR_LEN+1


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

struct Pedal {
  // 14 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t channel           = 0;
  // 16 params
};

#define FSW_MODE_OFF     0
#define FSW_MODE_TOGGLE  2
#define FSW_MODE_CYCLE   3
#define FSW_MODE_ONESHOT 1
struct Footswitch {
  // 8 bytes
  uint8_t colors[NUM_STATES] = { 0, 1, 2 };
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

struct Preset {
  // 14 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  boolean is_dirty          = false;
  // 4 footswitches
  // 1 main footswitch menu + 3 footswitch sub-menus
};

#endif
