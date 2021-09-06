uint8_t f_colors() {
  // Set the LED colors to match the selected color
  uint8_t color_id = GET_ID_FROM_ADDR(M_COLORS, GET_ACTIVE_PARENT_NOT_OPTION, COLOR_SZ);
  leds_set(
    Color::get_red(color_id),
    Color::get_green(color_id),
    Color::get_blue(color_id)
  );

  return true;
}

uint8_t f_preset_params_run() {
  return true;
}

uint8_t f_preset_params_setup() {
  return true;
}

uint8_t f_global() {
  leds_set(0,0,0);
  return true;
}

#define F_NONE                0
#define F_COLORS              1
#define F_PRESET_PARAMS_RUN   2
#define F_PRESET_PARAMS_SETUP 3
#define F_GLOBAL              4

typedef uint8_t (*Callback)();

Callback get_callback(uint8_t id) {
  switch(id) {
    case F_COLORS:              return &f_colors;
    case F_PRESET_PARAMS_RUN:   return &f_preset_params_run;
    case F_PRESET_PARAMS_SETUP: return &f_preset_params_setup;
    case F_GLOBAL:              return &f_global;
  };

  return nullptr;
}
