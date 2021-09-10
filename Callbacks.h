/* :: PEDAL :: */
uint8_t get_pedal_id_from_parents() {
  uint16_t pedal_addr = 0;
  for (int i=NUM_PARENTS_MAX-1; i>=0; i--) {
    if ( IS_IN_PARTITION_PEDALS(parents[i]) )
      pedal_addr = parents[i];
  }
  return GET_ID_FROM_ADDR(M_PEDALS, pedal_addr, sizeof(Pedal));
}
/* :: END PEDAL :: */


/* :: COLOR :: */
uint8_t f_colors() {
  uint16_t active_parent_addr = GET_ACTIVE_PARENT_NOT_OPTION;

  leds_set(
    Color::get_red(active_parent_addr),
    Color::get_green(active_parent_addr),
    Color::get_blue(active_parent_addr)
  );

  return true;
}
/* :: END COLOR :: */


/* :: FEATURE :: */
uint8_t f_features_setup() {
  uint8_t pedal_id = get_pedal_id_from_parents();
  alt_start_addr   = GET_CHILD(M_FEATURES, pedal_id, 0, sizeof(Feature), NUM_FEATURES_PER_PEDAL);
  return true;
}
/* :: END FEATURE :: */


/* :: GLOBAL :: */
uint8_t f_global() {
  leds_set(0,0,0);
  return true;
}
/* :: END GLOBAL :: */


