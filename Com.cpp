#include <Arduino.h>
#include "Nav.h"
#include "Com.h"

Nav     COM::n;
uint8_t COM::is_socket = false;


void COM::thru() {
  int sz = Serial.available();

  if ( sz > 0 ) {
    for (int i=0; i<sz; i++) {
      uint8_t value = Serial.read();

      if ( value == 0xFF ) {
        // Socket mode initiated by Serial in
        Serial.write(0xFF);  // Confirm packet
        is_socket = true;    // Tell main.ino to go into socket mode
      }
      else {
#ifdef RUN_DEBUG
        Serial.write( String("THRU>> ") + String(value) );
#else
        Serial.write( value );
#endif
      }
    }
  }
}

/* 
 * We want this to be an API that we can do pretty much anything with but also
 * limiting the amount of code that we keep on the Arduino.
 * 
 * So we could do this one of two ways:
 *   - Have just an API to access bytes in the EEPROM, read/write
 *     OR
 *   - Have custom written functions below to write to EEPROM for the variety of
 *     different components we have..
 * */
#define E_WAITING        0
#define E_READ_UINT8_T   1
#define E_READ_UINT16_T  2
#define E_WRITE_UINT8_T  3
#define E_WRITE_UINT16_T 4
void COM::socket() {
  switch(n.e()) {
    case E_WAITING:
      if ( Serial.available() > 0 ) {
        Serial.write(0xFF);        // Confirm
        n.jump_to(Serial.read());
      }
      break;

    case E_READ_UINT8_T:
      if ( Serial.available() >= 2 ) {
        Serial.write( EPROM::read_uint8_t() );
      }
      break;

    case E_READ_UINT16_T:
      break;

    case E_WRITE_UINT8_T:
      break;

    case E_WRITE_UINT16_T:
      break;
  };
}

void COM::debug(String text) {
#ifdef RUN_DEBUG
  Serial.println(text);
#endif
}
