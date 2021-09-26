// PUBLIC DEFINES

// Buttons
#define NUM_BTNS 4

// LEDs
#define NUM_LEDS             NUM_BTNS
#define NUM_SHIFT_REGISTERS  2
#define SHIFT_REG_RESOLUTION 100

// PRIVATE DEFINES

// LEDs
#define LED1_SR_PINS 3,  2,  1
#define LED2_SR_PINS 7,  6,  5
#define LED3_SR_PINS 11, 10, 9
#define LED4_SR_PINS 15, 14, 13
// --

// buttons on foot-pedal
Button btns[NUM_BTNS];

// Knob Encoder
Knob knob;

// LEDs
ShiftRegisterPWM shift_reg(NUM_SHIFT_REGISTERS, SHIFT_REG_RESOLUTION);
LED              leds[NUM_LEDS];
void leds_set(uint8_t r_new, uint8_t g_new, uint8_t b_new, uint16_t time=DEFAULT_LED_TIME_MS) {
  for (uint8_t i=0; i<NUM_LEDS; i++) leds[i].set(r_new, g_new, b_new, time);
}
void leds_set_red(uint8_t new_value)   { for (uint8_t i=0; i<NUM_LEDS; i++) leds[i].r.set(new_value); }
void leds_set_green(uint8_t new_value) { for (uint8_t i=0; i<NUM_LEDS; i++) leds[i].g.set(new_value); }
void leds_set_blue(uint8_t new_value)  { for (uint8_t i=0; i<NUM_LEDS; i++) leds[i].b.set(new_value); }

void hw_setup() {
  //SERIAL_MIDI_SETUP;

  // Board LED
  LED_BOARD_SETUP;

  // Buttons
  btns[0].setup(PIN_B0);
  btns[1].setup(PIN_D7);
  btns[2].setup(PIN_D6);
  btns[3].setup(PIN_D5);

  // LEDs
  shift_reg.setup();
  leds[0].setup(LED1_SR_PINS, &shift_reg);
  leds[1].setup(LED2_SR_PINS, &shift_reg);
  leds[2].setup(LED3_SR_PINS, &shift_reg);
  leds[3].setup(LED4_SR_PINS, &shift_reg);

  // Knob
  knob.setup(PIN_D3, PIN_D2, PIN_D4);

  // LCD Screen
  lcd_setup();
}

void hw_loop() {
  // Buttons & LEDs
  for (uint8_t i=0; i<NUM_BTNS; i++) { btns[i].loop(); leds[i].loop(); }

  // Knob
  knob.loop();

  lcd_loop();
}

// PRIVATE UNDEF
#undef LED1_SR_PINS
#undef LED2_SR_PINS
#undef LED3_SR_PINS
#undef LED4_SR_PINS
// --
