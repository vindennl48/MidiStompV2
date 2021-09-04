#ifndef LOAD_EEPROM
// Uncomment to use this program
#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

Footswitch fsw[NUM_FSW_PER_PRESET];

void setup() {
  hw_setup();
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    // GET_ABS_CHILD_ID_2(parent_id1, parent_id2, child_id, num_children_in_parent2, num_parent2_in_parent1)
    // preset_id, submenu_id
    PRINT_NLINE(0,0, FswParam::get_feature( GET_ABS_CHILD_ID_2(2, 0, 2, NUM_FSW_PER_SUBMENU, NUM_SUBMENUS_PER_PRESET) ));
  }
}

#endif
#endif
