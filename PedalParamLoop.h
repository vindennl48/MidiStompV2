#ifndef PEDAL_PARAM_LOOP_H
#define PEDAL_PARAM_LOOP_H

struct PedalParamLoop {
  Menu     m;
  uint8_t  parent_id, size, x, is_fsw;
  String   title                   = "PARAMS";
  char     pedal_name[STR_LEN_MAX] = {" "};
  char     param_name[STR_LEN_MAX] = {" "};

  PedalParamLoop(uint8_t parent_id, uint8_t is_fsw=true, uint8_t start_point=0) {
    // If is_fsw false, then this finds preset pedal params
    this->x         = start_point>=NUM_PEDAL_PARAMS ? 1 : start_point+1;
    this->parent_id = parent_id;
    this->is_fsw    = is_fsw;
    this->size      = sizeof(PedalParam);
  }

  uint16_t loop() {
    if ( m.not_initialized() ) {
      //HW::screen.clear();
      HW::screen.print_with_nline(0,0, "::" + title);
      HW::screen.print(0,1, "  ");
      // print number
      if ( x < 10 ) HW::screen.print(1,1, String(x));
      else          HW::screen.print(0,1, String(x));
      HW::screen.print(2,1, ".");

      if ( pedal_param_p == nullptr ) { pedal_param_p = new PedalParam; }
      if ( is_fsw ) {
        *pedal_param_p = DB::fsw_param_at(parent_id, x-1);
        sel_fsw_id     = x-1;
      }
      else {
        *pedal_param_p = DB::preset_param_at(parent_id, x-1);
        sel_param_id   = x-1;
      }

      if ( pedal_param_p->pedal == EEP_NUM_PEDALS ) {
        HW::screen.print_with_nline(3,1,"EMPTY");
      }
      else {
        eReadBlock(EEP_START_PEDALS + sizeof(Pedal)*(pedal_param_p->pedal), (uint8_t*)pedal_name, STR_LEN_MAX);
        eReadBlock(EEP_START_PARAMS + sizeof(Param)*(pedal_param_p->pedal)*NUM_PEDAL_PARAMS + sizeof(Param)*(pedal_param_p->param), (uint8_t*)param_name, STR_LEN_MAX);

        HW::screen.print_with_nline(3,1,pedal_name);
        HW::screen.print(9,1," ");
        HW::screen.print(10,1,param_name);
      }
    }
    else {
      if ( HW::knob.is_left() ) {
        x = CONTAIN(x-1, 1, NUM_PARAMS_PER_FSW);
        m.reinitialize();
      }
      else if ( HW::knob.is_right() ) {
        x = CONTAIN(x+1, 1, NUM_PARAMS_PER_FSW);
        m.reinitialize();
      }
      else if ( HW::knob.is_pressed() || HW::knob.is_long_pressed() ) {
        if ( HW::knob.is_long_pressed() ) { x = (NUM_PARAMS_PER_FSW+1); }
        m.back();
        CLRPTR(pedal_param_p);
        return x;
      }
    }

    return false;
  }

  uint16_t get_result() {
    return x == (NUM_PARAMS_PER_FSW+1) ? x : (x-1);
  }
} *pedal_param_loop_p = nullptr;


#endif
