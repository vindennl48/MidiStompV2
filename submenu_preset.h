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
        /*  SAVE
         *  - Preset
         *  - ALL FSW
         *  - Pedal Params for FSW and Preset
         *  */
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
    pedal_param_loop_p = new PedalParamLoop(preset_id, false);
  }
  else {
    if ( pedal_param_loop_p->loop() ) {
      if ( pedal_param_loop_p->get_result() != (NUM_PARAMS_PER_FSW+1) ) {
        //continue
        m->back();
      }
      else {
        //go back
        m->jump_to(63);
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
        m->jump_to(63);
      }
      CLRPTR(list_loop_p);
      return true;
    }
  }

  return false;
}

uint8_t submenu_preset_copy  (Menu *m) { }
uint8_t submenu_preset_reset (Menu *m) { }

#endif
