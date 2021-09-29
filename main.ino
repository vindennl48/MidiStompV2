#include <Arduino.h>
#include "Standard.h"
#include "Nav.h"
#include "Hardware.h"

Nav n;

// #define PIN_OUTPUT_SETUP(X, POS)         DDR##X  |=  _BV(POS)
// #define PIN_SET_TRUE(X, POS)             PORT##X |=  _BV(POS)
// #define PIN_SET_FALSE(X, POS)            PORT##X &= ~_BV(POS)
// #define PIN_SET_TOGGLE(X, POS)           PORT##X ^=  _BV(POS)
// 
// #define LED_BOARD_SETUP          PIN_OUTPUT_SETUP(B, 5)
// #define LED_BOARD_TRUE           PIN_SET_TRUE(    B, 5)
// #define LED_BOARD_FALSE          PIN_SET_FALSE(   B, 5)
// #define LED_BOARD_TOGGLE         PIN_SET_TOGGLE(  B, 5)

void setup() {
  HW::setup();

  HW::screen.print(0,0, "HELLO");
  for (int i=0; i<4; i++) HW::leds[i].set(0, 255, 0);
}

void loop() {
  HW::loop();

  /*delay(1000);*/
  /*LED_BOARD_TOGGLE;*/

//  if ( n.not_init() ) {
//    HW::screen.print(0,0, String("HI"));
//    for (int i=0; i<4; i++) HW::leds[i].set(0, 255, 0);
//  }
//  else {
//  }
}
