#ifndef MENU_SELECT_H
#define MENU_SELECT_H

#include "Hardware.h"
#include "Menu.h"

#define LEN(x) *(&x+1)-x  // get length of array

uint8_t MenuDummy() { return true; }
uint8_t MenuBack()  { return 2; }

typedef uint8_t (*FuncMenuResult)();
struct MenuInput {
  String option;
  FuncMenuResult funcMenuResult;

  //MenuInput(String new_option, FuncMenuResult new_funcMenuResult) {
    //option         = new_option;
    //funcMenuResult = new_funcMenuResult;
  //}
};

template <typename T, size_t size>
struct MenuSelect {
  Menu    m;
  uint8_t i = 0;
  T       (*array)[size];

  MenuSelect(T (*new_array)[size]) {
    array = new_array;
  }

  uint8_t loop() {
    if ( m.is_active() ) {
      if      ( (*array)[i+1].funcMenuResult() > 1 ) { return m.back(); }
      else if ( (*array)[i+1].funcMenuResult() > 0 ) { m.back(); }
    }
    else if ( m.not_initialized() ) {
      HW::screen.clear();
      if (!i) HW::screen.print(0,0,(*array)[i].option);
      else    HW::screen.print(0,0,"  " + (*array)[i].option);
      if ( i+1 < (uint8_t)size ) HW::screen.print(0,1," >" + (*array)[i+1].option);
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
      else               m.reinitialize(); 
    }
    else if ( HW::knob.is_pressed() ) {
      m.activate();
    }

    return false;
  }

};


//template <typename T, size_t size>
//struct MenuSelect {
//  Menu    m;
//  uint8_t i = 0;
//  T       (*array)[size];
//
//  MenuSelect(T (*new_array)[size]) {
//    array = new_array;
//  }
//
//  bool loop() {
//    if ( m.not_initialized() ) {
//      HW::screen.clear();
//      if (!i) HW::screen.print(0,0,(*array)[i]);
//      else    HW::screen.print(0,0,"  " + (*array)[i]);
//      if ( i+1 < (uint8_t)size ) HW::screen.print(0,1," >" + (*array)[i+1]);
//    }
//    else if ( HW::knob.is_left() )  {
//      if ( i > 0 ) {
//        i -= 1;
//        m.reinitialize();
//      }
//    }
//    else if ( HW::knob.is_right() ) {
//      i += 1;
//      if ( i >= size-1 ) i = size-2;
//      else               m.reinitialize(); 
//    }
//    else if ( HW::knob.is_pressed() ) {
//      uint8_t result = i+1; i = 0;
//      m.back(); return result;
//    }
//
//    return false;
//  }
//
//};


struct MenuListChoose {
  Menu    m;
  uint8_t i = 0;

  template <typename T, size_t size>
  bool loop(const T (&array)[size]) {
    if ( m.not_initialized() ) {
      HW::screen.clear();
      if (!i) HW::screen.print(0,0,array[i]);
      else    HW::screen.print(0,0,"  " + array[i]);
      if ( i+1 < (uint8_t)size ) HW::screen.print(0,1," >" + array[i+1]);
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
      else               m.reinitialize(); 
    }
    else if ( HW::knob.is_pressed() ) {
      uint8_t result = i+1;
      i = 0;
      return result;
    }

    return false;
  }

} menu_list_choose;


#endif
