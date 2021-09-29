/* What I'm essentially looking for is a library that can treat the eeprom like
 * a hard drive..
 *
 * Will need to have a first few vars on the EEPROM
 *   - Sofware Version
 *   - EEPROM Version (database version)
 *
 * JUST rethought a couple things.. if on preset change, we could pull all the
 * data we needed for the preset, ie. Preset/FSW/Params, then stick all those
 * in a reserved part of the EEPROM, all of these functions would then turn
 * into super easy functions.  We would operate everything off of that section
 * of the EEPROM until we saved it or discarded it.  If we tried to change
 * presets without saving, we would run into a prompt asking to save first.
 *
 * There could be a mode dedicated to shows, or mby some way to boot the pedal
 * to start in song mode.  that way when we make changes to the FSW when dancing
 * on the pedals, then we wouldn't be interrupted when switching to other songs.
 *
 *
 * */

// Just want to remember this macro
#define MOD(absolute, div_by) ((absolute+div_by)%div_by) // returns relative pos

struct Text {
  char text[13] = {' '};
  // Bunch of functions and overloads to deal with text

  // this allows you to use char_arr literals ie:
  //   Text.set_text("UNTITLED");
  // instead of having to declare a var first and then send it to the func
  template <int N>
  void set_text(char const (&c)[N]);
};


struct ObjName {
  Text name();
  void set_name(Text);
};

struct Color : ObjName {
  uint8_t r();
  void    set_r(uint8_t);
  uint8_t g();
  void    set_g(uint8_t);
  uint8_t b();
  void    set_b(uint8_t);
  uint8_t at(uint8_t); // get color by i
};

struct Feature : ObjName {
  uint8_t type();
  void    set_type(uint8_t);
  uint8_t pitch();
  void    set_pitch(uint8_t);
};

struct Pedal : ObjName {
  uint8_t channel();
  void    set_channel(uint8_t);
  Feature feature(uint8_t);
};

/* The whole idea here is that we can do something like this.. */
// Pedal adam;
// uint8_t type = adam.feature(2).type();

struct Param {
  Pedal   pedal();
  void    set_pedal(uint8_t);
  Feature feature();
  void    set_feature(uint8_t);
  void    send_midi() {
    // put a feature in here to block all outgoing midi IF the baudrate is not
    // equal to 31250 so that we can quickly switch between debugging modes
  }
};

struct Footswitch {
  uint8_t color[3] = { 0, 1, 3 };

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

  Param param(uint8_t);          // state is assumed
  Param param(uint8_t, uint8_t); // provide state
  Param param_lp(uint8_t);       // long press params

  void update_state();  // run when fsw is pressed

  void send_midi() {
    for (int i=0; i<32; i++) param(i).send_midi();
  }
  void send_midi_lp() {
    for (int i=0; i<32; i++) param_lp(i).send_midi();
  }
  void save();
};

struct Preset : ObjName {
  uint8_t    preset_id;
  uint8_t    submenu;   // 4 per preset
  Footswitch fsw[16];   // 4 per submenu

  void       at(uint8_t);     // change preset
  Footswitch fsw_at(uint8_t); // FSW 1-4 for selected submenu
  void       save() {         // saves all the FSW
    for (int i=0; i<16; i++) fsw[i].save();
  }
};

/*
 * Preset steel;
 * uint8_t channel = steel.fsw[0].param(0).pedal().channel();
 * */

