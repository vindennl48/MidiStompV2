#ifndef DATABASE_H
#define DATABASE_H

//#define MIDI_START    4
//#define MIDI_SIZE     10

//#define DEVICES_START 4
//#define DEVICES_SIZE  4

//#define COLORS_START  4
//#define COLORS_SIZE   4

//#define PRESETS_START 4
//#define PRESETS_SIZE  4


#define CHAR_LEN  16


/*  :: TEMPLATES :: */
template <typename T>
T get_data(uint16_t id, uint16_t max, uint16_t shift) {
/*
  * shift is for the start location in EEPROM for the data
  * you are trying to access.
  *
  * max is the limit of amount of objects that can be stored
  * for that particular eeprom storage type.
  */
  unsigned int size = sizeof(T);
  T            data;

  if ( id >= max ) {
    id = max-1;
  }

  eeprom_read_block(
    (void*)&data,
    (void*)(size * (id + shift)),
    size
  );
  return data;
}

template <typename T>
void set_data(T *data, uint16_t max, uint16_t shift) {
/*
  * shift is for the start location in EEPROM for the data
  * you are trying to access.
  *
  * max is the limit of amount of objects that can be stored
  * for that particular eeprom storage type.
  */
  unsigned int size = sizeof(T);

  if ( data->id >= max ) {
    data->id = max-1;
  }

  eeprom_write_block(
    (const void*)data,
    (void*)(size * (data->id + shift)),
    size
  );
}
/*  :: END TEMPLATES :: */


/* :: MIDI :: */
#define MIDI_KIND_MAX 3
#define MIDI_NOTE_MAX 128
String midiKind[] = { "NOTE", "CC", "PC" };
struct Midi {
  uint8_t id = 0, kind = 0, note = 0;  
  void   kind_up()      { kind += 1; if ( kind >= MIDI_KIND_MAX ) kind = MIDI_KIND_MAX-1; }
  void   kind_down()    { if ( kind > 0 ) kind -= 1; }
  void   note_up()      { note += 1; if ( note >= MIDI_NOTE_MAX ) note = MIDI_NOTE_MAX-1; }
  void   note_down()    { if ( note > 0 ) note -= 1; }
  String get_kind_str() { return midiKind[kind]; }
  void   set_kind(uint8_t new_kind) { if ( new_kind < MIDI_KIND_MAX ) kind = new_kind; }
};
#define MIDI_MAX   10
#define MIDI_SHIFT 4
#define SET_MIDI(midi) set_data<Midi>(midi, MIDI_MAX, MIDI_SHIFT)
#define GET_MIDI(id)   get_data<Midi>(id,   MIDI_MAX, MIDI_SHIFT)
/* :: END MIDI :: */


/* :: DEVICE :: */
struct Device {
private:
  char name[CHAR_LEN] = "UNTITLED       ";
public:
  uint8_t id      = 0;
  uint8_t channel = 0;

  void   set_name(String new_name) { new_name.toCharArray(name, CHAR_LEN); }
  String get_name()                { return String(name); }

  struct parameter {
  private:
    char name[CHAR_LEN] = "PARAM          ";
  public:
    uint8_t midi_id = 0;

    void   set_name(String new_name) { new_name.toCharArray(name, CHAR_LEN); }
    String get_name()                { return String(name); }
  } params[10];
};
#define DEVICE_MAX   4
#define DEVICE_SHIFT ( ( sizeof(Midi) * MIDI_MAX ) + MIDI_SHIFT )
#define SET_DEVICE(device) set_data<Device>(device, DEVICE_MAX, DEVICE_SHIFT)
#define GET_DEVICE(id)     get_data<Device>(id,     DEVICE_MAX, DEVICE_SHIFT)
/* :: END DEVICE :: */


#endif
