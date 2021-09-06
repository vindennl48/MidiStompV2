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
  uint16_t preset_param_id = GET_ID_FROM_ADDR(M_PRESET_PARAMS, GET_ACTIVE_PARENT_NOT_OPTION, PRESET_PARAM_SZ);
  uint8_t  pedal_id        = PresetParam::get_pedal(preset_param_id);
  uint8_t  feature_id      = PresetParam::get_feature(preset_param_id);

  if ( pedal_id == NUM_PEDALS )
    memcpy(text[TXT_BUF_2], "EMPTY       ", TEXT_SZ);
  else {
    Pedal::get_name(pedal_id, TXT_BUF_2);
    Feature::get_name(pedal_id, feature_id, TXT_BUF_1);

    text[TXT_BUF_2][5] = ' ';
    for (uint8_t i=6; i<TEXT_SZ; i++) {
      text[TXT_BUF_2][i] = text[TXT_BUF_1][i-6];
    }
  }
  return true;
}

uint8_t f_preset_params_setup() {
  uint8_t preset_id = GET_ID_FROM_ADDR(M_PRESETS, GET_ACTIVE_PARENT_NOT_OPTION, PRESET_SZ);
  alt_start_addr = GET_CHILD(M_PRESET_PARAMS, preset_id, 0, PRESET_PARAM_SZ, NUM_PRESET_PARAMS_PER_PRESET);
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
