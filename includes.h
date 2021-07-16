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
#define EEPROM_START_COLORS     0
#define EEPROM_NUM_COLORS       100

#define EEPROM_START_PEDALS     2400
#define EEPROM_NUM_PEDALS       8

#define EEPROM_START_PARAMS     2568
#define EEPROM_NUM_PARAMS       256

#define EEPROM_START_FSW        7944
#define EEPROM_NUM_FSW          1600

#define EEPROM_START_PRESETS    31944
#define EEPROM_NUM_PRESETS      100

#define EEPROM_START_MENUS      34044
#define EEPROM_NUM_MENUS        20

#define EEPROM_START_OPTS       34074
#define EEPROM_NUM_OPTS         20
//--
//EEPROM MENU TEXT LOCATIONS
#define EEPROM_TEXT_SETTINGS    0
#define EEPROM_TEXT_SAVE        1
#define EEPROM_TEXT_NAME        2
#define EEPROM_TEXT_PARAMS      3
#define EEPROM_TEXT_COPY        4
#define EEPROM_TEXT_RESET       5
#define EEPROM_TEXT_GLOBAL      6
#define EEPROM_TEXT_PEDALS      7
#define EEPROM_TEXT_CHANNEL     8
#define EEPROM_TEXT_MIDI        9
#define EEPROM_TEXT_COLORS      10
#define EEPROM_TEXT_VALUES      11
#define EEPROM_TEXT_TYPE        12
#define EEPROM_TEXT_SHORT_PRESS 13
#define EEPROM_TEXT_LONG_PRESS  14

//RESET EEPROM - Undef to remove
//#define CODING_RESET
//#define EEPROM_RESET_COLORS
//#define EEPROM_RESET_PEDALS
//#define EEPROM_RESET_PARAMS
//#define EEPROM_RESET_FSW
//#define EEPROM_RESET_PRESETS
//#define EEPROM_RESET_MENUS
//#define EEPROM_RESET_OPTS
//-- END RESET EEPROM--

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
#define CONTAIN(i, min, max) (i>(min) ? (i<(max) ? i : (max)) : (min))
#define ROTATE(i, min, max) (i>(min) ? (i<(max) ? i : (min)) : (max))

// Headers
#include "Standard.h"
#include "Menu.h"
#include "I2C_EEPROM.h"
#include "Database.h"
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
#include "Settings.h"

#endif
