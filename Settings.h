#ifndef SETTINGS_H
#define SETTINGS_H

#define E_MAIN 0

struct Settings {
  static Menu     m;
  static MenuLoop mloop;

  static bool loop() {
    switch( m.e() ) {
      default:
      case E_MAIN:
        if ( m.not_initialized() ) {
          mloop.reset(0);
        }
        else {
          switch( mloop.loop() ) {
            default:
            case 0: // No response yet
              break;
            case 1: // SAVE
              return true;
              break;
            case 2: // NAME
              break;
            case 3: // PARAMS
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

#endif
