#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "Standard.h"
#include "Button.h"

#define NUM_BTNS  4

struct Buttons {
  Button btn1, btn2, btn3, btn4;

  Buttons() {}

  void setup() {
    btn1.setup(PIN_B0);
    btn2.setup(PIN_D7);
    btn3.setup(PIN_D6);
    btn4.setup(PIN_D5);
  }

  void loop() {
    for (int i=0; i<NUM_BTNS; i++) at(i)->loop();
  }

  Button* at(uint8_t pos) {
    switch (pos) {
      case 0:
        return &btn1;
      case 1:
        return &btn2;
      case 2:
        return &btn3;
      case 3:
        return &btn4;
      default:
        return NULL;
    }
  }
};


#endif
