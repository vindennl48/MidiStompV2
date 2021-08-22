#ifndef SUBMENU_PRESET_H
#define SUBMENU_PRESET_H

uint8_t submenu_preset_save(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE

      // Eventually, would like to store currently running
      // preset on a reserved section of EEPROM so we can 
      // also store temporary fsw pedal params and preset
      // pedal params.  Currently, we don't have enough
      // room in ram to do this.
      DB::preset_save(sel_preset_id, preset_p);

      for (int i=0; i<NUM_FSW_PER_PRESET; i++) {
        DB::fsw_save(sel_preset_id, i, &fsw_p[i]);
      }
    }

    return true;
  }

  return false;
}

uint8_t submenu_preset_name(Menu *m) {
  return submenu_helper_text(m, preset_p->name);
}

uint8_t submenu_preset_params(Menu *m) {
  return submenu_helper_pedal_param_loop(m, sel_preset_id, false, sel_param_id);
}

uint8_t submenu_preset_param_pedal(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PEDALS, sizeof(Pedal), "PEDALS", EEP_NUM_PEDALS, false, sel_pedal_id);

  if ( result ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::preset_param_at(sel_preset_id, sel_param_id);

    pedal_param_p->pedal = result-1;

    DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);

    CLRPTR(pedal_param_p);
    return true;
  }

  return false;
}

uint8_t submenu_preset_param_velocity(Menu *m) {
  if ( !m->initialized ) {
    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    *pedal_param_p = DB::preset_param_at(sel_preset_id, sel_param_id);
  }

  uint16_t result = submenu_helper_value(m, pedal_param_p->velocity, 0, 127, "VELOCITY"); 

  if ( result ) {
    pedal_param_p->velocity = result-1;

    DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);

    CLRPTR(pedal_param_p);
    return true;
  }

  return false;
}

uint8_t submenu_preset_param_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      if ( pedal_param_p == nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);
      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

uint8_t submenu_preset_copy(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PRESETS, sizeof(Preset), "COPY OVER", EEP_NUM_PRESETS, false, sel_preset_id);

  if ( result ) {
    if ( m->event == 255 ) { return true; }  // Cancel

    DB::preset_save(result-1, preset_p);

    if ( pedal_param_p == nullptr ) pedal_param_p = new PedalParam;
    for (int i=0; i<NUM_PRESET_PARAMS; i++) {
      *pedal_param_p = DB::preset_param_at(sel_preset_id, i);
      DB::preset_param_save(result-1, i, pedal_param_p);
    }

    for (int i=0; i<NUM_FSW_PER_PRESET; i++) {
      DB::fsw_save(result-1, i, &fsw_p[i]);

      for (int j=0; j<NUM_PARAMS_PER_FSW; j++) {
        *pedal_param_p = DB::fsw_param_at(i + sel_preset_id*NUM_FSW*NUM_SUB_MENUS, j);
        DB::fsw_param_save(i + (result-1)*NUM_FSW*NUM_SUB_MENUS, j, pedal_param_p);
      }
    }

    HW::screen.clear();
    HW::screen.print(0,0, "COPY COMPLETE!");
    HW::screen.print(0,1, String(sel_preset_id)+String(" TO ")+String(result-1));
    delay(5000);

    CLRPTR(pedal_param_p);
  }

  return false;
}

uint8_t submenu_preset_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      *preset_p      = Preset();
      if ( pedal_param_p == nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      DB::preset_save(sel_preset_id, preset_p);

      for (int i=0; i<NUM_PRESET_PARAMS; i++) DB::preset_param_save(sel_preset_id, i, pedal_param_p);

      for (int i=0; i<NUM_FSW_PER_PRESET; i++) {
        fsw_p[i] = Footswitch();
        DB::fsw_save(sel_preset_id, i, &fsw_p[i]);

        for (int j=0; j<NUM_PARAMS_PER_FSW; j++) {
          DB::fsw_param_save(i + sel_preset_id*NUM_FSW*NUM_SUB_MENUS, j, pedal_param_p);
        }
      }

      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

#endif
