#ifndef LEDS_H
#define LEDS_H

#define NUM_SHIFT_REGISTERS   2
#define SHIFT_REG_RESOLUTION  100

#define LED1_SR_PINS          3,  2,  1
#define LED2_SR_PINS          7,  6,  5
#define LED3_SR_PINS          11, 10, 9
#define LED4_SR_PINS          15, 14, 13

struct LEDs {

  LED              led1, led2, led3, led4;
  ShiftRegisterPWM shift_reg;

  LEDs()
    : led1(LED1_SR_PINS, &shift_reg),
      led2(LED2_SR_PINS, &shift_reg),
      led3(LED3_SR_PINS, &shift_reg),
      led4(LED4_SR_PINS, &shift_reg),
      shift_reg(NUM_SHIFT_REGISTERS, SHIFT_REG_RESOLUTION)
  {}

  void setup() {
    shift_reg.setup();
    set(0,0,0);
  }

  void loop() {
    for (int i=0; i<NUM_FSW; i++) at(i)->loop();
  }

  void set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time = DEFAULT_LED_TIME_MS) {
    for (int i=0; i<NUM_FSW; i++) at(i)->set(r_new, g_new, b_new, time);
  }
  void set(Color color, uint16_t time = DEFAULT_LED_TIME_MS) {
    for (int i=0; i<NUM_FSW; i++) at(i)->set(color, time);
  }

  LED* at(uint8_t pos) {
    switch (pos) {
      case 0:
        return &led1;
      case 1:
        return &led2;
      case 2:
        return &led3;
      case 3:
        return &led4;
      default:
        return NULL;
    }
  }
};

#undef NUM_SHIFT_REGISTERS
#undef SHIFT_REG_RESOLUTION

#undef LED1_SR_PINS
#undef LED2_SR_PINS
#undef LED3_SR_PINS
#undef LED4_SR_PINS

#endif
