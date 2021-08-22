#ifndef SUBMENU_PEDAL_H
#define SUBMENU_PEDAL_H

uint8_t submenu_pedals(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PEDALS, sizeof(Pedal), "PEDALS", EEP_NUM_PEDALS, false, sel_pedal_id);

  if ( result ) {
    sel_pedal_id = result-1;
    return true;
  }

  return false;
}

uint8_t submenu_pedal_name(Menu *m) {
  if ( !m->initialized ) {
    if ( pedal_p == nullptr ) pedal_p = new Pedal;
    *pedal_p = DB::pedal_at(sel_pedal_id);
  }

  uint8_t result = submenu_helper_text(m, pedal_p->name);

  if ( result ) {
    DB::pedal_save(sel_pedal_id, pedal_p);
    CLRPTR(pedal_p)
    return true;
  }

  return false;
}

uint8_t submenu_pedal_params(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_PARAMS, sizeof(Param), "PARAMS", NUM_PEDAL_PARAMS, false, sel_param_id);

  if ( result ) {
    sel_param_id = result-1;
    return true;
  }

  return false;
}

uint8_t submenu_pedal_channel(Menu *m) {
  if ( !m->initialized ) {
    if ( pedal_p == nullptr ) pedal_p = new Pedal;
    *pedal_p = DB::pedal_at(sel_pedal_id);
  }

  uint16_t result = submenu_helper_value(m, pedal_p->channel, 0, 15, "CHANNEL"); 

  if ( result ) {
    pedal_p->channel = result-1;

    DB::pedal_save(sel_pedal_id, pedal_p);

    CLRPTR(pedal_p);
    return true;
  }

  return false;
}

uint8_t submenu_pedal_param_name(Menu *m) {
  if ( !m->initialized ) {
    if ( param_p == nullptr ) param_p = new Param;
    *param_p = DB::param_at(sel_pedal_id, sel_param_id);
  }

  uint8_t result = submenu_helper_text(m, param_p->name);

  if ( result ) {
    DB::param_save(sel_pedal_id, sel_param_id, param_p);
    CLRPTR(param_p)
    return true;
  }

  return false;
}

uint8_t submenu_pedal_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      if ( pedal_p == nullptr )  pedal_p = new Pedal;
      else                      *pedal_p = Pedal();

      DB::pedal_save(sel_pedal_id, pedal_p);

      if ( param_p == nullptr )  param_p = new Param;
      else                      *param_p = Param();
      for (int i=0; i<NUM_PEDAL_PARAMS; i++) DB::param_save(sel_pedal_id, i, param_p);

      CLRPTR(pedal_p);
      CLRPTR(param_p);
    }

    return true;
  }

  return false;
}


#endif
