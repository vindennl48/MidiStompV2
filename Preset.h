#ifndef PRESET_H
#define PRESET_H

#define NUM_PEDAL_PARAMS 20
#define NUM_FSW          4
#define NUM_STATES       3

#define STR_LEN     12
#define STR_LEN_MAX STR_LEN+1

struct Color {
  // 16 bytes
  char    name[STR_LEN_MAX] = "UNTITLED";
  uint8_t r,g,b             = 0;
};

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

struct Footswitch {
  // 8 bytes
  uint8_t colors[NUM_STATES];
  uint8_t velocities[NUM_STATES];

  // States of footswitch
  union {
    struct {
      unsigned mode:4;
      unsigned state:4;
    };
  };

  // Pedal Param = PP
  union {
    struct {
      unsigned pedal:4;
      unsigned param:4;
    };
  };

  Footswitch() {
    this->mode  = 0;
    this->state = 0;
    this->pedal = 0;
    this->param = 0;
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
