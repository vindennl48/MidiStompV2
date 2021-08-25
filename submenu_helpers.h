#ifndef SUBMENU_HELPERS_H
#define SUBMENU_HELPERS_H

uint16_t submenu_helper_list_loop(Menu *m, uint16_t start, uint8_t size, String title, uint16_t max, uint8_t is_color=false, uint8_t start_point=0) {
  if ( m->not_initialized() ) {
    if ( list_loop_p == nullptr )  list_loop_p = new ListLoop(start, size, title, max, is_color, start_point);
    else                          *list_loop_p = ListLoop(start, size, title, max, is_color, start_point);
  }
  else {
    uint16_t result = list_loop_p->loop();
    if ( result ) {
      if ( result != max+1 ) {
        // Continue
        m->back();
      }
      else {
        // Cancel
        m->jump_to(255);
      }
      CLRPTR(list_loop_p);
      return result;
    }
  }

  return false;
}

uint8_t submenu_helper_pedal_param_loop(Menu *m, uint8_t parent_id, uint8_t is_fsw=true, uint8_t start_point=0) {
  if ( m->not_initialized() ) {
    if ( pedal_param_loop_p == nullptr )  pedal_param_loop_p = new PedalParamLoop(parent_id, is_fsw, start_point);
    else                                 *pedal_param_loop_p = PedalParamLoop(parent_id, is_fsw, start_point);
  }
  else {
    if ( pedal_param_loop_p->loop() ) {
      if ( pedal_param_loop_p->get_result() == (NUM_PARAMS_PER_FSW+1) ) {
        // cancel
        m->jump_to(255);
      }
      else {
        // continue
        m->back();
      }
      CLRPTR(pedal_param_loop_p);
      return true;
    }
  }

  return false;
}

uint8_t submenu_helper_text(Menu *m, char text[STR_LEN_MAX]) {
  if ( m->not_initialized() ) {
    if ( text_edit_p == nullptr )  text_edit_p = new TextEdit(text);
    else                          *text_edit_p = TextEdit(text);
  }
  else {
    if ( text_edit_p->loop() ) {
      CLRPTR(text_edit_p);
      return m->back();
    }
  }

  return false;
}

uint8_t submenu_helper_confirm(Menu *m) {
  if ( m->not_initialized() ) {
    if ( confirm_p == nullptr )  confirm_p = new Confirm;
    else                        *confirm_p = Confirm();
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
    if ( value_edit_p == nullptr )
      value_edit_p = new ValueEdit(value+1, min+1, max+1, title);
    else
      *value_edit_p = ValueEdit(value+1, min+1, max+1, title);
  }
  else {
    if ( value_edit_p->loop() ) {
      value = value_edit_p->get_result();
      CLRPTR(value_edit_p);
      m->back();
      return value;
    }
  }

  return false;
}

#endif
