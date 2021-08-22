#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#define E_SUBMENU   0
#define E_OPTION    1

#define F_SUBMENU_PRESET_SAVE        1
#define F_SUBMENU_PRESET_NAME        2
#define F_SUBMENU_PRESET_PARAMS      3
#define F_SUBMENU_PRESET_PARAM_PEDAL 4
#define F_SUBMENU_PRESET_COPY        5
#define F_SUBMENU_PRESET_RESET       6
#define F_SUBMENU_PEDALS             7
#define F_SUBMENU_PEDAL_NAME         8
#define F_SUBMENU_COLORS             9
#define F_SUBMENU_COLOR_NAME         10

typedef uint8_t (*SelectedFunction)(Menu*);

SelectedFunction get_selected_function(uint8_t id) {
  switch(id) {
    case F_SUBMENU_PRESET_SAVE:        return &submenu_preset_save;
    case F_SUBMENU_PRESET_NAME:        return &submenu_preset_name;
    case F_SUBMENU_PRESET_PARAMS:      return &submenu_preset_params;
    case F_SUBMENU_PRESET_PARAM_PEDAL: return &submenu_preset_param_pedal;
    case F_SUBMENU_PRESET_COPY:        return &submenu_preset_copy;
    case F_SUBMENU_PRESET_RESET:       return &submenu_preset_reset;
    case F_SUBMENU_PEDALS:             return &submenu_pedals;
    case F_SUBMENU_PEDAL_NAME:         return &submenu_pedal_name;
    case F_SUBMENU_COLORS:             return &submenu_colors;
    case F_SUBMENU_COLOR_NAME:         return &submenu_color_name;
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
            m.back();
            return true;
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
            if ( selected_function(&m_sub) ) m.jump_to(E_SUBMENU);
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNC_AND_SUB ) {
            if ( !func_or_sub ) {
              if ( selected_function(&m_sub) ) {
                if ( ( menu_option_2.value == F_SUBMENU_COLORS && m_sub.d.event == 255 ) || m_sub.d.event == 63 ) {
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