#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H


struct Footswitch {
  //uint8_t state       = 0;      // 0=toggle, 1=momentary, 2=submenu, 3=preset
  //bool    quick_press = false;  // if true, no long press available
  //uint8_t submenu     = 0;      // submenu id to jump to
  //uint8_t preset      = 0;      // preset id to jump to
  union {
    uint12_t data = 0;
    struct {
      unsigned state:2;        // 0=toggle, 1=momentary, 2=submenu, 3=preset
      unsigned quick_press:1;  // if true, no long press available
      unsigned submenu:2;      // submenu id to jump to
      unsigned preset:6;       // preset id to jump to
    }
  };
  uint8_t color_id[3];          // [ inactive, active#1, active#2 ]

  struct MidiOut {
    union {
      uint16_t data = 0;
      struct {
        unsigned pedal_id:4; // 16 devices
        unsigned param_id:4; // 16 params
        unsigned value:7;    // 0-127
      };
    };
  } midi_out[3][10];

} __attributes__((packed));


#endif
