#ifndef INCLUDES_H
#define INCLUDES_H

/*
 * I know you're not really supposed to do this, however, I'm keeping
 * everything as header files so..
 */


// Global Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


// Definitions

// EEPROM map
#define EEP_START_COLORS     0
#define EEP_NUM_COLORS       100

#define EEP_START_PEDALS     2400
#define EEP_NUM_PEDALS       8

#define EEP_START_PARAMS     2568
#define EEP_NUM_PARAMS       256

#define EEP_START_FSW        7944
#define EEP_NUM_FSW          1600

#define EEP_START_PRESETS    31944
#define EEP_NUM_PRESETS      100

#define EEP_START_MENUS      34044
#define EEP_NUM_MENUS        20

#define EEP_START_OPTS       34074
#define EEP_NUM_OPTS         20

#define EEP_START_LETTERS    40535
#define EEP_NUM_LETTERS      38
#define EEP_NUM_LETTERS_MAX  (EEP_NUM_LETTERS+1)

// EEPROM MENUS
#define EEP_PRESET_MENU       0
#define EEP_GLOBAL_MENU       1
#define EEP_GLOBAL_COLOR_MENU 4
#define EEP_PRESET_PARAM_MENU 3 // NOT CORRECT
//--

// Settings
#define NUM_PEDAL_PARAMS 20
#define NUM_FSW          4
#define NUM_SUB_MENUS    4
#define NUM_STATES       3

#define NUM_MENU_ITEMS   10

#define STR_LEN          12
#define STR_LEN_MAX      (STR_LEN+1)

// Button
#define PRESS_TYPE_UP   0
#define PRESS_TYPE_DOWN 1

// Footswitch
#define FSW_MODE_OFF     0
#define FSW_MODE_TOGGLE  2
#define FSW_MODE_CYCLE   3
#define FSW_MODE_ONESHOT 1

// Screen
#define LCD_ADDR   0x27
#define LCD_WIDTH  16
#define LCD_HEIGHT 2

// LED
#define DEFAULT_LED_TIME_MS 50

// MACROS
#define LTRUE  1
#define LFALSE 2
#define CONTAIN(i, min, max) (i>(min) ? (i<(max) ? i : (max)) : (min))
#define ROTATE(i, min, max) (i>(min) ? (i<(max) ? i : (min)) : (max))
#define CLRPTR(ptr) if(ptr != nullptr) {delete ptr; ptr = nullptr;}

// FLAGS
// RESET EEPROM - Undef to remove
//#define EEP_RESET
//#define EEP_RESET_COLORS
//#define EEP_RESET_PEDALS
//#define EEP_RESET_PARAMS
//#define EEP_RESET_FSW
//#define EEP_RESET_PRESETS
//#define EEP_RESET_MENUS
//#define EEP_RESET_OPTS
//#define EEP_RESET_LETTERS
//-- END RESET EEPROM--

// FLAGS
//#define ALT_PROGRAM
//#define RESET_EEP_PROGRAM
// -- END FLAGS --

// Headers
#include "Standard.h"
#include "Menu.h"
#include "I2C_EEPROM.h"
#include "Database.h"
uint8_t    preset_id = 0;
Preset     preset;
Footswitch fsw[NUM_SUB_MENUS][NUM_FSW];
#include "Button.h"
#include "Encoder.h"
#include "Buttons.h"
#include "ShiftRegisterPWM.h"
#include "Channel.h"
#include "LED.h"
#include "LEDs.h"
#include "Screen.h"
#include "Hardware.h"
#include "MenuLoop.h"
#include "TextEdit.h"
#include "ColorEdit.h"
//#include "ValueEdit.h"
#include "Settings.h"

#endif
