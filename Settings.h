#ifndef SETTINGS_H
#define SETTINGS_H

#define E_SETTINGS     0
#define E_FSW_SETTINGS 1
#define E_FSW_COLOR    2

#define PRESET_MENU_SIZE 7
#define FSW_MENU_SIZE    4

struct Settings {
  static Menu    m;
  static uint8_t fsw_num, fsw_state, x;
  static char    text[STR_LEN_MAX];
  static uint8_t preset_menu[PRESET_MENU_SIZE];
  static uint8_t fsw_menu[FSW_MENU_SIZE];

  static bool loop(Footswitch fsw[NUM_FSW]) {
    switch( m.e() ) {
      case E_SETTINGS:
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
          else {
            for (int i=0; i<NUM_FSW; i++) {
              if ( HW::btns.at(i)->is_pressed() ) { x = 1; fsw_num = i; m.jump_to(E_FSW_SETTINGS); }
            }
          }
        }
        break;

      case E_FSW_SETTINGS:
        if ( m.not_initialized() ) {
          // Reset LEDs and Screen
          HW::leds.at(fsw_num)->set( DB::color_at( fsw[fsw_num].colors[fsw_state] ) );
          HW::screen.clear();

          DB::text_at(text, fsw_menu[x-1]);
          if ( x == 1 )  HW::screen.print(0,0, "::FSW" + String(fsw_num+1) + " S" + String(fsw_state+1));
          else           { HW::screen.print(0,0, "  "); HW::screen.print(2,0, text); }

          DB::text_at(text, fsw_menu[x]);
          HW::screen.print(0,1, ">");
          HW::screen.print(2,1, text);
        }
        else {
          if      ( HW::knob.is_left()  ) { x = CONTAIN(x-1, 1, (FSW_MENU_SIZE-1)); m.reinitialize(); }
          else if ( HW::knob.is_right() ) { x = CONTAIN(x+1, 1, (FSW_MENU_SIZE-1)); m.reinitialize(); }
          else if ( HW::knob.is_long_pressed() ) { x = 1; m.jump_to(E_SETTINGS); }
          else if ( HW::btns.at(fsw_num)->is_pressed() ) {
            fsw_state = ROTATE(fsw_state+1, 0, NUM_STATES);
            x = 1;
            m.reinitialize();
          }
        }
        break;

      case E_FSW_COLOR:
        if ( m.not_initialized() ) { }
        else                       { }
        break;
    };

    return false;
  }

};

Menu    Settings::m;
uint8_t Settings::x         = 1;
uint8_t Settings::fsw_num   = 0;
uint8_t Settings::fsw_state = 0;
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

uint8_t Settings::fsw_menu[FSW_MENU_SIZE] = {
  EEPROM_TEXT_SETTINGS,
  EEPROM_TEXT_COLORS,
  EEPROM_TEXT_SHORT_PRESS,
  EEPROM_TEXT_LONG_PRESS
};


#undef E_SETTINGS
#undef E_FSW_SETTINGS

#endif
