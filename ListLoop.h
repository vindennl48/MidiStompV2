#ifndef LIST_LOOP_H
#define LIST_LOOP_H

struct ListLoop {
  Menu     m;
  uint8_t  address, size, x;
  String   title               = "UNTITLED";
  char     option[STR_LEN_MAX] = {" "};
  uint16_t max                 = 99;
  uint8_t  is_color            = 0;

  ListLoop(uint16_t address, uint8_t size, String title, uint16_t max, uint8_t is_color=0) {
    this->x        = 1;
    this->address  = address;
    this->size     = size;
    this->title    = title;
    this->max      = max;
    this->is_color = is_color;
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
        return x;
      }
      else if ( HW::knob.is_long_pressed() ) {
        m.back();
        x = max;
        return x;
      }
    }

    return false;
  }

  uint16_t get_result() {
    return x == max ? x : (x-1);
  }
} *list_loop_p = nullptr;


#endif
