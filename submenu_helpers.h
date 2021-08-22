#ifndef SUBMENU_HELPERS_H
#define SUBMENU_HELPERS_H

uint8_t submenu_helper_confirm(Menu *m) {
  if ( m->not_initialized() ) {
    if ( confirm_p != nullptr )
      confirm_p = new Confirm;
    else
      confirm_p = Confirm();
  }
  else {
    uint8_t result = confirm_p->loop();
    if ( result ) {
      m->back();
      CLRPTR(confirm_p);
      return result;
    }
  }

  return false;
}

uint16_t submenu_helper_value(Menu *m, uint16_t value, uint16_t min, uint16_t max, String title) {
  if ( m->not_initialized() ) {
    if ( value_edit_p != nullptr )
      value_edit_p = new ValueEdit(value+1, min+1, max+1, title);
    else
      *value_edit_p = ValueEdit(value+1, min+1, max+1, title);
  }
  else {
    if ( value_edit_p->loop() ) {
      value = value_edit_p->get_result()-1;
      CLRPTR(value_edit_p);
      m->back();
      return value;
    }
  }

  return false;
}

#endif
