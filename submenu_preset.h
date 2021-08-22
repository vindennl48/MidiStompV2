#ifndef SUBMENU_PRESET_H
#define SUBMENU_PRESET_H

uint8_t submenu_preset_save(Menu *m) {
  if ( m->not_initialized() ) {
    confirm_p = new Confirm;
  }
  else {
    uint8_t result = confirm_p->loop();

    if ( result != false ) {
      if ( result == LTRUE ) {
        //  SAVE
        DB::preset_save(preset_id, preset_p);

        for (int i=0; i<NUM_FSW_PER_PRESET; i++) {
          DB::fsw_save(preset_id, i, &fsw_p[i]);
        }

        /*
         * Eventually, would like to store currently running
         * preset on a reserved section of EEPROM so we can 
         * also store temporary fsw pedal params and preset
         * pedal params.  Currently, we don't have enough
         * room in ram to do this. */
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

uint8_t submenu_preset_name(Menu *m) {
  if ( m->not_initialized() ) {
    text_edit_p = new TextEdit(preset_p->name);
  }
  else {
    if ( text_edit_p->loop() ) {
      CLRPTR(text_edit_p);
      return m->back();
    }
  }
  return false;
}

uint8_t submenu_preset_params(Menu *m) {
  if ( m->not_initialized() ) {
    pedal_param_loop_p = new PedalParamLoop(preset_id, false, preset_selected_param);
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
        DB::preset_param_save(preset_id, preset_selected_param, pedal_param_p);
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
    DB::preset_param_save(preset_id, preset_selected_param, pedal_param_p);
    return true;
  }
  return false;
}

uint8_t submenu_preset_param_reset(Menu *m) {
  if ( m->not_initialized() ) {
    confirm_p = new Confirm;
  }
  else {
    uint8_t result = confirm_p->loop();

    if ( result != false ) {
      if ( result == LTRUE ) {
        //  SAVE
        pedal_param_p = new PedalParam;
        DB::preset_param_save(preset_id, preset_selected_param, pedal_param_p);
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

        DB::preset_save(preset_id, preset_p);

        for (int i=0; i<NUM_PRESET_PARAMS; i++) DB::preset_param_save(preset_id, i, pedal_param_p);

        for (int i=0; i<NUM_FSW_PER_PRESET; i++) {
          fsw_p[i] = Footswitch();
          DB::fsw_save(preset_id, i, &fsw_p[i]);

          for (int j=0; j<NUM_PARAMS_PER_FSW; j++) {
            DB::fsw_param_save(i + preset_id*NUM_FSW*NUM_SUB_MENUS, j, pedal_param_p);
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
