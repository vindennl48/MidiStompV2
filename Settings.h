#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
  Menu     m;
  MenuLoop mloop;

  bool loop() {
    switch(m.e()) {
      /* :: PRESET SETTINGS :: */
      case E_PRESET:
        if ( m.not_initialized() ) {
          mloop.reset(EEPROM_PRESET_MENU);
        }
        else {
          switch(mloop.loop()) {
            default: //loop
              break;

            case 1: //E_PRESET_SAVE
              m.jump_to(E_PRESET_SAVE);
              break;

            case 2: //E_PRESET_NAME
              m.jump_to(E_PRESET_NAME);
              break;

            //case 3: //E_PRESET_PARAMS
              //m.jump_to(E_PRESET_PARAMS);
              //break;

            //case 4: //E_PRESET_COPY
              //m.jump_to(E_PRESET_COPY);
              //break;

            //case 5: //E_PRESET_RESET
              //m.jump_to(E_PRESET_RESET);
              //break;

            case 6: //E_GLOBAL
              m.jump_to(E_GLOBAL);
              break;
          };
        }
        break;

      case E_PRESET_SAVE:
        if ( m.not_initialized() ) {
          confirm_p = new Confirm;
        }
        else {
          switch( confirm.loop() ) {
            case 0: //loop
              break;

            case LTRUE:
              /*save*/
              DB::preset_save(preset_id, &preset);
            default:
            case LFALSE:
              /*cancel*/
              m.jump_to(E_PRESET);
              CLRPTR(confirm_p);
              break;
          };
        }
        break;

      case E_PRESET_NAME:
        if ( m.not_initialized() ) {
          text_edit_p = new TextEdit(preset.name);
        }
        else {
          if ( *text_edit_p->loop() ) {
            CLRPTR(text_edit_p);
            m.jump_to(E_PRESET);
          }
        }
        break;

      // PARAM SUBMENU
      case E_PRESET_PARAMS:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;

      case E_PRESET_PARAM:
        if ( m.not_initialized() ) {
          mloop.reset(EEPROM_PRESET_PARAM_MENU);
        }
        else {
        }
        break;

      case E_PRESET_PARAM_CHANGE:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;

      case E_PRESET_PARAM_VALUE:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;

      case E_PRESET_PARAM_RESET:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;
      // END PARAM SUBMENU

      case E_PRESET_COPY:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;

      case E_PRESET_RESET:
        if ( m.not_initialized() ) {
        }
        else {
        }
        break;
      /* :: END PRESET SETTINGS :: */

      /* :: GLOBAL SETTINGS :: */
      case E_GLOBAL:
        if ( m.not_initialized() ) {
          mloop.reset(EEPROM_GLOBAL_MENU);
        }
        else {
        }
        break;
      /* :: END GLOBAL SETTINGS :: */


      /* :: EXIT SETTINGS :: */
      default:
      case NUM_MENU_ITEMS:
        return m.back();
        break;
      /* :: END EXIT SETTINGS :: */
    };

    return false;
  }

} *settings_p = nullptr;

#endif
