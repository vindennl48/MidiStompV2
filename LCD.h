// PUBLIC DEF
#define LCD_ADDR   0x27
#define LCD_WIDTH  16
#define LCD_HEIGHT 2
// --

// LCD Screen
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_WIDTH, LCD_HEIGHT);
Timer             lcd_timer = 0;

void lcd_setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void lcd_loop() {
  // Flash the screen
  if ( lcd_timer ) {
    if ( millis()-lcd_timer >= 100 ) {
      lcd_timer = 0;
      lcd.backlight();
    }
  }
}

void print(uint8_t x, uint8_t y, String text) {
  lcd.setCursor(x, y);
  lcd.print(text);
}
#define PRINT(x, y, t) print(x, y, String(t))

void print_nline(uint8_t x, uint8_t y, String text) {
  uint8_t pad_sz = 0;

  print(x, y, text);

  if ( text.length() + x < LCD_WIDTH )
    pad_sz = LCD_WIDTH - text.length() - x;

  for (uint8_t i=0; i<pad_sz; i++)
    lcd.print(' ');
}
#define PRINT_NLINE(x, y, t) print_nline(x, y, String(t))

void flash() {
  lcd_timer = millis();
  lcd_timer = !lcd_timer ? 1 : lcd_timer;
  lcd.noBacklight();
}
