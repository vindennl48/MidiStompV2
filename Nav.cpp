#include "Nav.h"

Nav::Nav() : data(0) {}

uint8_t Nav::not_init() {
  uint8_t result = d_init;
  d_init           = true;
  return !result; 
}
void    Nav::reinit()           { d_init = false; }
uint8_t Nav::is_active()        { return d_active; }
void    Nav::activate()         { d_init = false; d_active = true; }
void    Nav::jump_to(uint8_t e) { data = 0; d_event = e; }
uint8_t Nav::back()             { data = 0; return true; }
uint8_t Nav::reset()            { return back(); }
uint8_t Nav::e()                { return d_event; }