/* :: PRESET :: */
uint8_t f_preset_save() {
  // Because we are going back to the same screen, MenuSystem won't delete it
  // so we need to make sure active parent gets deleted manually.
  deactivate_active_parent();

  return true;
}
uint8_t f_preset_params_setup() {
  // preset is always parent 0
  uint8_t preset_id = GET_ID_FROM_ADDR(M_PRESETS, parents[0], sizeof(Preset));
  alt_start_addr    = GET_CHILD(M_PRESET_PARAMS, preset_id, 0, sizeof(Parameter), NUM_PRESET_PARAMS_PER_PRESET);
  return true;
}
uint8_t f_preset_params_run() {
  uint16_t active_parent_addr  = GET_ACTIVE_PARENT_NOT_OPTION;
  uint8_t  pedal_id            = Parameter::get_pedal(active_parent_addr);
  uint8_t  feature_relative_id = Parameter::get_feature(active_parent_addr);

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
    // If it's not, then set new parent addr as the start_addr of menu struct
    SET_NEW_PARENT( GET_PARENT(M_PEDALS, pedal_id, sizeof(Pedal)) );
  }
  return true;
}
uint8_t f_preset_param_pedal_save() {
  uint8_t pedal_id = get_pedal_id_from_parents();
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
/* :: END PRESET :: */


/* :: FSW :: */
uint8_t f_fsw_setup() {
  String title =  "FSW" + String((fsw_settings.id%NUM_FSW_PER_SUBMENU)+1) + " S" + String(fsw_settings.state+1) + " M" + String(submenu_id+1) ;
  for (uint8_t i=0; i<TEXT_SZ; i++)
    text[TXT_BUF_1][i] = title[i];
  leds_set(0,0,0);
  leds[fsw_settings.id % NUM_FSW_PER_SUBMENU].set(GET_RGB(fsw[fsw_settings.id].color_id[fsw_settings.state]));
  return true;
}
uint8_t f_fsw_color_setup() {
  // Check parents list if last addr is not in the menu options list
  if ( !IS_IN_PARTITION_COLORS(GET_ACTIVE_PARENT) ) {
    // If it's not, then set new parent addr as the start_addr of menu struct
    SET_NEW_PARENT( GET_PARENT(M_COLORS, fsw[fsw_settings.id].color_id[fsw_settings.state], sizeof(Color)) );
  }
  return true;
}
uint8_t f_fsw_color_save() {
  fsw[fsw_settings.id].color_id[fsw_settings.state] = GET_ID_FROM_ADDR(M_COLORS, GET_ACTIVE_PARENT, sizeof(Color));

  // Because we are going back to the same screen, MenuSystem won't delete it
  // so we need to make sure active parent gets deleted manually.
  deactivate_active_parent();

  return true;
}
uint8_t f_fsw_params_setup() {
  DEBUG("M_FSW_PARAMS:       ", M_FSW_PARAMS);
  DEBUG("fsw_settings.id:    ", fsw_settings.id);
  DEBUG("preset_id:          ", preset_id);
  DEBUG("fsw_settings.state: ", fsw_settings.state);
  alt_start_addr = GET_CHILD(M_FSW_PARAMS, (fsw_settings.id+(preset_id*NUM_FSW_PER_PRESET)), (fsw_settings.state*NUM_FSW_PARAMS_PER_STATE), sizeof(Parameter), NUM_FSW_PARAMS_PER_STATE);
  DEBUG("----", 0);
  DEBUG("pedal_id: ", Parameter::get_pedal(alt_start_addr));
  DEBUG("feature_id: ", Parameter::get_feature(alt_start_addr));
  return true;
}
uint8_t f_fsw_params_run() {
  return f_preset_params_run();
}
uint8_t f_fsw_param_pedal_setup() {
  return f_preset_param_pedal_setup();
}
uint8_t f_fsw_param_pedal_save() {
  return f_preset_param_pedal_save();
}
uint8_t f_fsw_param_feature_setup() {
  return f_preset_param_feature_setup();
}
uint8_t f_fsw_param_feature_save() {
  return f_preset_param_feature_save();
}
/* :: END FSW :: */



#define F_NONE                       0
#define F_COLORS                     1
#define F_PRESET_SAVE                2
#define F_PRESET_PARAMS_RUN          3
#define F_PRESET_PARAMS_SETUP        4
#define F_PRESET_PARAM_PEDAL_SETUP   5
#define F_PRESET_PARAM_PEDAL_SAVE    6
#define F_PRESET_PARAM_FEATURE_SETUP 7
#define F_PRESET_PARAM_FEATURE_SAVE  8
#define F_FEATURES_SETUP             9
#define F_GLOBAL                     10
#define F_FSW_SETUP                  11
#define F_FSW_COLOR_SETUP            12
#define F_FSW_COLOR_SAVE             13
#define F_FSW_PARAMS_RUN             14
#define F_FSW_PARAMS_SETUP           15
#define F_FSW_PARAM_PEDAL_SETUP      16
#define F_FSW_PARAM_PEDAL_SAVE       17
#define F_FSW_PARAM_FEATURE_SETUP    18
#define F_FSW_PARAM_FEATURE_SAVE     19

typedef uint8_t (*Callback)();

Callback get_callback(uint8_t id) {
  switch(id) {
    case F_COLORS:                     return &f_colors;
    case F_PRESET_SAVE:                return &f_preset_save;
    case F_PRESET_PARAMS_RUN:          return &f_preset_params_run;
    case F_PRESET_PARAMS_SETUP:        return &f_preset_params_setup;
    case F_PRESET_PARAM_PEDAL_SETUP:   return &f_preset_param_pedal_setup;
    case F_PRESET_PARAM_PEDAL_SAVE:    return &f_preset_param_pedal_save;
    case F_PRESET_PARAM_FEATURE_SETUP: return &f_preset_param_feature_setup;
    case F_PRESET_PARAM_FEATURE_SAVE:  return &f_preset_param_feature_save;
    case F_FEATURES_SETUP:             return &f_features_setup;
    case F_GLOBAL:                     return &f_global;
    case F_FSW_SETUP:                  return &f_fsw_setup;
    case F_FSW_COLOR_SETUP:            return &f_fsw_color_setup;
    case F_FSW_COLOR_SAVE:             return &f_fsw_color_save;
    case F_FSW_PARAMS_RUN:             return &f_fsw_params_run;
    case F_FSW_PARAMS_SETUP:           return &f_fsw_params_setup;
    case F_FSW_PARAM_PEDAL_SETUP:      return &f_fsw_param_pedal_setup;
    case F_FSW_PARAM_PEDAL_SAVE:       return &f_fsw_param_pedal_save;
    case F_FSW_PARAM_FEATURE_SETUP:    return &f_fsw_param_feature_setup;
    case F_FSW_PARAM_FEATURE_SAVE:     return &f_fsw_param_feature_save;
  };

  return nullptr;
}
