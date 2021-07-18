#ifndef SETTINGS_H
#define SETTINGS_H

#define E_MAIN               0
#define E_GLOBAL             1
#define E_GLOBAL_COLORS      2
#define E_GLOBAL_COLOR       3
#define E_GLOBAL_COLOR_NAME  4
#define E_GLOBAL_COLOR_VALUE 5
#define E_FSW                6
#define E_PRESET_NAME        7

struct Settings {
  static Menu     m;
  static MenuLoop mloop;
  static ListLoop lloop;
  static Color    color;
  static uint8_t  fsw_num, submenu, state, temp;

  static bool loop() {
    switch( m.e() ) {
      default:

      case E_MAIN:
        if ( m.not_initialized() ) {
          mloop.reset(0);
          state = 0; // reset the fsw state
          for (int i=0;i<4; i++) HW::leds.at(i)->set(0,0,0);
        }
        else {
          switch( mloop.loop() ) {
            default:
            case 0: // No response yet
              break;
            case 1: // SAVE
              return m.back();
              break;
            case 2: // NAME
              m.jump_to( E_PRESET_NAME );
              break;
            case 3: // PARAMS
              break;

            case 6: // GLOBAL
              m.jump_to( E_GLOBAL );
              break;

            case NUM_MENU_ITEMS:
              return m.back();
              break;
          };

          if      ( HW::btns.at(0)->is_pressed() ) { fsw_num = 0; m.jump_to(E_FSW); }
          else if ( HW::btns.at(1)->is_pressed() ) { fsw_num = 1; m.jump_to(E_FSW); }
          else if ( HW::btns.at(2)->is_pressed() ) { fsw_num = 2; m.jump_to(E_FSW); }
          else if ( HW::btns.at(3)->is_pressed() ) { fsw_num = 3; m.jump_to(E_FSW); }
        }
        break;

      case E_PRESET_NAME:
        if ( m.not_initialized() ) { TextEdit::setup( preset.name ); }
        else                       { if ( TextEdit::loop() ) m.jump_to( E_MAIN ); }
        break;

      case E_GLOBAL:
        if ( m.not_initialized() ) {
          mloop.reset(1);
        }
        else {
          switch( mloop.loop() ) {
            default:
            case 0:
              break;
            case 1:
              break;
            case 2:  // COLORS
              m.jump_to( E_GLOBAL_COLORS );
              break;

            case NUM_MENU_ITEMS:
              return m.back();
              break;
          };
        }
        break;

      case E_GLOBAL_COLORS:
        if ( m.not_initialized() ) {
          lloop.reset(EEPROM_START_COLORS, sizeof(Color), "COLORS", EEPROM_NUM_COLORS, true);
        }
        else {
          temp = lloop.loop();
          if ( temp == EEPROM_NUM_COLORS ) m.jump_to( E_GLOBAL );
          else if ( temp ) {
            temp -=1;
            m.jump_to( E_GLOBAL_COLOR );
          }
        }
        break;

      case E_GLOBAL_COLOR:
        if ( m.not_initialized() ) {
          mloop.reset(4, String(DB::color_at(temp).name) );
          for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set( DB::color_at(temp) );
        }
        else {
          switch( mloop.loop() ) {
            default:
            case 0:
              break;
            case 1:  // NAME
              m.jump_to( E_GLOBAL_COLOR_NAME );
              break;
            case 2:  // VALUES
              m.jump_to( E_GLOBAL_COLOR_VALUE );
              break;

            case NUM_MENU_ITEMS:
              m.jump_to( E_GLOBAL_COLORS );
              for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
              break;
          };
        }
        break;

      case E_GLOBAL_COLOR_NAME:
        if ( m.not_initialized() ) {
          color = DB::color_at(temp);
          TextEdit::setup(color.name);
        }
        else {
          if ( TextEdit::loop() ) {
            DB::color_save(temp, color);
            m.jump_to( E_GLOBAL_COLOR );
          }
        }
        break;

      case E_GLOBAL_COLOR_VALUE:
        if ( m.not_initialized() ) { ColorEdit::setup(temp); }
        else                       { if ( ColorEdit::loop() ) m.jump_to( E_GLOBAL_COLOR ); }
        break;

      case E_FSW:
        if ( m.not_initialized() ) {
          mloop.reset(2);
          HW::leds.at(fsw_num)->set( DB::color_at( fsw[submenu][fsw_num].colors[state] ) );
        }
        else {
          switch( mloop.loop() ) {
            default:
            case 0:
              break;
            case 1:
              return m.back();
              break;

            case NUM_MENU_ITEMS:
              return m.back();
              break;
          };
        }
        break;
    };

    return false;
  }

};

Menu     Settings::m;
MenuLoop Settings::mloop;
ListLoop Settings::lloop;
Color    Settings::color;
uint8_t  Settings::fsw_num = 0;
uint8_t  Settings::submenu = 0;
uint8_t  Settings::state   = 0;
uint8_t  Settings::temp    = 0;

#undef E_MAIN
#undef E_GLOBAL
#undef E_GLOBAL_COLORS
#undef E_GLOBAL_COLOR
#undef E_GLOBAL_COLOR_NAME
#undef E_GLOBAL_COLOR_VALUE
#undef E_FSW
#undef E_PRESET_NAME

#endif
