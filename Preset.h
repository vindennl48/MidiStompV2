#ifndef PRESET_H
#define PRESET_H

#define NUM_PEDAL_PARAMS 16
#define NUM_FSW          4
#define NUM_STATES       3

struct Color {
  String  name;
  uint8_t r,g,b;
};

struct Param {
  String name;

  union {
    struct {
      unsigned type:1;
      unsigned pitch:7;
    };
  };
};

struct Pedal {
  String  name;
  uint8_t Channel;
  Param   params[NUM_PARAMS];
};

struct Footswitch {
  Color   colors[NUM_STATES];
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
};

struct Preset {
  String     name;
  boolean    is_dirty;
  Footswitch fsw[NUM_FSW];
};

#endif
