#ifndef LOAD_EEPROM
// Uncomment to use this program
#define ALT_PROGRAM // <----

#ifdef ALT_PROGRAM

Nav n;

Footswitch fsw[NUM_FSW_PER_PRESET];

// void setup() {
//   hw_setup();
// }
// 
// void loop() {
//   hw_loop();
// 
//   if ( n.not_init() ) {
//     Parameter parameter;
//     parameter = read_data<Parameter>(M_PRESET_PARAMS);
//     PRINT_NLINE(0,0, "PARAMETER");
//     uint16_t result = 0;
//     eReadBlock(M_PRESET_PARAMS, (uint8_t*)&result, sizeof(uint16_t));
//     PRINT_NLINE(0,1, Parameter::get_pedal(M_PRESET_PARAMS) );
//   }
//   else {
//   }
// }

void setup() {
  hw_setup();

  // First thing we have to do is load up the preset address in parents
  SET_NEW_PARENT(M_PRESETS);
}

void loop() {
  hw_loop();

  if ( n.not_init() ) {
    menu.setup(MENU_PRESET);
  }
  else {
    switch(n.e()) {
      case 0:
        if ( menu.loop() ) n.jump_to(1);
        break;

      case 1:
        PRINT_NLINE(0,0, "FINISHED");
        PRINT_NLINE(0,1, " ");
        break;
    };
  }
}

#endif
#endif
