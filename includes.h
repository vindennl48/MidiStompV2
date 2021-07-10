#ifndef INCLUDES_H
#define INCLUDES_H

/*
 * I know you're not really supposed to do this, however, I'm keeping
 * everything as header files so..
 */


// Global Libraries
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


// Definitions

// EEPROM map
#define EEPROM_START_COLORS  0
#define EEPROM_NUM_COLORS    14

#define EEPROM_START_PEDALS  225
#define EEPROM_NUM_PEDALS    2

#define EEPROM_START_PARAMS  254
#define EEPROM_NUM_PARAMS    20

#define EEPROM_START_FSW     535
#define EEPROM_NUM_FSW       32

#define EEPROM_START_PRESETS 792
#define EEPROM_NUM_PRESETS   2

#define EEPROM_START_MENUS   821
#define EEPROM_NUM_MENUS     15
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

// Settings
#define NUM_PEDAL_PARAMS 20
#define NUM_FSW          4
#define NUM_STATES       3

#define STR_LEN          12
#define STR_LEN_MAX      (STR_LEN+1)

#define CODING_RESET     //undef to remove useless bytes from code

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
#define CONTAIN(i, min, max) (i>min ? (i<max ? i : max) : min)
#define ROTATE(i, min, max) (i>min ? (i<max ? i : min) : max)

// Headers
#include "Standard.h"
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
#include "Menu.h"
#include "Settings.h"

#endif
