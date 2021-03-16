#ifndef DATABASE_H
#define DATABASE_H


/*
  2 bits for note type
  7 bits for note
  7 bits for default velocity
  Total: 2 bytes / 16 bits
*/
#define MIDI_START    4
#define MIDI_SIZE     2

#define DEVICES_START 4
#define DEVICES_SIZE  4

#define COLORS_START  4
#define COLORS_SIZE   4

#define PRESETS_START 4
#define PRESETS_SIZE  4


namespace DB {

  struct Midi { uint8_t id = 0, kind = 0, note = 0;  };
  void set_midi(Midi *data) {
    unsigned int size = sizeof(Midi);
    eeprom_write_block((const void*)data, (void*)(size * data->id), size);
  }
  Midi get_midi(uint8_t id) {
    unsigned int size = sizeof(Midi);
    Midi         midi;
    eeprom_read_block((void*)&midi, (void*)(size * id), size);
    return midi;
  }

};


#endif


/*
void saveChan() {
  unsigned int size = sizeof(Channel);
  unsigned int pos  = (size * selChan);
  eeprom_write_block((const void*)&chan, (void*)pos, size);
}

void loadChan() {
  unsigned int size = sizeof(Channel);
  unsigned int pos  = (size * selChan);
  eeprom_read_block((void*)&chan, (void*)pos, size);
}
*/
