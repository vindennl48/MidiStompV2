#ifndef SUBMENU_COLOR_H
#define SUBMENU_COLOR_H

// Select color to edit
uint8_t submenu_colors(Menu *m) {
  uint16_t result = submenu_helper_list_loop(m, EEP_START_COLORS, sizeof(Color), "COLORS", EEP_NUM_COLORS, true, sel_color_id);

  if ( result ) {
    sel_color_id = result-1;
    return true;
  }

  return false;
}

// Change color name
uint8_t submenu_color_name(Menu *m) {
  if ( !m->initialized ) {
    if ( color_p == nullptr ) color_p = new Color;
    *color_p = DB::color_at(sel_color_id);
  }

  uint8_t result = submenu_helper_text(m, color_p->name);

  if ( result ) {
    DB::color_save(sel_color_id, color_p);
    CLRPTR(color_p)
    return true;
  }

  return false;
}

// Change color value
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

// Reset color
uint8_t submenu_color_reset(Menu *m) {
  uint8_t result = submenu_helper_confirm(m);

  if ( result ) {
    if ( result == LTRUE ) {
      if ( color_p == nullptr )  color_p = new Color;
      else                      *color_p = Color();

      DB::color_save(sel_color_id, color_p);

      CLRPTR(color_p);
    }

    return true;
  }

  return false;
}
#endif
