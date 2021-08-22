#ifndef SUBMENU_COLOR_H
#define SUBMENU_COLOR_H

uint8_t submenu_colors(Menu *m) {
  if ( m->not_initialized() ) {
    list_loop_p = new ListLoop(EEP_START_COLORS, sizeof(Color), "COLORS", EEP_NUM_COLORS, true);
  }
  else {
    if ( list_loop_p->loop() ) {
      if ( list_loop_p->get_result() != (EEP_NUM_COLORS+1) ) {
        //continue
        sel_color_id = list_loop_p->get_result();
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

uint8_t submenu_color_name(Menu *m) {
  if ( m->not_initialized() ) {
    if ( color_p == nullptr ) color_p = new Color;
    *color_p = DB::color_at(sel_color_id);

    text_edit_p = new TextEdit(color_p->name);
  }
  else {
    if ( text_edit_p->loop() ) {
      DB::color_save(sel_color_id, color_p);
      CLRPTR(text_edit_p);
      CLRPTR(color_p)
      return m->back();
    }
  }

  return false;
}

uint8_t submenu_color_edit(Menu *m) {
  if ( m->not_initialized() ) {
    if ( color_p == nullptr ) color_p = new Color;
    *color_p = DB::color_at(sel_color_id);

    color_edit_p = new ColorEdit();
  }
  else {
    if ( color_edit_p->loop() ) {
      CLRPTR(color_edit_p);
      CLRPTR(color_p)
      return m->back();
    }
  }

  return false;
}

#endif
