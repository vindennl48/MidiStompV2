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
// Settings
#define NUM_PEDAL_PARAMS   32          // Number of params per pedal
#define NUM_PARAMS_PER_FSW 10          // Number of params that activate on fsw stomp
#define NUM_FSW            4           // Number of hardware fsw
#define NUM_SUB_MENUS      4           // Number of total sub-menus per preset
#define NUM_STATES         3           // Number of states to cycle per fsw

#define NUM_MENU_ITEMS     10          // Number of total menu items allowed per settings menu

#define STR_LEN            12          // Max number of characters per string
#define STR_LEN_MAX        (STR_LEN+1) // Max chars plus null terminated char

// -- EEPROM MAP --
#define EEP_NUM_COLORS       100
#define EEP_NUM_PEDALS       8
#define EEP_NUM_PARAMS       (NUM_PEDAL_PARAMS * EEP_NUM_PEDALS)
#define EEP_NUM_PRESETS      100
#define EEP_NUM_FSW          (NUM_FSW * NUM_SUB_MENUS * EEP_NUM_PRESETS)
#define EEP_NUM_MENUS        20
#define EEP_NUM_OPTS         (EEP_NUM_MENUS * 10)
#define EEP_NUM_LETTERS      38
#define EEP_NUM_LETTERS_MAX  (EEP_NUM_LETTERS+1)

#define EEP_START_COLORS     0
#define EEP_START_PEDALS     ((sizeof(Color)*EEP_NUM_COLORS)+1)
#define EEP_START_PARAMS     (EEP_START_PEDALS+(sizeof(Pedal)*EEP_NUM_PEDALS)+1)
#define EEP_START_FSW        (EEP_START_PARAMS+(sizeof(Param)*EEP_NUM_PARAMS)+1)
#define EEP_START_PRESETS    (EEP_START_FSW+(sizeof(Footswitch)*EEP_NUM_FSW)+1)
#define EEP_START_MENUS      (EEP_START_PRESETS+(sizeof(Preset)*EEP_NUM_PRESETS)+1)
#define EEP_START_OPTS       (EEP_START_MENUS+(sizeof(SubMenu)*EEP_NUM_MENUS)+1)
#define EEP_START_LETTERS    (EEP_START_OPTS+(sizeof(MenuOption)*EEP_NUM_OPTS)+1)

// EEPROM MENUS
#define EEP_PRESET_MENU       0
#define EEP_GLOBAL_MENU       1
#define EEP_GLOBAL_COLOR_MENU 4
#define EEP_PRESET_PARAM_MENU 3 // NOT CORRECT
// -- END EEPROM MAP --

// Button
#define PRESS_TYPE_UP   0   // Only activates when fsw is pressed THEN released
#define PRESS_TYPE_DOWN 1   // Activates as soon as fsw pressed down; Cannot use long-press

// Footswitch
#define FSW_MODE_OFF     0  // NONE
#define FSW_MODE_TOGGLE  2  // Press once for on, 2x for off
#define FSW_MODE_CYCLE   3  // Press once for on, 2x for on2, 3x for off
#define FSW_MODE_ONESHOT 1  // Every press only sends one set of params, no cycling or toggle

// Screen
#define LCD_ADDR   0x27
#define LCD_WIDTH  16
#define LCD_HEIGHT 2

// LED
#define DEFAULT_LED_TIME_MS 50

// MENUS/SETTINGS
#define NUM_MENU_OPTIONS 10

#define MENU_TYPE_DUMMY        0
#define MENU_TYPE_SUB_MENU     1
#define MENU_TYPE_FUNCTION     2
#define MENU_TYPE_FUNC_AND_SUB 3

// MACROS
#define LTRUE  1  // True with 0 return
#define LFALSE 2  // False with 0 return
#define CONTAIN(i, min, max) (i>(min) ? (i<(max) ? i : (max)) : (min))
#define ROTATE(i, min, max) (i>(min) ? (i<(max) ? i : (min)) : (max))
#define CLRPTR(ptr) if(ptr != nullptr) {delete ptr; ptr = nullptr;}

// -- FLAGS --
// --- RESET EEPROM --- Undef to remove
//#define EEP_RESET
//#define EEP_RESET_COLORS
//#define EEP_RESET_PEDALS
//#define EEP_RESET_PARAMS
//#define EEP_RESET_PEDAL_PARAMS
//#define EEP_RESET_FSW
//#define EEP_RESET_PRESETS
//#define EEP_RESET_MENUS
//#define EEP_RESET_LETTERS
// --- END RESET EEPROM ---

#define ALT_PROGRAM
//#define RESET_EEP_PROGRAM
// -- END FLAGS --

// Headers
#include "Standard.h"
#include "Menu.h"
#include "I2C_EEPROM.h"
#include "Database.h"
uint8_t    preset_id = 0;
//Preset     preset;
//Footswitch fsw[NUM_SUB_MENUS][NUM_FSW];
#include "Button.h"
#include "Encoder.h"
#include "Buttons.h"
#include "ShiftRegisterPWM.h"
#include "Channel.h"
#include "LED.h"
#include "LEDs.h"
#include "Screen.h"
#include "Hardware.h"
#include "Reset.h"
#include "MenuLoop.h"
#include "TextEdit.h"
#include "ColorEdit.h"
//#include "ValueEdit.h"
//#include "Settings.h"
#include "test_menu.h"

#endif
