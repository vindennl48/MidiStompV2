/* :: TYPEDEFS :: */
typedef unsigned long Timer;
/* :: END - TYPEDEFS :: */


/* :: VARS TO SAVE SRAM :: */
#define TEXT_SZ      13 // bytes, 12 chars + 1 null termination
#define RAM_TEXT_MAX 2
#define TXT_BUF_1    0
#define TXT_BUF_2    1
char text[RAM_TEXT_MAX][TEXT_SZ] = {{' '}};

#define NUM_PARENTS_MAX 6
uint8_t  parents_used             = 0;  // flip bit for parent being used
                                        // NEVER delete parent 0 or things will crash
uint16_t parents[NUM_PARENTS_MAX] = { 0 };

uint8_t get_unused_parent_id() {
  for (uint8_t i=0; i<8; i++)
    if ( !(parents_used & 1<<i) ) return i;
  return 255;
}
uint8_t get_active_parent_id() {
  for (uint8_t i=0; i<8; i++)
    if ( !(parents_used & 1<<i) ) return (i > 0 ? i-1 : i);
  return 0;
}
void activate_new_parent() {
  if ( get_unused_parent_id() < 8 )
    parents_used |= 1<<get_unused_parent_id();
}
void deactivate_active_parent() {
  if ( parents_used > 1 )
    parents_used &= ~(1<<get_active_parent_id());
}
#define GET_UNUSED_PARENT_ID       (get_unused_parent_id())
#define GET_ACTIVE_PARENT_ID       (get_active_parent_id())
#define GET_ACTIVE_PARENT          (parents[GET_ACTIVE_PARENT_ID])
#define SET_ACTIVE_PARENT(address) parents[GET_ACTIVE_PARENT_ID] = address
#define SET_NEW_PARENT(address)    activate_new_parent(); SET_ACTIVE_PARENT(address)
#define CLEAR_PARENTS              parents_used = 1;
/* :: END VARS TO SAVE SRAM :: */


/* :: LOGIC :: */
#define LTRUE  1  // True with 0 return
#define LFALSE 2  // False with 0 return
/* :: END LOGIC :: */


/* :: HELPFUL MACROS :: */
#define CONTAIN(i, min, max) (i>(min) ? (i<(max) ? i : (max-1)) : (min))
#define ROTATE(i, min, max) (i>(min) ? (i<(max) ? i : (min)) : (max-1))
/* :: END HELPFUL MACROS :: */


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


/* :: SERIAL SETUP :: */
#define SERIAL_MIDI_SETUP Serial.begin(31250)
//#define SERIAL_MIDI_SETUP Serial.begin(9600)
/* :: END SERIAL SETUP :: */


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

#define PIN_B0                   BUILD_ARGS(      B, 0)
#define PIN_B0_SETUP_INPUT       PIN_INPUT_SETUP( B, 0)
#define PIN_B0_GET               PIN_GET_VALUE(   B, 0)
#define PIN_B0_SETUP_OUTPUT      PIN_OUTPUT_SETUP(B, 0)
#define PIN_B0_TRUE              PIN_SET_TRUE(    B, 0)
#define PIN_B0_FALSE             PIN_SET_FALSE(   B, 0)
#define PIN_B0_TOGGLE            PIN_SET_TOGGLE(  B, 0)

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


