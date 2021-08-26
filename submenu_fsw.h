#ifndef SUBMENU_FSW_H
#define SUBMENU_FSW_H

uint8_t submenu_fsw_color(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_COLORS, sizeof(Color), "COLORS", EEP_NUM_COLORS, true, 0);

  if ( result ) {
    fsw_p[sel_fsw_id].colors[sel_fsw_state_id] = result-1;
    return true;
  }

  return false;
}

uint8_t submenu_fsw_params(Menu *m) {
  // menu, footswitch id (global), true, sel_param_id
  return submenu_helper_pedal_param_loop(m, sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, true, sel_param_id);
}

uint8_t submenu_fsw_mode_off(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_OFF;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_toggle(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_TOGGLE;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_cycle(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_CYCLE;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_oneshot(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_ONESHOT;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_submenu(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_SUBMENU;
  uint8_t result = submenu_helper_value(m, 0, 0, 3, "SUBMENU");

  if ( result ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, 0);

    pedal_param_p->velocity = result-1;

    DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, 0, pedal_param_p);

    CLRPTR(pedal_param_p);
    m->jump_to(255);
    return true;
  }

  return false;
}

uint8_t submenu_fsw_mode_preset(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_PRESET;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_lp_mode_off(Menu *m) {
  fsw_p[sel_fsw_id].lp_mode = FSW_MODE_OFF;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_lp_mode_oneshot(Menu *m) {
  fsw_p[sel_fsw_id].lp_mode = FSW_MODE_ONESHOT;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_lp_mode_submenu(Menu *m) {
  fsw_p[sel_fsw_id].lp_mode = FSW_MODE_SUBMENU;
  uint8_t result = submenu_helper_value(m, 0, 0, 3, "SUBMENU");

  if ( result ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, 3);

    pedal_param_p->velocity = result-1;

    DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, 3, pedal_param_p);

    CLRPTR(pedal_param_p);
    m->jump_to(255);
    return true;
  }

  return false;
}

uint8_t submenu_fsw_lp_mode_preset(Menu *m) {
  fsw_p[sel_fsw_id].lp_mode = FSW_MODE_PRESET;
  m->jump_to(255);
  return true;
}


uint8_t submenu_fsw_param_pedal(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PEDALS, sizeof(Pedal), "PEDALS", EEP_NUM_PEDALS, false, sel_pedal_id);

  if ( result ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id);

    pedal_param_p->pedal = result-1;

    DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id, pedal_param_p);

    CLRPTR(pedal_param_p);
    return true;
  }

  return false;
}

uint8_t submenu_fsw_param_pedal_param(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PARAMS, sizeof(Param), "PARAMS", EEP_NUM_PARAMS, false, sel_param_id);

  if ( result ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id);

    pedal_param_p->param = result-1;

    DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id, pedal_param_p);

    CLRPTR(pedal_param_p);
    return true;
  }

  return false;
}

uint8_t submenu_fsw_param_velocity(Menu *m) {
  if ( !m->initialized ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::fsw_param_at(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id);
  }

  uint16_t result = submenu_helper_value(m, pedal_param_p->velocity, 0, 127, "VELOCITY"); 

  if ( result ) {
    pedal_param_p->velocity = result-1;

    DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id, pedal_param_p);

    CLRPTR(pedal_param_p);
    return true;
  }

  return false;
}

uint8_t submenu_fsw_param_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      if ( pedal_param_p == nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + sel_param_id, pedal_param_p);
      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

uint8_t submenu_fsw_lp_params(Menu *m) {
  uint8_t old_sel_fsw_state_id = sel_fsw_state_id;
  uint8_t result               = 0;

  sel_fsw_state_id = 3;  // 4th position is where LongPress params are stored

  result = submenu_helper_pedal_param_loop(m, sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, true, sel_param_id);

  sel_fsw_state_id = old_sel_fsw_state_id;

  return result;
}

uint8_t submenu_fsw_lp_param_pedal(Menu *m) {
  uint8_t old_sel_fsw_state_id = sel_fsw_state_id;
  uint8_t result               = 0;

  sel_fsw_state_id = 3;  // 4th position is where LongPress params are stored

  result = submenu_fsw_param_pedal(m);

  sel_fsw_state_id = old_sel_fsw_state_id;

  return result;
}

uint8_t submenu_fsw_lp_param_pedal_param(Menu *m) {
  uint8_t old_sel_fsw_state_id = sel_fsw_state_id;
  uint8_t result               = 0;

  sel_fsw_state_id = 3;  // 4th position is where LongPress params are stored

  result = submenu_fsw_param_pedal_param(m);

  sel_fsw_state_id = old_sel_fsw_state_id;

  return result;
}

uint8_t submenu_fsw_lp_param_velocity(Menu *m) {
  uint8_t old_sel_fsw_state_id = sel_fsw_state_id;
  uint8_t result               = 0;

  sel_fsw_state_id = 3;  // 4th position is where LongPress params are stored

  result = submenu_fsw_param_velocity(m);

  sel_fsw_state_id = old_sel_fsw_state_id;

  return result;
}

uint8_t submenu_fsw_lp_param_reset(Menu *m) {
  uint8_t old_sel_fsw_state_id = sel_fsw_state_id;
  uint8_t result               = 0;

  sel_fsw_state_id = 3;  // 4th position is where LongPress params are stored

  result = submenu_fsw_param_reset(m);

  sel_fsw_state_id = old_sel_fsw_state_id;

  return result;
}


uint8_t submenu_fsw_lp_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      if ( pedal_param_p == nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      fsw_p[sel_fsw_id].lp_mode = FSW_MODE_OFF;

      for (int i=0; i<NUM_PRESET_PARAMS; i++) {
        DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, /*sel_fsw_state_id*/3*NUM_PRESET_PARAMS + /*sel_param_id*/i, pedal_param_p);
      }
      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

uint8_t submenu_fsw_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      if ( pedal_param_p == nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      fsw_p[sel_fsw_id].mode      = FSW_MODE_OFF;
      fsw_p[sel_fsw_id].mode      = FSW_MODE_TOGGLE;
      fsw_p[sel_fsw_id].colors[0] = 0;
      fsw_p[sel_fsw_id].colors[1] = 1;
      fsw_p[sel_fsw_id].colors[2] = 2;

      for (int i=0; i<NUM_PRESET_PARAMS; i++) {
        DB::fsw_param_save(sel_preset_id*NUM_FSW*NUM_SUB_MENUS + sel_fsw_id, sel_fsw_state_id*NUM_PRESET_PARAMS + i, pedal_param_p);
      }
      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

#endif
