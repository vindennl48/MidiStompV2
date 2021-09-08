// PRIVATE
#define E_MAIN                0
#define E_EDIT_VALUE          1
#define E_EDIT_PEDAL_CHANNEL  2
#define E_EDIT_FEATURE_PITCH  3
#define E_EDIT_PARAM_VELOCITY 4
// --

struct ValueEdit {
  Nav      n;
  uint16_t value     = 0;
  uint8_t  edit_type = 0;
  uint8_t  cursor    = 0;

  void setup() {
    PRINT_NLINE(0,0, F("VALUE: "));
    PRINT_NLINE(0,1, F("SAVE      CANCEL"));

    cursor = 0;

    lcd.cursor();  // Highlight

    uint16_t active_parent_addr = GET_ACTIVE_PARENT_NOT_OPTION;
    if ( IS_IN_PARTITION_PEDALS(active_parent_addr) ) {
      edit_type = E_EDIT_PEDAL_CHANNEL;
    }
    else if ( IS_IN_PARTITION_FEATURES(active_parent_addr) ) {
      edit_type = E_EDIT_FEATURE_PITCH;
    }
    else if ( IS_IN_PARTITION_PRESET_PARAMS(active_parent_addr) ) {
      edit_type = E_EDIT_PARAM_VELOCITY;
    }
    else {
      edit_type = 0;
    }

    reset_value();
  }

  uint8_t loop() {
    if ( edit_type == 0 ) { return true; }  // exit if no edit_type exists

    switch( n.e() ) {
      case E_MAIN:
        if ( n.not_init() ) {
          print_value();

          if      ( cursor == 0 ) lcd.setCursor(15, 0);
          else if ( cursor == 1 ) lcd.setCursor(0,  1);
          else if ( cursor == 2 ) lcd.setCursor(10, 1);

          lcd.blink();
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if      ( knob.is_left() )  { cursor = CONTAIN((int)cursor-1, (int)0, (int)3); }
            else if ( knob.is_right() ) { cursor = CONTAIN((int)cursor+1, (int)0, (int)3); }
            n.reinit();
          }
          else if ( knob.is_pressed() ) {
            switch(cursor) {
              case 0:  // EDIT
                n.jump_to(E_EDIT_VALUE);
                //if      ( edit_type == E_EDIT_PEDAL_CHANNEL )  n.jump_to(E_EDIT_PEDAL_CHANNEL);
                //else if ( edit_type == E_EDIT_FEATURE_PITCH )  n.jump_to(E_EDIT_FEATURE_PITCH);
                //else if ( edit_type == E_EDIT_PARAM_VELOCITY ) n.jump_to(E_EDIT_PARAM_VELOCITY);
                lcd.noBlink();
                break;
              case 1:  // SAVE
                lcd.noCursor();  // Highlight
                lcd.noBlink();
                n.back();
                save();
                return true;
              case 2:  // CANCEL
                lcd.noCursor();  // Highlight
                lcd.noBlink();
                n.back();
                return true;
            };
          }
          else if ( knob.is_long_pressed() ) {  // CANCEL
            lcd.noCursor();  // Highlight
            lcd.noBlink();
            n.back();
            return true;
          }
        }
        break;

      case E_EDIT_VALUE:
        uint16_t min, max;

        switch(edit_type) {
          case E_EDIT_PEDAL_CHANNEL:
            min = 0;
            max = 16;
            break;
          case E_EDIT_FEATURE_PITCH:
            min = 0;
            max = 128;
            break;
          case E_EDIT_PARAM_VELOCITY:
            min = 0;
            max = 128;
            break;
        };

        if ( n.not_init() ) {
          print_value();
        }
        else {
          if ( knob.is_left() || knob.is_right() ) {
            if      ( knob.is_left() )  { value = CONTAIN((int)value-1, (int)min, (int)max); }
            else if ( knob.is_right() ) { value = CONTAIN((int)value+1, (int)min, (int)max); }
            n.reinit();
          }
          else if ( knob.is_pressed() ){
            n.jump_to(E_MAIN);
          }
          else if ( knob.is_long_pressed() ){
            reset_value();
            n.jump_to(E_MAIN);
          }
        }
        break;
    };

    return false;
  }

  void reset_value() {
    // Pull the value from the current parent address
    switch(edit_type) {
      case E_EDIT_PEDAL_CHANNEL:
        value = Pedal::get_channel( GET_ACTIVE_PARENT_NOT_OPTION );
        break;
      case E_EDIT_FEATURE_PITCH:
        value = Feature::get_pitch( GET_ACTIVE_PARENT_NOT_OPTION );
        break;
      case E_EDIT_PARAM_VELOCITY:
        value = Parameter::get_velocity( GET_ACTIVE_PARENT_NOT_OPTION );
        break;
    };
  }

  void save() {
    // Here we will figure out what struct the var comes from and save there
    switch(edit_type) {
      case E_EDIT_PEDAL_CHANNEL:
        Pedal::set_channel( GET_ACTIVE_PARENT_NOT_OPTION, value );
        break;
      case E_EDIT_FEATURE_PITCH:
        Feature::set_pitch( GET_ACTIVE_PARENT_NOT_OPTION, value );
        break;
      case E_EDIT_PARAM_VELOCITY:
        Parameter::set_velocity( GET_ACTIVE_PARENT_NOT_OPTION, value );
        break;
    };
  }

  void print_value() {
    PRINT(13,0, "   ");  // Clear out number to reprint
    if      ( value <  10  ) PRINT(15,0, value);
    else if ( value <  100 ) PRINT(14,0, value);
    else                     PRINT(13,0, value);
  }

} value_edit;

#undef E_MAIN
#undef E_EDIT_VALUE
#undef E_EDIT_PEDAL_CHANNEL
#undef E_EDIT_FEATURE_PITCH
#undef E_EDIT_PARAM_VELOCITY
