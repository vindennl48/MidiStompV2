#include <Arduino.h>
#include "Standard.h"
#include "Hardware.h"

#define LED1_SR_PINS 3,  2,  1
#define LED2_SR_PINS 7,  6,  5
#define LED3_SR_PINS 11, 10, 9
#define LED4_SR_PINS 15, 14, 13

char buffer[2][TEXT_SZ] = {{' '}};

Button HW::btns[NUM_BTNS];
LED    HW::leds[NUM_LEDS];
Knob   HW::knob;
Screen HW::screen;

void HW::setup() {
  LED_BOARD_SETUP;
  SERIAL_MIDI_SETUP;

  btns[0].setup(PIN_B0);
  btns[1].setup(PIN_D7);
  btns[2].setup(PIN_D6);
  btns[3].setup(PIN_D5);

  leds[0].setup(LED1_SR_PINS);
  leds[1].setup(LED2_SR_PINS);
  leds[2].setup(LED3_SR_PINS);
  leds[3].setup(LED4_SR_PINS);

  knob.setup(PIN_D3, PIN_D2, PIN_D4);
  screen.setup();
}
void HW::loop() {
  for (int i=0; i<NUM_BTNS; i++) btns[i].loop();
  for (int i=0; i<NUM_LEDS; i++) leds[i].loop();

  knob.loop();
  screen.loop();
}

void HW::leds_set(Color c) {
  leds_set(c, DEFAULT_LED_TIME_MS);
}
void HW::leds_set(Color c, uint16_t time) {
  leds_set(c.at(0), c.at(1), c.at(2), time);
}
void HW::leds_set(uint8_t r_new, uint8_t g_new, uint8_t b_new) {
  leds_set(r_new, g_new, b_new, DEFAULT_LED_TIME_MS);
}
void HW::leds_set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time) {
  for (int i=0; i<NUM_LEDS; i++)
    leds[i].set(r_new, g_new, b_new, time);
}
