#include <Arduino.h>
#include "Nav.h"
#include "Com.h"
#include "Hardware.h"
#include "I2C_EPROM.h"

Nav     COM::n;
uint8_t COM::is_socket = false;


void COM::thru() {
  int sz = Serial.available();

  if ( sz > 0 ) {
    for (int i=0; i<sz; i++) {
      uint8_t value = Serial.read();

      if ( value == 0xFF ) {
        // Socket mode initiated by Serial in
        //Serial.write(0xFF);  // Confirm packet
        is_socket = true;    // Tell main.ino to go into socket mode
      }
      else {
#ifdef RUN_DEBUG
        Serial.println( String("THRU>> ") + String(value) );
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
#define E_READ_TEXT      3
#define E_READ_BLOCK     4
#define E_WRITE_UINT8_T  5
#define E_WRITE_UINT16_T 6
#define E_WRITE_TEXT     7
#define E_WRITE_BLOCK    8
uint8_t COM::socket() {
  switch(n.e()) {
    default:
    case E_WAITING:
      if ( n.not_init() ) {
        HW::screen.print_nline(0, 0, ">CONNECTED");
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 1 ) {
          uint8_t value = Serial.read();
          if ( value != 0 ) {
            n.jump_to(value);
          }
          else {
            // We are done connecting
            n.reset();
            is_socket = false;
            Serial.write(0xFF); // Confirm
            return true;
          }
        }
      }
      break;

    case E_READ_UINT8_T:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 2 ) {
          Serial.write(
            EPROM::read_uint8_t( Serial.read()<<8 | Serial.read() )
          );

          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_READ_UINT16_T:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 2 ) {
          uint16_t addr = Serial.read()<<8 | Serial.read();
          Serial.write( EPROM::read_uint8_t(addr) );
          Serial.write( EPROM::read_uint8_t(addr + 1) );

          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_READ_TEXT:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 2 ) {
          uint16_t addr = Serial.read()<<8 | Serial.read();
          for (int i=0; i<TEXT_SZ-1; i++)
            Serial.write( EPROM::read_uint8_t(addr) );

          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_READ_BLOCK:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 4 ) {
          HW::screen.print(15, 1, "H");
          uint16_t addr = Serial.read()<<8 | Serial.read();
          uint16_t sz   = Serial.read()<<8 | Serial.read();

          for (uint16_t i=0; i<sz; i++)
            Serial.write( EPROM::read_uint8_t(addr + i) );
          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_WRITE_UINT8_T:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 3 ) {
          EPROM::write_uint8_t(Serial.read()<<8 | Serial.read(), Serial.read());

          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_WRITE_UINT16_T:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == 4 ) {
          EPROM::write_uint16_t(
            Serial.read()<<8 | Serial.read(),
            Serial.read()<<8 | Serial.read()
          );

          n.jump_to(E_WAITING);
        }
      }
      break;

    case E_WRITE_TEXT:
      if ( n.not_init() ) {
        Serial.write(0xFF); // Confirm
      }
      else {
        if ( Serial.available() == (TEXT_SZ+1) ) {
          uint16_t addr = Serial.read()<<8 | Serial.read();
          for (int i=0; i<TEXT_SZ-1; i++)
            EPROM::write_uint8_t( addr, Serial.read() );

          n.jump_to(E_WAITING);
        }
      }
      break;
  };

  return false;
}

void COM::debug(String text) {
#ifdef RUN_DEBUG
  Serial.println(text);
#endif
}
