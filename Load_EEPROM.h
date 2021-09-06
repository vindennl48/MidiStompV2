// Uncomment to use this program
//#define LOAD_EEPROM // <----

#ifdef LOAD_EEPROM

// -- LOADING OPTIONS --
//#define RESET_COLORS
//#define RESET_PEDALS
//#define RESET_FEATURES
//#define RESET_PRESETS
#define RESET_PRESET_PARAMS
//#define RESET_FSW
//#define RESET_FSW_PARAMS
//#define RESET_MENUS
// --

void setup() {
  hw_setup();

  print_nline(0,0, "RESETTING..");

#ifdef RESET_COLORS
{
  PRINT_NLINE(11,0, NUM_COLORS);
  print_nline(0, 1, "> COLORS");

  for (uint16_t i=M_COLORS, j=0; j<NUM_COLORS; i+=sizeof(Color), j++) {
    if ( !(j%10) ) PRINT_NLINE(9,1, j);
    switch(j) {
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
  for (uint16_t i=M_PEDALS, j=0; j<NUM_PEDALS; i+=sizeof(Pedal), j++) {
    PRINT_NLINE(9,1, j);
    Pedal::set_name(   i, TXT_BUF_1);
    Pedal::set_channel(i, 0);
  }
}
#endif // -- END PEDALS --

#ifdef RESET_FEATURES
{
  PRINT_NLINE(11,0, NUM_FEATURES_TOTAL);
  print_nline(0, 1, "> FEATURES");
  memcpy(text[0], "UNTITLED    ", TEXT_SZ);
  for (uint16_t i=M_FEATURES, j=0; j<NUM_FEATURES_TOTAL; i+=sizeof(Feature), j++) {
    if ( !(j%10) ) PRINT_NLINE(11,1, j);
    Feature::set_name( i, TXT_BUF_1);
    Feature::set_type( i, 0);
    Feature::set_pitch(i, 0);
  }
}
#endif // -- END FEATURES --

#ifdef RESET_PRESETS
{
  PRINT_NLINE(11,0, NUM_PRESETS);
  print_nline(0, 1, "> PRESETS");
  memcpy(text[0], "UNTITLED    ", TEXT_SZ);
  for (uint16_t i=M_PRESETS, j=0; j<NUM_PRESETS; i+=sizeof(Preset), j++) {
    PRINT_NLINE(10,1, j);
    Preset::set_name(i, TXT_BUF_1);
  }
}
#endif // -- END FEATURES --

#ifdef RESET_PRESET_PARAMS
{
  PRINT_NLINE(11,0, NUM_PRESET_PARAMS_TOTAL);
  print_nline(0, 1, "> PRST PRMS");
  Parameter parameter;
  for (uint16_t i=M_PRESET_PARAMS, j=0; j<NUM_PRESET_PARAMS_TOTAL; i+=sizeof(Parameter), j++) {
    if ( !(j%10) ) PRINT_NLINE(12,1, j);
    write_data<Parameter>(&parameter, i);
  }
}
#endif // -- END PRESET PARAMS --

#ifdef RESET_FSW_PARAMS
{
  PRINT_NLINE(11,0, NUM_FSW_PARAMS_TOTAL);
  print_nline(0, 1, "> FSW PRMS");
  Parameter parameter;
  for (uint16_t i=M_FSW_PARAMS, j=0; j<NUM_FSW_PARAMS_TOTAL; i+=sizeof(Parameter), j++) {
    if ( !(j%500) ) PRINT_NLINE(11,1, j);
    write_data<Parameter>(&parameter, i);
  }
}
#endif // -- END PRESET PARAMS --

#ifdef RESET_MENUS
{
  PRINT_NLINE(11,0, " ");
  print_nline(0, 1, "> MENUS");

  // Helper variables
  Menu     menu;
  Option   option;
  uint16_t address;
  uint16_t option_partition_addr;
  uint8_t  num_options_per_menu;

  #include "Load_EEPROM_Menu_Preset.h"
  #include "Load_EEPROM_Menu_Preset_Params.h"
  #include "Load_EEPROM_Menu_Global.h"
//  #include "Load_EEPROM_Menu_Global_Colors.h"
//  #include "Load_EEPROM_Menu_Global_Pedals.h"
//  #include "Load_EEPROM_Menu_Global_Pedal_Features.h"
}
#endif // -- END MENUS --

  lcd.clear();
  print_nline(0,0, "DONE!");
  print_nline(0,1, "END: ");
  PRINT_NLINE(5,1, M_END);

} // -- END SETUP --

void loop() {}

#endif
