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
  if ( m->not_initialized() ) {
    pedal_param_loop_p = new PedalParamLoop(sel_preset_id, false, sel_param_id);
  }
  else {
    if ( pedal_param_loop_p->loop() ) {
      if ( pedal_param_loop_p->get_result() != (NUM_PARAMS_PER_FSW+1) ) {
        //continue
        m->back();
      }
      else {
        //go back
        m->jump_to(255);
      }
      CLRPTR(pedal_param_loop_p);
      return true;
    }
  }

  return false;
}

uint8_t submenu_preset_param_pedal(Menu *m) {
  if ( m->not_initialized() ) {
    list_loop_p = new ListLoop(EEP_START_PEDALS, sizeof(Pedal), "PEDALS", EEP_NUM_PEDALS);
  }
  else {
    if ( list_loop_p->loop() ) {
      if ( list_loop_p->get_result() != EEP_NUM_PEDALS ) {
        //continue
        pedal_param_p->pedal = list_loop_p->get_result();
        DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);
        m->back();
      }
      else {
        //go back
        m->jump_to(255);
      }
      CLRPTR(list_loop_p);
      return true;
    }
  }

  return false;
}

uint8_t submenu_preset_param_velocity(Menu *m) {
  uint16_t result = submenu_helper_value(m, pedal_param_p->velocity, 0, 127, "VELOCITY"); 
  if ( result ) {
    pedal_param_p->velocity = result-1;
    DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);
    return true;
  }
  return false;
}

uint8_t submenu_preset_param_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      //  SAVE
      if ( pedal_param_p != nullptr )  pedal_param_p = new PedalParam;
      else                            *pedal_param_p = PedalParam();

      DB::preset_param_save(sel_preset_id, sel_param_id, pedal_param_p);
      CLRPTR(pedal_param_p);
    }

    return true;
  }

  return false;
}

uint8_t submenu_preset_copy  (Menu *m) {
  if ( m->not_initialized() ) {
  }
  else {
  }

  return false;
}

uint8_t submenu_preset_reset (Menu *m) {
  if ( m->not_initialized() ) {
    confirm_p = new Confirm;
  }
  else {
    uint8_t result = confirm_p->loop();

    if ( result != false ) {
      if ( result == LTRUE ) {
        //  SAVE
        *preset_p      = Preset();
        pedal_param_p  = new PedalParam;

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
      else if ( result == LFALSE ) {
        // CANCEL
      }

      CLRPTR(confirm_p);
      return m->back();
    }
  }

  return false;
}

#endif
