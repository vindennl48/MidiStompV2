#ifndef MENU_SELECT_H
#define MENU_SELECT_H

// Default call-back functions
uint8_t MenuDummy() { return true; }
uint8_t MenuBack()  { return 2; }


// Typedef of call-back function
typedef uint8_t (*f_menuResult)();


/* ::ACTUAL MENU:: */
struct MenuSelect {
  Menu    m;
  uint8_t i = 0, ans = 0;

  uint8_t loop(String str_ar[], f_menuResult f_ar[], uint8_t size) {
    if ( m.is_active() ) {
      ans = f_ar[i]();
      if      ( ans > 1 ) { i=0; return m.back(); }
      else if ( ans > 0 ) { m.back(); }
    }
    else if ( m.not_initialized() ) {
      if (!i) HW::screen.print_with_nline(0,0,str_ar[i]);
      else    HW::screen.print_with_nline(0,0,"  " + str_ar[i]);
      if ( i+1 < size ) HW::screen.print_with_nline(0,1," >" + str_ar[i+1]);
    }
    else if ( HW::knob.is_left() )  {
      if ( i > 0 ) {
        i -= 1;
        m.reinitialize();
      }
    }
    else if ( HW::knob.is_right() ) {
      i += 1;
      if ( i >= size-1 ) i = size-2;
      else m.reinitialize(); 
    }
    else if ( HW::knob.is_pressed() ) {
      m.activate();
    }

    return false;
  }
};
/* ::END ACTUAL MENU:: */

#endif
