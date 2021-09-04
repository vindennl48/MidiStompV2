// Uncomment to use this program
//#define LOAD_EEPROM // <----

#ifdef LOAD_EEPROM

// -- LOADING OPTIONS --
#define RESET_COLORS
#define RESET_PEDALS
#define RESET_FEATURES
#define RESET_PRESETS
#define RESET_PRESET_PARAMS
#define RESET_FSW
#define RESET_FSW_PARAMS
// --

void setup() {
  hw_setup();

  print_nline(0,0, "RESETTING..");

#ifdef RESET_COLORS
{
  PRINT_NLINE(11,0, NUM_COLORS);
  print_nline(0, 1, "> COLORS");

  for (uint8_t i=0; i<NUM_COLORS; i++) {
    if ( !(i%10) ) PRINT_NLINE(9,1, i);
    switch(i) {
      case 0:
        memcpy(text[0], "RED_OFF     ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 2);
        Color::set_green(i, 0);
        Color::set_blue( i, 0);
        break;

      case 1:
        memcpy(text[0], "RED_ON      ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 255);
        Color::set_green(i, 0);
        Color::set_blue( i, 0);
        break;

      case 2:
        memcpy(text[0], "GREEN_OFF   ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 0);
        Color::set_green(i, 2);
        Color::set_blue( i, 0);
        break;

      case 3:
        memcpy(text[0], "GREEN_ON    ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 0);
        Color::set_green(i, 255);
        Color::set_blue( i, 0);
        break;

      case 4:
        memcpy(text[0], "BLUE_OFF    ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 0);
        Color::set_green(i, 0);
        Color::set_blue( i, 2);
        break;

      case 5:
        memcpy(text[0], "BLUE_ON     ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 0);
        Color::set_green(i, 0);
        Color::set_blue( i, 255);
        break;

      default:
        memcpy(text[0], "UNTITLED    ", TEXT_SZ);
        Color::set_name( i, TXT_BUF_1);
        Color::set_red(  i, 255);
        Color::set_green(i, 0);
        Color::set_blue( i, 0);
        break;
    };
  }
}
#endif // -- END COLORS --

#ifdef RESET_PEDALS
{
  PRINT_NLINE(11,0, NUM_PEDALS);
  print_nline(0, 1, "> PEDALS");
  memcpy(text[0], "UNTITLED    ", TEXT_SZ);
  for (uint8_t i=0; i<NUM_PEDALS; i++) {
    PRINT_NLINE(9,1, i);
    Pedal::set_name(i, TXT_BUF_1);
    Pedal::set_channel(i, 0);
  }
}
#endif // -- END PEDALS --

#ifdef RESET_FEATURES
{
  PRINT_NLINE(11,0, NUM_FEATURES_TOTAL);
  print_nline(0, 1, "> FEATURES");
  memcpy(text[0], "UNTITLED    ", TEXT_SZ);
  for (uint16_t i=0; i<NUM_FEATURES_TOTAL; i++) {
    if ( !(i%10) ) PRINT_NLINE(11,1, i);
    Feature::set_name(i, TXT_BUF_1);
    Feature::set_type(i, 0);
    Feature::set_pitch(i, 0);
  }
}
#endif // -- END FEATURES --

#ifdef RESET_PRESET_PARAMS
{
  PRINT_NLINE(11,0, NUM_PRESET_PARAMS_TOTAL);
  print_nline(0, 1, "> PRST PRMS");
  for (uint16_t i=0; i<NUM_PRESET_PARAMS_TOTAL; i++) {
    if ( !(i%10) ) PRINT_NLINE(12,1, i);
    PresetParam::set_data(i, 0);
    //PresetParam::set_pedal(   i, 0);
    //PresetParam::set_feature( i, 0);
    //PresetParam::set_velocity(i, 0);
  }
}
#endif // -- END PRESET PARAMS --

#ifdef RESET_FSW_PARAMS
{
  PRINT_NLINE(11,0, NUM_FSW_PARAMS_TOTAL);
  print_nline(0, 1, "> FSW PRMS");
  for (uint16_t i=0; i<NUM_FSW_PARAMS_TOTAL; i++) {
    if ( !(i%500) ) PRINT_NLINE(11,1, i);
    FswParam::set_data(i, 0);
    //FswParam::set_pedal(   i, 0);
    //FswParam::set_feature( i, 0);
    //FswParam::set_velocity(i, 0);
  }
}
#endif // -- END PRESET PARAMS --

  lcd.clear();
  print_nline(0,0, "DONE!");
  print_nline(0,1, "END: ");
  PRINT_NLINE(5,1, M_END);

} // -- END SETUP --

void loop() {}

#endif
