#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#define E_SUBMENU   0
#define E_OPTION    1

#define F_SUBMENU_PRESET_SAVE              1
#define F_SUBMENU_PRESET_NAME              2
#define F_SUBMENU_PRESET_PARAMS            3
#define F_SUBMENU_PRESET_PARAM_PEDAL       4
#define F_SUBMENU_PRESET_PARAM_PEDAL_PARAM 5
#define F_SUBMENU_PRESET_PARAM_VELOCITY    6
#define F_SUBMENU_PRESET_PARAM_RESET       7
#define F_SUBMENU_PRESET_COPY              8
#define F_SUBMENU_PRESET_RESET             9
#define F_SUBMENU_PEDALS                   10
#define F_SUBMENU_PEDAL_NAME               11
#define F_SUBMENU_PEDAL_PARAMS             12
#define F_SUBMENU_PEDAL_PARAM_NAME         13
#define F_SUBMENU_PEDAL_PARAM_TYPE_NONE    14
#define F_SUBMENU_PEDAL_PARAM_TYPE_NOTE    15
#define F_SUBMENU_PEDAL_PARAM_TYPE_CC      16
#define F_SUBMENU_PEDAL_PARAM_TYPE_PC      17
#define F_SUBMENU_PEDAL_PARAM_PITCH        18
#define F_SUBMENU_PEDAL_PARAM_RESET        19
#define F_SUBMENU_PEDAL_CHAN               20
#define F_SUBMENU_PEDAL_RESET              21
#define F_SUBMENU_COLORS                   22
#define F_SUBMENU_COLOR_NAME               23
#define F_SUBMENU_COLOR_EDIT               24
#define F_SUBMENU_COLOR_RESET              25
#define F_SUBMENU_FSW_COLOR                26
#define F_SUBMENU_FSW_MODE_OFF             27
#define F_SUBMENU_FSW_MODE_TOGGLE          28
#define F_SUBMENU_FSW_MODE_CYCLE           29
#define F_SUBMENU_FSW_MODE_ONESHOT         30
#define F_SUBMENU_FSW_MODE_SUBMENU         31
#define F_SUBMENU_FSW_MODE_PRESET          32
#define F_SUBMENU_FSW_PARAMS               33
#define F_SUBMENU_FSW_PARAM_PEDAL          34
#define F_SUBMENU_FSW_PARAM_PEDAL_PARAM    35
#define F_SUBMENU_FSW_PARAM_VELOCITY       36
#define F_SUBMENU_FSW_PARAM_RESET          37
#define F_SUBMENU_FSW_PRESS_TYPE_UP        38
#define F_SUBMENU_FSW_PRESS_TYPE_DOWN      39
#define F_SUBMENU_FSW_LP_MODE_OFF          40
#define F_SUBMENU_FSW_LP_MODE_ONESHOT      41
#define F_SUBMENU_FSW_LP_MODE_SUBMENU      42
#define F_SUBMENU_FSW_LP_MODE_PRESET       43
#define F_SUBMENU_FSW_LP_PARAMS            44
#define F_SUBMENU_FSW_LP_PARAM_PEDAL       45
#define F_SUBMENU_FSW_LP_PARAM_PEDAL_PARAM 46
#define F_SUBMENU_FSW_LP_PARAM_VELOCITY    47
#define F_SUBMENU_FSW_LP_PARAM_RESET       48
#define F_SUBMENU_FSW_LP_RESET             49

typedef uint8_t (*SelectedFunction)(Menu*);

