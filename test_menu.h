#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#define E_SUBMENU   0
#define E_OPTION    1

typedef uint8_t (*SelectedFunction)(Menu*);

SelectedFunction get_selected_function(uint8_t id) {
  switch(id) {
    case 1: return &submenu_preset_save;
    case 2: return &submenu_preset_name;
    case 3: return &submenu_preset_params;
    case 4: return &submenu_preset_copy;
    case 5: return &submenu_preset_reset;
  };

  return nullptr;
}

struct MenuHost {
  /* Function to run the entire menu system */

  Menu             m, m_sub;
  MenuHost         *sub_menu_host;
  SubMenu          sub_menu;
  MenuOption       menu_option_1, menu_option_2;
  SelectedFunction selected_function;
  uint8_t          sub_menu_id    = 0;
  uint8_t          x              = 1;

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
            m.jump_to(E_OPTION);
          }
          else if ( HW::knob.is_long_pressed() ) {
            m.back();
            return true;
          }
        }
        break;

      case E_OPTION:
        if ( m.not_initialized() ) {
          if ( menu_option_2.type == MENU_TYPE_SUB_MENU ) {
            sub_menu_host = new MenuHost;
            sub_menu_host->setup(menu_option_2.value);
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNCTION ) {
            selected_function = get_selected_function(menu_option_2.value);
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNC_AND_SUB) { }
        }
        else {
          if ( menu_option_2.type == MENU_TYPE_SUB_MENU ) {
            if ( sub_menu_host->loop() ) {
              delete sub_menu_host;
              m.jump_to(E_SUBMENU);
            }
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNCTION ) {
            if ( selected_function(&m_sub) ) m.jump_to(E_SUBMENU);
          }
          else if ( menu_option_2.type == MENU_TYPE_FUNC_AND_SUB ) {
            m.jump_to(E_SUBMENU);
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
