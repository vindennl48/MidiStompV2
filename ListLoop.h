#ifndef LIST_LOOP_H
#define LIST_LOOP_H

struct ListLoop {
  Menu     m;
  uint16_t address;
  uint8_t  size, x;
  String   title               = "UNTITLED";
  char     option[STR_LEN_MAX] = {" "};
  uint16_t max                 = 99;
  uint8_t  is_color            = 0;

  ListLoop(uint16_t address, uint8_t size, String title, uint16_t max, uint8_t is_color=false, uint8_t start_point=0) {
    this->x        = start_point+1;
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

      if ( address == EEP_START_PEDALS ) {
        if ( pedal_p == nullptr ) pedal_p = new Pedal();
        *pedal_p = DB::pedal_at(x-1);
        memcpy(option, pedal_p->name, STR_LEN_MAX);
      }
      else if ( address == EEP_START_COLORS ) {
        if ( color_p == nullptr ) color_p = new Color();
        *color_p = DB::color_at(x-1);
        memcpy(option, color_p->name, STR_LEN_MAX);
      }
      else {
        eReadBlock(address + size * (x-1), (uint8_t*)option, STR_LEN_MAX);
      }

      // print number
      HW::screen.print(0,1, "   ");
      if      ( x < 10 )  HW::screen.print(2,1, String(x));
      else if ( x < 100 ) HW::screen.print(1,1, String(x));
      else                HW::screen.print(0,1, String(x));

      // print option
      HW::screen.print(3,1, ".");
      HW::screen.print_with_nline(4,1, option);

      if ( is_color ) { HW::leds.set( DB::color_at(x-1) ); }
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, max);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, max);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() || HW::knob.is_long_pressed() ) {
        if ( HW::knob.is_long_pressed() ) { x = max+1; }
        else {  // REGULAR PRESS
          if      ( address == EEP_START_PEDALS ) sel_pedal_id = x-1;
          else if ( address == EEP_START_COLORS ) sel_color_id = x-1;
        }
        if ( is_color ) { HW::leds.set(0,0,0); }
        m.back();
        CLRPTR(pedal_p);
        CLRPTR(color_p);
        return x;
      }
    }

    return false;
  }

  uint16_t get_result() {
    return x == (max+1) ? max : (x-1);
  }
} *list_loop_p = nullptr;


#endif
