#ifndef HARDWARE_H
#define HARDWARE_H

struct HW {

  static Screen  screen;
  static Encoder knob;
  static LEDs    leds;
  static Buttons btns;

  static void setup() {
    //Serial.begin(9600);  // Set up serial output

    LED_BOARD_SETUP;  // LED on the arduino board

    screen.setup(LCD_ADDR, LCD_WIDTH, LCD_HEIGHT);
    knob.setup(PIN_D3, PIN_D2, PIN_D4);
    leds.setup();
    btns.setup();
  }

  static void loop() {
    screen.loop();
    knob.loop();
    leds.loop();
    btns.loop();
  }

};

Screen  HW::screen;
Encoder HW::knob;
LEDs    HW::leds;
Buttons HW::btns;

#endif
