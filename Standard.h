#ifndef STANDARD_H
#define STANDARD_H

/* :: CREATOR MACROS :: */

#define BIT_OUTPUT_SETUP(DDR, POS)       DDR  |=  _BV(POS)
#define BIT_SET_TRUE(PORT, POS)          PORT |=  _BV(POS)
#define BIT_SET_FALSE(PORT, POS)         PORT &= ~_BV(POS)
#define BIT_SET_TOGGLE(PORT, POS)        PORT ^=  _BV(POS)
#define BIT_INPUT_SETUP(DDR, PORT, POS)  DDR  &= ~_BV(POS); PORT |= _BV(POS)
#define BIT_GET_VALUE(PIN, POS)          ( PIN & _BV(POS) ) ? false : true

#define PIN_OUTPUT_SETUP(X, POS)         DDR##X  |=  _BV(POS)
#define PIN_SET_TRUE(X, POS)             PORT##X |=  _BV(POS)
#define PIN_SET_FALSE(X, POS)            PORT##X &= ~_BV(POS)
#define PIN_SET_TOGGLE(X, POS)           PORT##X ^=  _BV(POS)

#define PIN_INPUT_SETUP(X, POS)          DDR##X &= ~_BV(POS); PORT##X |= _BV(POS)
#define PIN_GET_VALUE(X, POS)            ( PIN##X & _BV(POS) ) ? false : true

#define BUILD_ARGS(X, POS)               &DDR##X, &PIN##X, &PORT##X, POS

/* :: END CREATOR MACROS :: */


/* :: ACTUAL HARDWARE PIN MAPS :: */

#define LED_BOARD_SETUP          PIN_OUTPUT_SETUP(B, 5)
#define LED_BOARD_TRUE           PIN_SET_TRUE(    B, 5)
#define LED_BOARD_FALSE          PIN_SET_FALSE(   B, 5)
#define LED_BOARD_TOGGLE         PIN_SET_TOGGLE(  B, 5)

#define PIN_D2                   BUILD_ARGS(      D, 2)
#define PIN_D2_SETUP_INPUT       PIN_INPUT_SETUP( D, 2)
#define PIN_D2_GET               PIN_GET_VALUE(   D, 2)
#define PIN_D2_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 2)
#define PIN_D2_TRUE              PIN_SET_TRUE(    D, 2)
#define PIN_D2_FALSE             PIN_SET_FALSE(   D, 2)
#define PIN_D2_TOGGLE            PIN_SET_TOGGLE(  D, 2)

#define PIN_D3                   BUILD_ARGS(      D, 3)
#define PIN_D3_SETUP_INPUT       PIN_INPUT_SETUP( D, 3)
#define PIN_D3_GET               PIN_GET_VALUE(   D, 3)
#define PIN_D3_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 3)
#define PIN_D3_TRUE              PIN_SET_TRUE(    D, 3)
#define PIN_D3_FALSE             PIN_SET_FALSE(   D, 3)
#define PIN_D3_TOGGLE            PIN_SET_TOGGLE(  D, 3)

#define PIN_D4                   BUILD_ARGS(      D, 4)
#define PIN_D4_SETUP_INPUT       PIN_INPUT_SETUP( D, 4)
#define PIN_D4_GET               PIN_GET_VALUE(   D, 4)
#define PIN_D4_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 4)
#define PIN_D4_TRUE              PIN_SET_TRUE(    D, 4)
#define PIN_D4_FALSE             PIN_SET_FALSE(   D, 4)
#define PIN_D4_TOGGLE            PIN_SET_TOGGLE(  D, 4)

#define PIN_D5                   BUILD_ARGS(      D, 5)
#define PIN_D5_SETUP_INPUT       PIN_INPUT_SETUP( D, 5)
#define PIN_D5_GET               PIN_GET_VALUE(   D, 5)
#define PIN_D5_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 5)
#define PIN_D5_TRUE              PIN_SET_TRUE(    D, 5)
#define PIN_D5_FALSE             PIN_SET_FALSE(   D, 5)
#define PIN_D5_TOGGLE            PIN_SET_TOGGLE(  D, 5)

#define PIN_D6                   BUILD_ARGS(      D, 6)
#define PIN_D6_SETUP_INPUT       PIN_INPUT_SETUP( D, 6)
#define PIN_D6_GET               PIN_GET_VALUE(   D, 6)
#define PIN_D6_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 6)
#define PIN_D6_TRUE              PIN_SET_TRUE(    D, 6)
#define PIN_D6_FALSE             PIN_SET_FALSE(   D, 6)
#define PIN_D6_TOGGLE            PIN_SET_TOGGLE(  D, 6)

#define PIN_D7                   BUILD_ARGS(      D, 7)
#define PIN_D7_SETUP_INPUT       PIN_INPUT_SETUP( D, 7)
#define PIN_D7_GET               PIN_GET_VALUE(   D, 7)
#define PIN_D7_SETUP_OUTPUT      PIN_OUTPUT_SETUP(D, 7)
#define PIN_D7_TRUE              PIN_SET_TRUE(    D, 7)
#define PIN_D7_FALSE             PIN_SET_FALSE(   D, 7)
#define PIN_D7_TOGGLE            PIN_SET_TOGGLE(  D, 7)

#define PIN_B9                   BUILD_ARGS(      B, 1)
#define PIN_B9_SETUP_INPUT       PIN_INPUT_SETUP( B, 1)
#define PIN_B9_GET               PIN_GET_VALUE(   B, 1)
#define PIN_B9_SETUP_OUTPUT      PIN_OUTPUT_SETUP(B, 1)
#define PIN_B9_TRUE              PIN_SET_TRUE(    B, 1)
#define PIN_B9_FALSE             PIN_SET_FALSE(   B, 1)
#define PIN_B9_TOGGLE            PIN_SET_TOGGLE(  B, 1)

#define PIN_B11                  BUILD_ARGS(      B, 3)
#define PIN_B11_SETUP_INPUT      PIN_INPUT_SETUP( B, 3)
#define PIN_B11_GET              PIN_GET_VALUE(   B, 3)
#define PIN_B11_SETUP_OUTPUT     PIN_OUTPUT_SETUP(B, 3)
#define PIN_B11_TRUE             PIN_SET_TRUE(    B, 3)
#define PIN_B11_FALSE            PIN_SET_FALSE(   B, 3)
#define PIN_B11_TOGGLE           PIN_SET_TOGGLE(  B, 3)

#define PIN_B12                  BUILD_ARGS(      B, 4)
#define PIN_B12_SETUP_INPUT      PIN_INPUT_SETUP( B, 4)
#define PIN_B12_GET              PIN_GET_VALUE(   B, 4)
#define PIN_B12_SETUP_OUTPUT     PIN_OUTPUT_SETUP(B, 4)
#define PIN_B12_TRUE             PIN_SET_TRUE(    B, 4)
#define PIN_B12_FALSE            PIN_SET_FALSE(   B, 4)
#define PIN_B12_TOGGLE           PIN_SET_TOGGLE(  B, 4)

/* :: END - ACTUAL HARDWARE PIN MAPS :: */

/* :: TYPEDEFS :: */
typedef unsigned long Timer;
/* :: END - TYPEDEFS :: */

#endif
