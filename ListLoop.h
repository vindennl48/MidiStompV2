#ifndef LIST_LOOP_H
#define LIST_LOOP_H

struct PedalParamLoop {
  Menu     m;
  uint8_t  parent_id, size, x, is_fsw;
  String   title                   = "PEDAL PARAMS";
  char     pedal_name[STR_LEN_MAX] = {" "};
  char     param_name[STR_LEN_MAX] = {" "};

  PedalParamLoop(uint8_t parent_id, uint8_t is_fsw=true) {
    // If is_fsw false, then this finds preset pedal params
    this->x      = 1;
    this->parent_id = parent_id;
    this->is_fsw = is_fsw;
    this->size   = sizeof(PedalParam);
  }

  uint16_t loop() {
    if ( m.not_initialized() ) {
      //HW::screen.clear();
      HW::screen.print_with_nline(0,0, "::" + title);
      // print number
      HW::screen.print(0,1, String(x));
      HW::screen.print(1,1, ".");

      if ( pedal_param_p == nullptr ) { pedal_param_p = new PedalParam; }
      if ( is_fsw ) *pedal_param_p = DB::fsw_param_at(parent_id, x-1);
      else          *pedal_param_p = DB::preset_param_at(parent_id, x-1);

      if ( !pedal_param_p->pedal ) {
        HW::screen.print_with_nline(2,1,"EMPTY");
      }
      else {
        eReadBlock(EEP_START_PEDALS + sizeof(Pedal)*(pedal_param_p->pedal), (uint8_t*)pedal_name, STR_LEN_MAX);
        eReadBlock(EEP_START_PARAMS + sizeof(Param)*(pedal_param_p->pedal)*NUM_PEDAL_PARAMS + sizeof(Param)*(pedal_param_p->param), (uint8_t*)param_name, STR_LEN_MAX);

        HW::screen.print_with_nline(2,1,pedal_name);
        HW::screen.print(8,1," ");
        HW::screen.print(9,1,param_name);
      }
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, NUM_PARAMS_PER_FSW-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, NUM_PARAMS_PER_FSW-1);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() ) {
        m.back();
        return x;
      }
      else if ( HW::knob.is_long_pressed() ) {
        m.back();
        x = NUM_PARAMS_PER_FSW;
        CLRPTR(pedal_param_p);
        return x;
      }
    }

    return false;
  }

  uint16_t get_result() {
    return x == max ? x : (x-1);
  }
} *pedal_param_loop_p = nullptr;


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