SelectedFunction get_selected_function(uint8_t id) {
  switch(id) {
    case F_SUBMENU_PRESET_SAVE:              return &submenu_preset_save;
    case F_SUBMENU_PRESET_NAME:              return &submenu_preset_name;
    case F_SUBMENU_PRESET_PARAMS:            return &submenu_preset_params;
    case F_SUBMENU_PRESET_PARAM_PEDAL:       return &submenu_preset_param_pedal;
    case F_SUBMENU_PRESET_PARAM_PEDAL_PARAM: return &submenu_preset_param_pedal_param;
    case F_SUBMENU_PRESET_PARAM_VELOCITY:    return &submenu_preset_param_velocity;
    case F_SUBMENU_PRESET_PARAM_RESET:       return &submenu_preset_param_reset;
    case F_SUBMENU_PRESET_COPY:              return &submenu_preset_copy;
    case F_SUBMENU_PRESET_RESET:             return &submenu_preset_reset;
    case F_SUBMENU_PEDALS:                   return &submenu_pedals;
    case F_SUBMENU_PEDAL_NAME:               return &submenu_pedal_name;
    case F_SUBMENU_PEDAL_PARAMS:             return &submenu_pedal_params;
    case F_SUBMENU_PEDAL_PARAM_NAME:         return &submenu_pedal_param_name;
    case F_SUBMENU_PEDAL_PARAM_TYPE_NONE:    return &submenu_pedal_param_type_none;
    case F_SUBMENU_PEDAL_PARAM_TYPE_NOTE:    return &submenu_pedal_param_type_note;
    case F_SUBMENU_PEDAL_PARAM_TYPE_CC:      return &submenu_pedal_param_type_cc;
    case F_SUBMENU_PEDAL_PARAM_TYPE_PC:      return &submenu_pedal_param_type_pc;
    case F_SUBMENU_PEDAL_PARAM_PITCH:        return &submenu_pedal_param_pitch;
    case F_SUBMENU_PEDAL_PARAM_RESET:        return &submenu_pedal_param_reset;
    case F_SUBMENU_PEDAL_CHAN:               return &submenu_pedal_channel;
    case F_SUBMENU_PEDAL_RESET:              return &submenu_pedal_reset;
    case F_SUBMENU_COLORS:                   return &submenu_colors;
    case F_SUBMENU_COLOR_NAME:               return &submenu_color_name;
    case F_SUBMENU_COLOR_EDIT:               return &submenu_color_edit;
    case F_SUBMENU_COLOR_RESET:              return &submenu_color_reset;
    case F_SUBMENU_FSW_COLOR:                return &submenu_fsw_color;
    case F_SUBMENU_FSW_MODE_OFF:             return &submenu_fsw_mode_off;
    case F_SUBMENU_FSW_MODE_TOGGLE:          return &submenu_fsw_mode_toggle;
    case F_SUBMENU_FSW_MODE_CYCLE:           return &submenu_fsw_mode_cycle;
    case F_SUBMENU_FSW_MODE_ONESHOT:         return &submenu_fsw_mode_oneshot;
    case F_SUBMENU_FSW_MODE_SUBMENU:         return &submenu_fsw_mode_submenu;
    case F_SUBMENU_FSW_MODE_PRESET:          return &submenu_fsw_mode_preset;
    case F_SUBMENU_FSW_PARAMS:               return &submenu_fsw_params;
    case F_SUBMENU_FSW_PARAM_PEDAL:          return &submenu_fsw_param_pedal;
    case F_SUBMENU_FSW_PARAM_PEDAL_PARAM:    return &submenu_fsw_param_pedal_param;
    case F_SUBMENU_FSW_PARAM_VELOCITY:       return &submenu_fsw_param_velocity;
    case F_SUBMENU_FSW_PARAM_RESET:          return &submenu_fsw_param_reset;
    case F_SUBMENU_FSW_PRESS_TYPE_UP:        return &submenu_fsw_press_type_up;
    case F_SUBMENU_FSW_PRESS_TYPE_DOWN:      return &submenu_fsw_press_type_down;
    case F_SUBMENU_FSW_LP_MODE_OFF:          return &submenu_fsw_lp_mode_off;
    case F_SUBMENU_FSW_LP_MODE_ONESHOT:      return &submenu_fsw_lp_mode_oneshot;
    case F_SUBMENU_FSW_LP_MODE_SUBMENU:      return &submenu_fsw_lp_mode_submenu;
    case F_SUBMENU_FSW_LP_MODE_PRESET:       return &submenu_fsw_lp_mode_preset;
    case F_SUBMENU_FSW_LP_PARAMS:            return &submenu_fsw_lp_params;
    case F_SUBMENU_FSW_LP_PARAM_PEDAL:       return &submenu_fsw_lp_param_pedal;
    case F_SUBMENU_FSW_LP_PARAM_PEDAL_PARAM: return &submenu_fsw_lp_param_pedal_param;
    case F_SUBMENU_FSW_LP_PARAM_VELOCITY:    return &submenu_fsw_lp_param_velocity;
    case F_SUBMENU_FSW_LP_PARAM_RESET:       return &submenu_fsw_lp_param_reset;
    case F_SUBMENU_FSW_LP_RESET:             return &submenu_fsw_lp_reset;
  };

  return nullptr;
}

