#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "ShiftRegisterPWM.h"
#include "Database.h"
#include "Standard.h"
#include "Channel.h"

#define IS_DIM    0
#define IS_BRIGHT 1

struct LED {

  bool    status = IS_DIM;
  Channel r, g, b;

  LED(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b, ShiftRegisterPWM *shift_reg)
   : r(pin_r, shift_reg), g(pin_g, shift_reg), b(pin_b, shift_reg)
  {}

  void loop() {
    for (int i=0; i<3; i++) at(i)->loop();
  }

  void set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time = DEFAULT_LED_TIME_MS) {
    r.set(r_new, time);
    g.set(g_new, time);
    b.set(b_new, time);
  }

  void set(Color color, uint16_t time = DEFAULT_LED_TIME_MS) {
    r.set(color.r, time);
    g.set(color.g, time);
    b.set(color.b, time);
  }

  void dim()    {
    for (int i=0; i<3; i++) at(i)->dim();
    status = IS_DIM;
  }
  void bright() {
    for (int i=0; i<3; i++) at(i)->bright();
    status = IS_BRIGHT;
  }
  void toggle() {
    if ( status == IS_DIM ) bright();
    else                    dim();
  }

  void set_dim(uint8_t color[3]) { set_dim(color[0], color[1], color[2]); }
  void set_dim(uint8_t new_r, uint8_t new_g, uint8_t new_b) {;
    r.set_dim(new_r);
    g.set_dim(new_g);
    b.set_dim(new_b);
  }

  void set_bright(uint8_t color[3]) { set_bright(color[0], color[1], color[2]); }
  void set_bright(uint8_t new_r, uint8_t new_g, uint8_t new_b) {
    r.set_bright(new_r);
    g.set_bright(new_g);
    b.set_bright(new_b);
  }

  Channel* at(uint8_t pos) {
    switch (pos) {
      case 0:
        return &r;
      case 1:
        return &g;
      case 2:
        return &b;
      default:
        return NULL;
    }
  }
};

#undef IS_DIM
#undef IS_BRIGHT

#endif
