#ifndef NAV_H
#define NAV_H

#include <Arduino.h>

struct Nav {
  union {
    uint16_t data;
    struct {
      unsigned d_event:8;
      unsigned d_init:1;
      unsigned d_active:1;
    };
  };

  Nav();

  uint8_t not_init();
  void    reinit();
  uint8_t is_active();
  void    activate();
  void    jump_to(uint8_t);
  uint8_t back();
  uint8_t reset();
  uint8_t e();
};

#endif