struct MenuHost {
  /* Function to run the entire menu system */

  Menu             m, m_sub;
  MenuHost         *sub_menu_host = nullptr;
  SubMenu          sub_menu;
  MenuOption       menu_option_1, menu_option_2;
  SelectedFunction selected_function;
  uint8_t          sub_menu_id    = 0;
  uint8_t          x              = 1;
  uint8_t          func_or_sub    = 0;

  void setup(uint8_t sub_menu_id) {
    this->sub_menu_id = sub_menu_id;
    sub_menu          = DB::sub_menu_at(sub_menu_id);
  }

  void change_title(const char title[STR_LEN_MAX]) {
    strcpy(sub_menu.title, title);
  }

  uint8_t loop() {
    switch(m.e()) {
      default:
      case E_SUBMENU:
        if ( m.not_initialized() ) {
          menu_option_1 = DB::menu_option_at(sub_menu_id, x-1);
          menu_option_2 = DB::menu_option_at(sub_menu_id, x);

          /* First Line */
          if ( x == 1 ) {
            HW::screen.print(0,0, "::");
            HW::screen.print_with_nline(2,0, sub_menu.title);
          }
          else {
            HW::screen.print(0,0, "  ");
            HW::screen.print_with_nline(2,0, menu_option_1.text);
          }

          /* Second Line */
          HW::screen.print(0,1, "> ");
          HW::screen.print_with_nline(2,1, menu_option_2.text);
        }
        else {
          if ( HW::knob.is_left() ) {
            x = CONTAIN(x-1, 1, sub_menu.num_options-1);
            m.reinitialize();
          }
          else if ( HW::knob.is_right() ) {
            x = CONTAIN(x+1, 1, sub_menu.num_options-1);
            m.reinitialize();
          }
          else if ( HW::knob.is_pressed() ) {
            if ( menu_option_2.type != MENU_TYPE_DUMMY ) m.jump_to(E_OPTION);
          }
          else if ( HW::knob.is_long_pressed() ) {
            return m.back();
          }
        }
        break;

      case E_OPTION:
        if ( m.not_initialized() ) {
          if ( menu_option_2.type == MENU_TYPE_SUB_MENU || menu_option_2.type == MENU_TYPE_FUNC_AND_SUB ) {
            sub_menu_host = new MenuHost;
            if ( menu_option_2.type == MENU_TYPE_FUNC_AND_SUB )
              sub_menu_host->setup(menu_option_2.value2);
            else
              sub_menu_host->setup(menu_option_2.value);
          }
          if ( menu_option_2.type == MENU_TYPE_FUNCTION || menu_option_2.type == MENU_TYPE_FUNC_AND_SUB ) {
            selected_function = get_selected_function(menu_option_2.value);
          }
        }
        else {
          if ( menu_option_2.type == MENU_TYPE_SUB_MENU ) {
            if ( sub_menu_host->loop() ) {
              CLRPTR(sub_menu_host);
              m.jump_to(E_SUBMENU);
            }
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNCTION ) {
            if ( selected_function(&m_sub) ) {
              if ( m_sub.event == 255 ) {
                m_sub.back();
                return m.back();
              }
              else {
                m_sub.back();
                m.jump_to(E_SUBMENU);
              }
            }
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNC_AND_SUB ) {
            if ( !func_or_sub ) {
              if ( selected_function(&m_sub) ) {
                if ( m_sub.event == 255 ) {
                  m.jump_to(E_SUBMENU);
                  CLRPTR(sub_menu_host);
                }
                else {
                  func_or_sub = true; 
                }
                m_sub.back();
              }
            }
            else {
              if ( sub_menu_host->loop() ) {
                func_or_sub = false;
                CLRPTR(sub_menu_host);
                m.reinitialize();
              }
            }
          }
        }
        break;
    };

    return false;
  }

};

#undef E_SUBMENU
#undef E_OPTION


#endif
