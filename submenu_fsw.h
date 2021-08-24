#ifndef SUBMENU_FSW_H
#define SUBMENU_FSW_H

uint8_t submenu_fsw_mode_off(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_OFF;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_toggle(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_TOGGLE;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_cycle(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_CYCLE;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_oneshot(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_ONESHOT;
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_submenu(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_SUBMENU;
  // Use the velocity value from the first MIDI param
  m->jump_to(255);
  return true;
}

uint8_t submenu_fsw_mode_preset(Menu *m) {
  fsw_p[sel_fsw_id].mode = FSW_MODE_PRESET;
  m->jump_to(255);
  return true;
}

#endif
