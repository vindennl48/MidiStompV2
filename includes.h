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

// Settings
#define NUM_PEDAL_PARAMS     20
#define NUM_FSW              4
#define NUM_STATES           3

#define STR_LEN              12
#define STR_LEN_MAX          (STR_LEN+1)

// Button
#define PRESS_TYPE_UP        0
#define PRESS_TYPE_DOWN      1

// Footswitch
#define FSW_MODE_OFF         0
#define FSW_MODE_TOGGLE      2
#define FSW_MODE_CYCLE       3
#define FSW_MODE_ONESHOT     1

// Screen
#define LCD_ADDR     0x27
#define LCD_WIDTH    16
#define LCD_HEIGHT   2

// LED
#define DEFAULT_LED_TIME_MS   50


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
#include "Hardware.h"  // Should be second to last
#include "Menu.h"      // Should be last

#endif
