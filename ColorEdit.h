#ifndef COLOR_EDIT_H
#define COLOR_EDIT_H

#define MAX_CURSOR_LOCS 4
#define RED_POS         0,0
#define GREEN_POS       6,0
#define BLUE_POS        13,0
#define SAVE_POS        0,1
#define CANCEL_POS      10,1

#define E_SELECT_CHANNEL 0
#define E_EDIT_CHANNEL   1

struct ColorEdit {
  static Menu    m;
  static Color   color;
  static uint8_t cursor, color_id, value_old, *value;

  static void setup( uint8_t id ) {
    color_id = id;
    color    = DB::color_at( id );
    cursor   = 0;

    HW::screen.clear();
    HW::screen.print(0,1, "SAVE      CANCEL");
    HW::screen.highlight(true);

    for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(color);
  }

  static bool loop() {
    switch ( m.e() ) {
      default:
      case E_SELECT_CHANNEL:
        if ( m.not_initialized() ) {
          HW::screen.print_with_nline(RED_POS,   String(color.r));
          HW::screen.print           (GREEN_POS, String(color.g));
          HW::screen.print           (BLUE_POS,  String(color.b));
          if ( cursor == 0 ) HW::screen.set_cursor(RED_POS);
          if ( cursor == 1 ) HW::screen.set_cursor(GREEN_POS);
          if ( cursor == 2 ) HW::screen.set_cursor(BLUE_POS);
          HW::screen.blink(true);
          for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(color);
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  cursor = CONTAIN(cursor-1, 0, MAX_CURSOR_LOCS);
            else if ( HW::knob.is_right() ) cursor = CONTAIN(cursor+1, 0, MAX_CURSOR_LOCS);

            if      ( cursor == 0 )                 HW::screen.set_cursor(RED_POS);
            if      ( cursor == 1 )                 HW::screen.set_cursor(GREEN_POS);
            if      ( cursor == 2 )                 HW::screen.set_cursor(BLUE_POS);
            else if ( cursor == MAX_CURSOR_LOCS-1 ) HW::screen.set_cursor(SAVE_POS);
            else if ( cursor == MAX_CURSOR_LOCS )   HW::screen.set_cursor(CANCEL_POS);
          }
          else if ( HW::knob.is_pressed() ) {
            if ( cursor < MAX_CURSOR_LOCS-1 ) {
              m.jump_to( E_EDIT_CHANNEL );
            }
            else if ( cursor == MAX_CURSOR_LOCS-1 ) { // SAVE
              HW::screen.highlight(false);
              HW::screen.blink(false);
              DB::color_save(color_id, color);

              for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
              return m.back();
            }
            else {  // CANCEL
              for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(0,0,0);
              return m.back();
            }
          }
        }
        break;

      case E_EDIT_CHANNEL:
        if ( m.not_initialized() ) {
          HW::screen.blink(false);
          switch(cursor) {
            case 0:
              value = &color.r;
              break;
            case 1:
              value = &color.g;
              break;
            case 2:
              value = &color.b;
              break;
          };
          value_old = *value;
        }
        else {
          if ( HW::knob.is_left() || HW::knob.is_right() ) {
            if      ( HW::knob.is_left() )  {
              if ( *value == 0 ) { *value = 255; }
              else               { *value = ROTATE(*value-1, 0, 256); }
            }
            else if ( HW::knob.is_right() ) *value = ROTATE(*value+20, 0, 256);
            for (int i=0; i<NUM_FSW; i++) HW::leds.at(i)->set(color);
            switch(cursor) {
              case 0:
                HW::screen.print(RED_POS, "   ");
                HW::screen.print(RED_POS, *value);
                break;
              case 1:
                HW::screen.print(GREEN_POS, "   ");
                HW::screen.print(GREEN_POS, *value);
                break;
              case 2:
                HW::screen.print(BLUE_POS, "   ");
                HW::screen.print(BLUE_POS, *value);
                break;
            };
          }
          else if ( HW::knob.is_pressed() ) {
            m.jump_to( E_SELECT_CHANNEL );
          }
          else if ( HW::knob.is_long_pressed() ) {
            *value = value_old;
            m.jump_to( E_SELECT_CHANNEL );
          }
        }
        break;
    };

    return false;
  }

};

Menu    ColorEdit::m;
Color   ColorEdit::color;
uint8_t ColorEdit::cursor    = 0;
uint8_t ColorEdit::color_id  = 0;
uint8_t ColorEdit::value_old = 0;
uint8_t *ColorEdit::value;

#endif
