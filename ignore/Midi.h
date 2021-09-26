#define MIDI_TYPE_NOTE_OUT 0x90
#define MIDI_TYPE_CC_OUT   0xB0
#define MIDI_TYPE_PC_OUT   0xC0

uint8_t send_midi(uint16_t parameter_addr) {
  uint8_t channel = 0;
  Parameter parameter = read_data<Parameter>(parameter_addr);

  // This means its an empty parameter
  if ( parameter.pedal == NUM_PEDALS ) return true;

  Feature feature = read_data<Feature>(GET_CHILD(M_FEATURES, parameter.pedal, parameter.feature, sizeof(Feature), NUM_FEATURES_PER_PEDAL));

  channel = Pedal::get_channel(GET_PARENT(M_PEDALS, parameter.pedal, sizeof(Pedal)));
  //feature.type = MIDI_TYPE_NOTE
  //feature.type = MIDI_TYPE_CC
  //feature.type = MIDI_TYPE_PC

#ifdef DISPLAY_DEBUG
  if      ( feature.type ==  MIDI_TYPE_NOTE ) DEBUG("MIDI> Type:     ", "Note");
  else if ( feature.type ==  MIDI_TYPE_CC )   DEBUG("MIDI> Type:     ", "CC");
  else if ( feature.type ==  MIDI_TYPE_PC )   DEBUG("MIDI> Type:     ", "PC");
  DEBUG("MIDI> Pitch:    ", feature.pitch);
  if ( feature.type != MIDI_TYPE_PC ) {
    DEBUG("MIDI> Velocity: ", parameter.velocity);
  }
#else

  if ( feature.type == MIDI_TYPE_NOTE ) {
    MIDI.sendNoteOn(feature.pitch, parameter.velocity, channel);
  }
  else if ( feature.type == MIDI_TYPE_CC ) {
    MIDI.sendControlChange(feature.pitch, parameter.velocity, channel);
  }
  else if ( feature.type == MIDI_TYPE_PC ) {
    MIDI.sendProgramChange(feature.pitch, channel);
  }

#endif

  return true;
}

// uint8_t send_midi(uint16_t parameter_addr) {
//   uint8_t command;
//   Parameter parameter = read_data<Parameter>(parameter_addr);
// 
//   // This means its an empty parameter
//   if ( parameter.pedal == NUM_PEDALS ) return true;
// 
//   Feature feature = read_data<Feature>(GET_CHILD(M_FEATURES, parameter.pedal, parameter.feature, sizeof(Feature), NUM_FEATURES_PER_PEDAL));
// 
//   command = Pedal::get_channel(GET_PARENT(M_PEDALS, parameter.pedal, sizeof(Pedal)));
//   if      ( feature.type ==  MIDI_TYPE_NOTE ) command += MIDI_TYPE_NOTE_OUT;
//   else if ( feature.type ==  MIDI_TYPE_CC )   command += MIDI_TYPE_CC_OUT;
//   else if ( feature.type ==  MIDI_TYPE_PC )   command += MIDI_TYPE_PC_OUT;
// 
// #ifdef DISPLAY_DEBUG
//   if      ( feature.type ==  MIDI_TYPE_NOTE ) DEBUG("MIDI> Type:     ", "Note");
//   else if ( feature.type ==  MIDI_TYPE_CC )   DEBUG("MIDI> Type:     ", "CC");
//   else if ( feature.type ==  MIDI_TYPE_PC )   DEBUG("MIDI> Type:     ", "PC");
//   DEBUG("MIDI> Pitch:    ", feature.pitch);
//   if ( feature.type != MIDI_TYPE_PC ) {
//     DEBUG("MIDI> Velocity: ", parameter.velocity);
//   }
// #else
//   // Note type and channel
//   Serial.write(command);
// 
//   // Pitch
//   Serial.write(feature.pitch);
// 
//   if ( feature.type != MIDI_TYPE_PC ) {
//     // Velocity
//     Serial.write(parameter.velocity);
//   }
// #endif
// 
//   return true;
// }

// fsw_submenu_id: 0-4
void send_fsw_midi(uint8_t fsw_submenu_id) {
  uint16_t param_addr = GET_FSW_PARAM_ADDR(fsw_submenu_id, 0);
  uint8_t  skip_first = false;

  if ( fsw[GET_FSW_PRESET_ID(fsw_submenu_id)].mode == FSW_MODE_SUBMENU || fsw[GET_FSW_PRESET_ID(fsw_submenu_id)].mode == FSW_MODE_PRESET ) {
    // If we are using submenu or preset mode, the first parameter is not actually MIDI
    skip_first = true;
  }

  for ( uint16_t i=param_addr, j=0; j<NUM_FSW_PARAMS_PER_STATE; i+=sizeof(Parameter), j++ ) {
    if ( !(j == 0 && skip_first) ) send_midi(i);
  }
}

// fsw_submenu_id: 0-4
void send_fsw_lp_midi(uint8_t fsw_submenu_id) {
  uint16_t param_addr = GET_FSW_LP_PARAM_ADDR(fsw_submenu_id, 0);
  uint8_t  skip_first = false;

  if ( fsw[GET_FSW_PRESET_ID(fsw_submenu_id)].lp_mode == FSW_MODE_SUBMENU || fsw[GET_FSW_PRESET_ID(fsw_submenu_id)].lp_mode == FSW_MODE_PRESET ) {
    // If we are using submenu or preset mode, the first parameter is not actually MIDI
    skip_first = true;
  }

  for ( uint16_t i=param_addr, j=0; j<NUM_FSW_PARAMS_PER_STATE; i+=sizeof(Parameter), j++ ) {
    if ( !(j == 0 && skip_first) ) send_midi(i);
  }
}
