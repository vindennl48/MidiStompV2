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
#define NUM_PEDAL_PARAMS   32                      // Number of params per pedal
#define NUM_PARAMS_PER_FSW 10                      // Number of params that activate on fsw stomp
#define NUM_PRESET_PARAMS  NUM_PARAMS_PER_FSW      // Number of params per preset load
#define NUM_FSW            4                       // Number of hardware fsw
#define NUM_SUB_MENUS      4                       // Number of total sub-menus per preset
#define NUM_FSW_PER_PRESET (NUM_FSW*NUM_SUB_MENUS) // Number of total FSW per preset
#define NUM_STATES         3                       // Number of states to cycle per fsw

#define NUM_MENU_ITEMS     10                      // Number of total menu items allowed per settings menu

#define STR_LEN            12                      // Max number of characters per string
#define STR_LEN_MAX        (STR_LEN+1)             // Max chars plus null terminated char

// -- EEPROM MAP --
#define EEP_NUM_COLORS          100
#define EEP_NUM_PEDALS          8
#define EEP_NUM_PARAMS          (NUM_PEDAL_PARAMS * EEP_NUM_PEDALS)
#define EEP_NUM_PRESETS         30
#define EEP_NUM_PRESET_PARAMS   (EEP_NUM_PRESETS * NUM_PRESET_PARAMS)
#define EEP_NUM_FSW             (NUM_FSW * NUM_SUB_MENUS * EEP_NUM_PRESETS)
#define EEP_NUM_FSW_PARAMS      (NUM_PARAMS_PER_FSW * (NUM_STATES+1) * EEP_NUM_FSW) // NUM_STATES + 1 for long-press
#define EEP_NUM_MENUS           20
#define EEP_NUM_OPTS            (EEP_NUM_MENUS * 10)
#define EEP_NUM_LETTERS         38
#define EEP_NUM_LETTERS_MAX     (EEP_NUM_LETTERS+1)

#define EEP_START_COLORS        0
#define EEP_START_PEDALS        ((sizeof(Color)*EEP_NUM_COLORS)+1)
#define EEP_START_PARAMS        (EEP_START_PEDALS+(sizeof(Pedal)*EEP_NUM_PEDALS)+1)
#define EEP_START_FSW           (EEP_START_PARAMS+(sizeof(Param)*EEP_NUM_PARAMS)+1)
#define EEP_START_FSW_PARAMS    (EEP_START_FSW+(sizeof(Footswitch)*EEP_NUM_FSW)+1)
#define EEP_START_PRESETS       (EEP_START_FSW_PARAMS+(sizeof(PedalParam)*EEP_NUM_FSW_PARAMS)+1)
#define EEP_START_PRESET_PARAMS (EEP_START_PRESETS+(sizeof(Preset)*EEP_NUM_PRESETS)+1)
#define EEP_START_MENUS         (EEP_START_PRESET_PARAMS+(sizeof(PedalParam)*EEP_NUM_PRESET_PARAMS)+1)
#define EEP_START_OPTS          (EEP_START_MENUS+(sizeof(SubMenu)*EEP_NUM_MENUS)+1)
#define EEP_START_LETTERS       65490 // At very end of EEPROM

#define EEP_RAM_PRESET          (EEP_START_OPTS+(sizeof(MenuOption)*EEP_NUM_OPTS)+1)
#define EEP_RAM_PRESET_PARAMS   (EEP_RAM_PRESET+(sizeof(Preset))+1)
#define EEP_RAM_FSW             (EEP_RAM_PRESET_PARAMS+(sizeof(PedalParam)*NUM_PRESET_PARAMS)+1)
#define EEP_RAM_FSW_PARAMS      (EEP_RAM_FSW+(sizeof(Footswitch)*NUM_FSW*NUM_SUB_MENUS)+1)

// EEPROM MENUS
#define EEP_SUBMENU_PRESET      0
#define EEP_SUBMENU_GLOBAL      1
#define EEP_SUBMENU_PARAM       2
#define EEP_SUBMENU_PEDAL       3
#define EEP_SUBMENU_PEDAL_PARAM 4
#define EEP_SUBMENU_FSW         5
#define EEP_SUBMENU_COLOR       6
// -- END EEPROM MAP --

// Footswitch
#define PRESS_TYPE_UP    0  // Only activates when fsw is pressed THEN released
#define PRESS_TYPE_DOWN  1  // Activates as soon as fsw pressed down; Cannot use long-press

#define FSW_MODE_OFF      0  // NONE
#define FSW_MODE_TOGGLE   1  // Press once for on, 2x for off
#define FSW_MODE_CYCLE    2  // Press once for on, 2x for on2, 3x for off
#define FSW_MODE_ONESHOT  3  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_SUBMENU  4  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_PRESET_X 5  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_PRESET_N 6  // Every press only sends one set of params, no cycling or toggle
#define FSW_MODE_QUANTIZE 7  // Every press only sends one set of params, no cycling or toggle

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
//#define EEP_RESET_PEDAL_PARAMS
//#define EEP_RESET_FSW
//#define EEP_RESET_FSW_PARAMS
//#define EEP_RESET_PRESETS
//#define EEP_RESET_PRESET_PARAMS
//#define EEP_RESET_MENUS
//#define EEP_RESET_LETTERS
// --- END RESET EEPROM ---

//#define ALT_PROGRAM
//#define RESET_EEP_PROGRAM
// -- END FLAGS --

// -- VARS --
uint8_t preset_id             = 0;
uint8_t preset_submenu        = 0;
uint8_t preset_selected_param = 0;
uint8_t pedal_selected        = 0;
uint8_t pedal_param_selected  = 0;
uint8_t color_selected        = 0;
uint8_t fsw_selected          = 0;
uint8_t fsw_selected_state    = 0;

uint16_t value_edit = 0;  // Used for ValueEdit and other functions
// -- END VARS --

// Headers
#include "Standard.h"
#include "Menu.h"
#include "I2C_EEPROM.h"
#include "Database.h"
#include "Button.h"
#include "Encoder.h"
#include "Buttons.h"
#include "ShiftRegisterPWM.h"
#include "Channel.h"
#include "LED.h"
#include "LEDs.h"
#include "Screen.h"
#include "Hardware.h"
#include "ListLoop.h"
#include "PedalParamLoop.h"
#include "Confirm.h"
#include "TextEdit.h"
#include "ColorEdit.h"
#include "ValueEdit.h"
#include "submenu_helpers.h"
#include "submenu_preset.h"
#include "submenu_pedal.h"
#include "submenu_color.h"
#include "MenuSystem.h"
#include "Reset.h"

#endif
