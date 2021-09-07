uint8_t f_colors() {
  uint16_t active_parent_addr = GET_ACTIVE_PARENT_NOT_OPTION;

  leds_set(
    Color::get_red(active_parent_addr),
    Color::get_green(active_parent_addr),
    Color::get_blue(active_parent_addr)
  );

  return true;
}


uint8_t f_preset_params_setup() {
  // preset is always parent 0
  uint8_t preset_id = GET_ID_FROM_ADDR(M_PRESETS, parents[0], sizeof(Preset));
  alt_start_addr    = GET_CHILD(M_PRESET_PARAMS, preset_id, 0, sizeof(Parameter), NUM_PRESET_PARAMS_PER_PRESET);
  DEBUG("----> preset_params_setup() preset_id:      ", preset_id);
  DEBUG("----> preset_params_setup() alt_start_addr: ", alt_start_addr);
  return true;
}
uint8_t f_preset_params_run() {
  uint16_t active_parent_addr  = GET_ACTIVE_PARENT_NOT_OPTION;
  uint8_t  pedal_id            = Parameter::get_pedal(active_parent_addr);
  uint8_t  feature_relative_id = Parameter::get_feature(active_parent_addr);

  DEBUG("----> preset_params_run() pedal_id:            ", pedal_id);
  DEBUG("----> preset_params_run() feature_relative_id: ", feature_relative_id);

  if ( pedal_id == NUM_PEDALS )
    memcpy(text[TXT_BUF_2], "EMPTY       ", TEXT_SZ);
  else {
    Pedal::get_name(GET_PARENT(M_PEDALS, pedal_id, sizeof(Pedal)), TXT_BUF_2);
    Feature::get_name(GET_CHILD(M_FEATURES, pedal_id, feature_relative_id, sizeof(Feature), NUM_FEATURES_PER_PEDAL), TXT_BUF_1);

    text[TXT_BUF_2][5] = ' ';
    for (uint8_t i=6; i<TEXT_SZ; i++) {
      text[TXT_BUF_2][i] = text[TXT_BUF_1][i-6];
    }
  }
  return true;
}


uint8_t f_global() {
  leds_set(0,0,0);
  return true;
}


uint8_t f_preset_param_pedal_setup() {
  uint16_t preset_param_addr = GET_ACTIVE_PARENT_NOT_OPTION;
  uint8_t  pedal_id          = Parameter::get_pedal(preset_param_addr);

  // Failsafe in case pedals is empty
  if ( pedal_id == NUM_PEDALS ) {
    pedal_id = 0;
    Parameter::set_pedal(preset_param_addr, pedal_id);
  }

  // Check parents list if last addr is not in the menu options list
  if ( !IS_IN_PARTITION_PEDALS(GET_ACTIVE_PARENT) ) {
    DEBUG("Setting new parent!: ", GET_UNUSED_PARENT_ID);
    // If it's not, then set new parent addr as the start_addr of menu struct
    SET_NEW_PARENT( GET_PARENT(M_PEDALS, pedal_id, sizeof(Pedal)) );
  }
  return true;
}
uint8_t f_preset_param_pedal_save() {
  uint8_t pedal_id = GET_ID_FROM_ADDR(M_PEDALS, GET_ACTIVE_PARENT, sizeof(Pedal));
  // In this menu, the parameter address is always active_parent - 2
  Parameter::set_pedal(parents[GET_ACTIVE_PARENT_ID-2], pedal_id);

  // Because we are going back to the same screen, MenuSystem won't delete it
  // so we need to make sure active parent gets deleted manually.
  deactivate_active_parent();

  return true;
}


uint8_t f_preset_param_feature_setup() {
  uint16_t preset_param_addr   = GET_ACTIVE_PARENT_NOT_OPTION;
  uint8_t  pedal_id            = Parameter::get_pedal(preset_param_addr);
  // relative ID meaning the nth feature of the pedal_id, NOT the nth feature in the eeprom
  uint8_t  feature_relative_id = Parameter::get_feature(preset_param_addr);

  // Failsafe in case pedals is empty
  if ( pedal_id == NUM_PEDALS ) {
    pedal_id = 0;
    Parameter::set_pedal(preset_param_addr, pedal_id);
  }


  // Check parents list if last addr is not in the menu options list
  if ( !IS_IN_PARTITION_FEATURES(GET_ACTIVE_PARENT) ) {
    DEBUG("Setting new parent!: ", GET_UNUSED_PARENT_ID);
    // If it's not, then set new parent addr as the start_addr of menu struct
    SET_NEW_PARENT( GET_CHILD(M_FEATURES, pedal_id, feature_relative_id, sizeof(Feature), NUM_FEATURES_PER_PEDAL) );
  }
  return true;
}
uint8_t f_preset_param_feature_save() {
  // relative ID meaning the nth feature of the pedal_id, NOT the nth feature in the eeprom
  uint8_t feature_relative_id = GET_ID_FROM_ADDR(M_FEATURES, GET_ACTIVE_PARENT, sizeof(Feature)) % NUM_FEATURES_PER_PEDAL;
  // In this menu, the parameter address is always active_parent - 2
  Parameter::set_feature(parents[GET_ACTIVE_PARENT_ID-2], feature_relative_id);

  // Because we are going back to the same screen, MenuSystem won't delete it
  // so we need to make sure active parent gets deleted manually.
  deactivate_active_parent();

  return true;
}


#define F_NONE                       0
#define F_COLORS                     1
#define F_PRESET_PARAMS_RUN          2
#define F_PRESET_PARAMS_SETUP        3
#define F_PRESET_PARAM_PEDAL_SETUP   4
#define F_PRESET_PARAM_PEDAL_SAVE    5
#define F_PRESET_PARAM_FEATURE_SETUP 6
#define F_PRESET_PARAM_FEATURE_SAVE  7
#define F_GLOBAL                     8

typedef uint8_t (*Callback)();

Callback get_callback(uint8_t id) {
  switch(id) {
    case F_COLORS:                     return &f_colors;
    case F_PRESET_PARAMS_RUN:          return &f_preset_params_run;
    case F_PRESET_PARAMS_SETUP:        return &f_preset_params_setup;
    case F_PRESET_PARAM_PEDAL_SETUP:   return &f_preset_param_pedal_setup;
    case F_PRESET_PARAM_PEDAL_SAVE:    return &f_preset_param_pedal_save;
    case F_PRESET_PARAM_FEATURE_SETUP: return &f_preset_param_feature_setup;
    case F_PRESET_PARAM_FEATURE_SAVE:  return &f_preset_param_feature_save;
    case F_GLOBAL:                     return &f_global;
  };

  return nullptr;
}
