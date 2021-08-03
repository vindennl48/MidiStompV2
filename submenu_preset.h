#ifndef SUBMENU_PRESET_H
#define SUBMENU_PRESET_H

uint8_t submenu_preset_save  (Menu *m) {
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

uint8_t submenu_preset_name  (Menu *m) {
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

uint8_t submenu_preset_params(Menu *m) { }
uint8_t submenu_preset_copy  (Menu *m) { }
uint8_t submenu_preset_reset (Menu *m) { }

#endif
