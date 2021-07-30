#ifndef SETTINGS_H
#define SETTINGS_H

#define E_PRESET              0
#define E_PRESET_SAVE         1
#define E_PRESET_NAME         2
#define E_PRESET_PARAMS       3
#define E_PRESET_PARAM        4
#define E_PRESET_PARAM_CHANGE 5
#define E_PRESET_PARAM_VALUE  6
#define E_PRESET_PARAM_RESET  7
#define E_PRESET_COPY         8
#define E_PRESET_RESET        9
#define E_GLOBAL              10
#define E_GLOBAL_COLORS       11
#define E_GLOBAL_COLOR        12
#define E_GLOBAL_COLOR_NAME   13
#define E_GLOBAL_COLOR_VALUE  14
#define E_EXIT                255

struct Settings {
  Menu     m;
  MenuLoop mloop;

  bool loop() {
    switch(m.e()) {
      /* :: PRESET SETTINGS :: */
      case E_PRESET:
        if ( m.not_initialized() ) {
          mloop.reset(EEP_PRESET_MENU);
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

            case E_EXIT:
              m.jump_to(E_EXIT);
              break;
          };
        }
        break;

      case E_PRESET_SAVE:
        if ( m.not_initialized() ) {
          confirm_p = new Confirm;
        }
        else {
          switch( confirm_p->loop() ) {
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
          if ( text_edit_p->loop() ) {
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
          mloop.reset(EEP_PRESET_PARAM_MENU);
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
          mloop.reset(EEP_GLOBAL_MENU);
        }
        else {
          switch(mloop.loop()) {
            default: //loop
              break;

            //case 1: // E_GLOBAL_PEDALS
              //m.jump_to(E_GLOBAL_PEDALS);
              //break;

            case 2: // E_GLOBAL_COLORS
              m.jump_to(E_GLOBAL_COLORS);
              break;

            //case 3: // E_GLOBAL_RESET
              //m.jump_to();
              //break;

            case E_EXIT:
              m.jump_to(E_PRESET);
              break;
          };
        }
        break;

      // PEDALS SUBMENU
      //case E_GLOBAL_PEDALS:
        //break;
      // END PEDALS SUBMENU

      // COLORS SUBMENU
      case E_GLOBAL_COLORS:
        if ( m.not_initialized() ) {
          if ( list_loop_p == nullptr ) {
            list_loop_p = new ListLoop(
              EEP_START_COLORS,
              sizeof(Color),
              "COLORS",
              EEP_NUM_COLORS,
              true
            );
          }
        }
        else {
          if ( list_loop_p->loop() ) {
            if ( list_loop_p->get_result() == EEP_NUM_COLORS ) {
              //cancel
              m.jump_to(E_GLOBAL);
              CLRPTR(list_loop_p);
            }
            else {
              color_p  = new Color;
              *color_p = DB::color_at(list_loop_p->get_result());
              m.jump_to(E_GLOBAL_COLOR);
            }
          }
        }
        break;

      case E_GLOBAL_COLOR:
        if ( m.not_initialized() ) {
          mloop.reset(EEP_GLOBAL_COLOR_MENU, color_p->name);
        }
        else {
          switch(mloop.loop()) {
            default: //loop
              break;

            case 1: //NAME
              m.jump_to(E_GLOBAL_COLOR_NAME);
              break;

            case 2: //VALUE
              m.jump_to(E_GLOBAL_COLOR_VALUE);
              break;

            //case 3: //RESET
              //break;

            case E_EXIT:
              m.jump_to(E_GLOBAL_COLORS);
              CLRPTR(color_p);
              break;
          }
        }
        break;

      case E_GLOBAL_COLOR_NAME:
        if ( m.not_initialized() ) {
          text_edit_p = new TextEdit(color_p->name);
        }
        else {
          if ( text_edit_p->loop() ) {
            DB::color_save(list_loop_p->get_result(), color_p);
            m.jump_to(E_GLOBAL_COLOR);
            CLRPTR(text_edit_p);
          }
        }
        break;

      case E_GLOBAL_COLOR_VALUE:
        if ( m.not_initialized() ) {
          color_edit_p = new ColorEdit(color_p);
        }
        else {
          if ( color_edit_p->loop() ) {
            if ( color_edit_p->get_result() == LTRUE ) {
              DB::color_save(list_loop_p->get_result(), color_p);
            }
            m.jump_to(E_GLOBAL_COLOR);
            CLRPTR(color_edit_p);
          }
        }
        break;
      // END COLORS SUBMENU

      /* :: END GLOBAL SETTINGS :: */


      /* :: EXIT SETTINGS :: */
      default:
      case E_EXIT:
        return m.back();
        break;
      /* :: END EXIT SETTINGS :: */
    };

    return false;
  }

} *settings_p = nullptr;

#endif
