#ifndef SETTINGS_H
#define SETTINGS_H

#define E_MAIN        0
#define E_FSW         1
#define E_PRESET_NAME 2

struct Settings {
  static Menu     m;
  static MenuLoop mloop;
  static uint8_t  fsw_num, submenu, state;

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
uint8_t  Settings::fsw_num = 0;
uint8_t  Settings::submenu = 0;
uint8_t  Settings::state   = 0;

#undef E_MAIN
#undef E_FSW
#undef E_PRESET_NAME

#endif
