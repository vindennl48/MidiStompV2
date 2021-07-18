#ifndef MENU_LOOP_H
#define MENU_LOOP_H


struct MenuLoop {
  Menu    m;
  uint8_t menu_id             = 0;
  uint8_t x                   = 0;
  char    option[STR_LEN_MAX] = " ";
  String  title               = "";

  void reset(uint8_t menu_id, String title = "") {
    this->x       = 1;
    this->menu_id = menu_id;
    this->title   = title;
    m.back();     // reset
  }

  uint8_t loop() {
    if ( m.not_initialized() ) {
      if ( x == 1 ) HW::screen.print(0,0, "::");
      else          HW::screen.print(0,0, "  ");

      if ( title != "" && x == 1 ) {
        HW::screen.print_with_nline(2,0, title);
      }
      else {
        DB::menu_item_at(menu_id, x-1, option);
        HW::screen.print_with_nline(2,0, option);
      }

      DB::menu_item_at(menu_id, x, option);
      HW::screen.print(0,1, "> ");
      HW::screen.print_with_nline(2,1, option);
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, DB::menu_at(menu_id)-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, DB::menu_at(menu_id)-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() ) {
        m.back();
        return x;
      }
      else if ( HW::knob.is_long_pressed() ) {
        m.back();
        return NUM_MENU_ITEMS;
      }
    }

    return false;
  }
};

struct ListLoop {
  Menu     m;
  uint8_t  address, size, x;
  String   title               = "UNTITLED";
  char     option[STR_LEN_MAX] = {" "};
  uint16_t max                 = 99;
  uint8_t  is_color            = 0;

  ListLoop() {
    this->x       = 1;
    this->address = 0;
    this->size    = STR_LEN_MAX;
  }

  void reset(uint16_t address, uint8_t size, String title, uint16_t max, uint8_t is_color=0) {
    this->x        = 1;
    this->address  = address;
    this->size     = size;
    this->title    = title;
    this->max      = max;
    this->is_color = is_color;
    m.back();
  }

  uint16_t loop() {
    if ( m.not_initialized() ) {
      //HW::screen.clear();
      HW::screen.print_with_nline(0,0, "::" + title);

      eReadBlock(address + size * (x-1), (uint8_t*)option, STR_LEN_MAX);
      // print number
      HW::screen.print(0,1, "   ");
      HW::screen.print(0,1, String(x));

      // print option
      HW::screen.print(3,1, ">");
      HW::screen.print_with_nline(4,1, option);

      if ( is_color ) {
        for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set( DB::color_at(x-1) );
      }
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, max-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, max-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() ) {
        m.back();
        for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
        return x;
      }
      else if ( HW::knob.is_long_pressed() ) {
        m.back();
        for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
        return max;
      }
    }

    return false;
  }
};



#endif
