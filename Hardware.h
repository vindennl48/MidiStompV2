// PUBLIC DEFINES
#define NUM_BTNS 4
// PRIVATE DEFINES
// --

// buttons on foot-pedal
Button btns[NUM_BTNS];

void hw_setup() {
  // Board LED
  LED_BOARD_SETUP;

  // Buttons
  btns[0].setup(PIN_B0);
  btns[1].setup(PIN_D7);
  btns[2].setup(PIN_D6);
  btns[3].setup(PIN_D5);

  // Knob
}

void hw_loop() {
  // Buttons
  for (uint8_t i=0; i<NUM_BTNS; i++) btns[i].loop();
}
