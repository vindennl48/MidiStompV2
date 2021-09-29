#include <Arduino.h>
#include "Screen.h"

LiquidCrystal_I2C Screen::lcd(SCREEN_ADDR, SCREEN_WIDTH, SCREEN_HEIGHT);
Timer             Screen::lcd_timer = 0;


void Screen::setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}
void Screen::loop() {
  // Flash the screen
  if ( lcd_timer ) {
    if ( millis()-lcd_timer >= 100 ) {
      lcd_timer = 0;
      lcd.backlight();
    }
  }
}
void Screen::print(uint8_t x, uint8_t y, String text) {
  lcd.setCursor(x, y);
  lcd.print(text);
}
void Screen::print_nline(uint8_t x, uint8_t y, String text) {
  uint8_t pad_sz = 0;

  print(x, y, text);

  if ( text.length() + x < SCREEN_WIDTH )
    pad_sz = SCREEN_WIDTH - text.length() - x;

  for (uint8_t i=0; i<pad_sz; i++) lcd.print(' ');
}
void Screen::flash() {
  lcd_timer = millis();
  lcd_timer = !lcd_timer ? 1 : lcd_timer;
  lcd.noBacklight();
}
