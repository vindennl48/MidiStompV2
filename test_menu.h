#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#define TYPE_DUMMY        0
#define TYPE_SUB_MENU     1
#define TYPE_FUNCTION     2
#define TYPE_FUNC_AND_SUB 3

/* MenuOption 0 is always going to be a dummy option (impossible to select) */
struct MenuOption {
  char text[STR_LEN_MAX];

  union {
    struct {
      unsigned type:2;    // 0=DUMMY, 1=SUBMENU, 2=FUNCTION, 3=FUNC THEN SUBMENU
      unsigned value:8;   // submenu or function id to call
      unsigned value2:8;  // value is function call, value2 is submenu (only in type 3)
    };
  };

  MenuOption(char text[STR_LEN_MAX], uint8_t type, uint8_t value=0, uint8_t value2=0) {
    strcpy(this->text, text);
    this->type   = type;
    this->value  = value;
    this->value2 = value2;
  }
  MenuOption() {}  // For pointers
};


struct SubMenu {
  char    title[STR_LEN_MAX];
  uint8_t num_options;
  uint8_t menu_option_id[10];

  SubMenu(char title[STR_LEN_MAX], uint8_t num_options, uint8_t menu_option_id[10]) {
    strcpy(this->title, title);
    this->num_options = num_options;
    for (int i=0; i<10; i++) { this->menu_option_id[i] = menu_option_id[i]; }
  }
  SubMenu() {}  // For pointers
};

#define E_SUBMENU   0
#define E_OPTION    1

struct MenuHost {
  /* Function to run the entire menu system */

  Menu       m;
  MenuHost   *sub_menu_host;
  SubMenu    sub_menu;
  MenuOption menu_option_1, menu_option_2;
  uint8_t    sub_menu_id = 0;
  uint8_t    x = 1;

  MenuHost(uint8_t sub_menu_id) {
    sub_menu          = DB::sub_menu_at(sub_menu_id);
    this->sub_menu_id = sub_menu_id;
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
          if ( menu_option_2.type == TYPE_SUB_MENU ) {
            sub_menu_host = new MenuHost(menu_option_2.value);
          }
          else if ( menu_option_2.type == TYPE_FUNCTION ) { }
          else if ( menu_option_2.type == TYPE_FUNC_AND_SUB) { }
        }
        else {
          if ( menu_option_2.type == TYPE_SUB_MENU ) {
            if ( sub_menu_host->loop() ) {
              delete sub_menu_host;
              m.jump_to(E_SUBMENU);
            }
          }
          else if ( menu_option_2.type == TYPE_FUNCTION ) {
            m.jump_to(E_SUBMENU);
          }
          else if ( menu_option_2.type == TYPE_FUNC_AND_SUB ) {
            m.jump_to(E_SUBMENU);
          }
        }
        break;
    };

    return false;
  }

};

#undef TYPE_DUMMY
#undef TYPE_SUB_MENU
#undef TYPE_FUNCTION

#undef E_SUBMENU
#undef E_OPTION

#ifdef EEP_RESET
#ifdef EEP_RESET_MENUS
#define NUM_MENU_OPTIONS 10

SubMenu    sub_menu;
MenuOption menu_option[NUM_MENU_OPTIONS];
uint8_t    menu_id     = 0;
uint8_t    num_options = NUM_MENU_OPTIONS;

menu_id     = 0;
num_options = 7;
sub_menu SubMenu("PRESET", num_options);
menu_option[0] = MenuOption("",       TYPE_DUMMY);
menu_option[1] = MenuOption("SAVE",   TYPE_DUMMY);
menu_option[2] = MenuOption("NAME",   TYPE_DUMMY);
menu_option[3] = MenuOption("PARAMS", TYPE_FUNC_AND_SUB, /*FUNC ID*/ 0, /*SUBMENU ID*/ 2);
menu_option[4] = MenuOption("COPY",   TYPE_DUMMY);
menu_option[5] = MenuOption("RESET",  TYPE_DUMMY);
menu_option[6] = MenuOption("GLOBAL", TYPE_SUB_MENU, 1);
DB::sub_menu_save(menu_id, &sub_menu);
for (int i=0; i<num_options; i++) DB::menu_option_save((NUM_MENU_OPTIONS * menu_id) + i, &menu_option[i]);

menu_id     = 1;
num_options = 4;
sub_menu SubMenu("GLOBAL", num_options);
menu_option[0] = MenuOption("",       TYPE_DUMMY);
menu_option[1] = MenuOption("PEDALS", TYPE_DUMMY);
menu_option[2] = MenuOption("COLORS", TYPE_DUMMY);
menu_option[3] = MenuOption("RESET",  TYPE_DUMMY);
DB::sub_menu_save(menu_id, &sub_menu);
for (int i=0; i<num_options; i++) DB::menu_option_save((NUM_MENU_OPTIONS * menu_id) + i, &menu_option[i]);

menu_id     = 2;
num_options = 4;
sub_menu SubMenu("PARAM", num_options);
menu_option[0] = MenuOption("",       TYPE_DUMMY);
menu_option[1] = MenuOption("CHANGE", TYPE_DUMMY);
menu_option[2] = MenuOption("VALUE",  TYPE_DUMMY);
menu_option[3] = MenuOption("RESET",  TYPE_DUMMY);
DB::sub_menu_save(menu_id, &sub_menu);
for (int i=0; i<num_options; i++) DB::menu_option_save((NUM_MENU_OPTIONS * menu_id) + i, &menu_option[i]);

#endif
#endif

#endif
