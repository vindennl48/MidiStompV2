#ifndef SETTINGS_H
#define SETTINGS_H

#define E_MAIN    0
#define E_GLOBAL  1

#define PRESET_MENU_SIZE 7

struct Settings {
  static Menu    m;
  static uint8_t x;
  static char    text[STR_LEN_MAX];
  static uint8_t preset_menu[PRESET_MENU_SIZE];

  static bool loop() {
    if ( m.not_initialized() ) {
      // Reset LEDs and Screen
      for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
      HW::screen.clear();

      DB::text_at(text, preset_menu[x-1]);
      if ( x == 1 )  HW::screen.print(0,0, "::");
      else           HW::screen.print(0,0, "  ");
      HW::screen.print(2,0, text);

      DB::text_at(text, preset_menu[x]);
      HW::screen.print(0,1, ">");
      HW::screen.print(2,1, text);
    }
    else {
      if      ( HW::knob.is_left()  ) { x = CONTAIN(x-1, 1, (PRESET_MENU_SIZE-1)); m.reinitialize(); }
      else if ( HW::knob.is_right() ) { x = CONTAIN(x+1, 1, (PRESET_MENU_SIZE-1)); m.reinitialize(); }
      else if ( HW::knob.is_long_pressed() ) { x = 1; return m.back(); }
    }

    return false;
  }

};

Menu    Settings::m;
uint8_t Settings::x = 1;
char    Settings::text[STR_LEN_MAX];

uint8_t Settings::preset_menu[PRESET_MENU_SIZE] = {
  EEPROM_TEXT_SETTINGS,
  EEPROM_TEXT_SAVE,
  EEPROM_TEXT_NAME,
  EEPROM_TEXT_PARAMS,
  EEPROM_TEXT_COPY,
  EEPROM_TEXT_RESET,
  EEPROM_TEXT_GLOBAL
};


#undef E_MAIN
#undef E_GLOBAL

#endif
