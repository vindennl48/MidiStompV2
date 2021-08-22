#ifndef SUBMENU_PEDAL_H
#define SUBMENU_PEDAL_H

uint8_t submenu_pedals(Menu *m) {
  if ( m->not_initialized() ) {
    list_loop_p = new ListLoop(EEP_START_PEDALS, sizeof(Pedal), "PEDALS", EEP_NUM_PEDALS);
  }
  else {
    if ( list_loop_p->loop() ) {
      if ( list_loop_p->get_result() != (EEP_NUM_PEDALS+1) ) {
        //continue
        pedal_selected = list_loop_p->get_result();
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

uint8_t submenu_pedal_name(Menu *m) {
  if ( m->not_initialized() ) {
    if ( pedal_p == nullptr ) pedal_p = new Pedal;
    *pedal_p = DB::pedal_at(pedal_selected);

    text_edit_p = new TextEdit(pedal_p->name);
  }
  else {
    if ( text_edit_p->loop() ) {
      DB::pedal_save(pedal_selected, pedal_p);
      CLRPTR(text_edit_p);
      CLRPTR(pedal_p)
      return m->back();
    }
  }

  return false;
}

uint8_t submenu_pedal_params(Menu *m) {
  if ( m->not_initialized() ) {
    list_loop_p = new ListLoop(EEP_START_PARAMS, sizeof(Param), "PARAMS", NUM_PEDAL_PARAMS);
  }
  else {
    if ( list_loop_p->loop() ) {
      if ( list_loop_p->get_result() != (NUM_PEDAL_PARAMS+1) ) {
        //continue
        pedal_param_selected = list_loop_p->get_result();
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

uint8_t submenu_pedal_channel(Menu *m) {
  if ( m->not_initialized() ) {
    if ( pedal_p == nullptr ) pedal_p = new Pedal;
    *pedal_p = DB::pedal_at(pedal_selected);

    value_edit_p = new ValueEdit(pedal_p->channel+1, 1, 16, "CHANNEL");
  }
  else {
    if ( value_edit_p->loop() ) {
      pedal_p->channel = value_edit_p->get_result()-1;
      DB::pedal_save(pedal_selected, pedal_p);
      CLRPTR(value_edit_p);
      CLRPTR(pedal_p)
      return m->back();
    }
  }

  return false;
}

uint8_t submenu_pedal_param_name(Menu *m) {
  if ( m->not_initialized() ) {
    if ( param_p == nullptr ) param_p = new Param;
    *param_p = DB::param_at(pedal_selected, pedal_param_selected);

    text_edit_p = new TextEdit(param_p->name);
  }
  else {
    if ( text_edit_p->loop() ) {
      DB::param_save(pedal_selected, pedal_param_selected, param_p);
      CLRPTR(text_edit_p);
      CLRPTR(param_p)
      return m->back();
    }
  }

  return false;
}

#endif
