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
        m->jump_to(63);
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

#endif
