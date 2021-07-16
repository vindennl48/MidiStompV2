#ifndef MENU_LOOP_H
#define MENU_LOOP_H


struct MenuLoop {
  Menu    m;
  uint8_t menu_id, size, x;
  char    option[STR_LEN_MAX] = {" "};

  MenuLoop() {
    this->x       = 1;
    this->menu_id = 0;
    //this->size    = DB::menu_at(0);
  }

  void reset(uint8_t menu_id) {
    this->x       = 1;
    this->menu_id = menu_id;
    this->size    = DB::menu_at(menu_id);
  }

  uint8_t loop() {
    if ( m.not_initialized() ) {
      HW::screen.clear();
      if ( x == 1 ) HW::screen.print(0,0, "::");
      else          HW::screen.print(0,0, "  ");

      DB::menu_item_at(menu_id, x-1, option);
      HW::screen.print(0,0, "::");
      HW::screen.print(2,0, option);

      DB::menu_item_at(menu_id, x, option);
      HW::screen.print(0,1, "> ");
      HW::screen.print(2,1, option);
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, size-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, size-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() ) {
        m.back();
        return x;
      }
    }

    return false;
  }
};





#endif
