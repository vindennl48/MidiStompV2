#ifdef SETTINGS_H
#define SETTINGS_H

#define E_MAIN    0
#define E_GLOBAL  1

struct Settings {
  static Menu    m;
  static uint8_t carousel_pos;

  static uint8_t loop() {
    switch( m.e() ) {
      case E_MAIN:
        if ( m.not_initialized() ) {
          // Reset all LEDs
          for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
        }
        else {
        }
        break;
    };
  }

  static carousel(uint8_t options[], uint8_t size) {
  }

};

Menu    Settings::m;
uint8_t Settings::carousel_pos = 0;

#undef E_MAIN
#undef E_GLOBAL

#endif
