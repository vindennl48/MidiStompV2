// #ifndef HARD_DRIVE_H
// #define HARD_DRIVE_H
// 
// #include <Arduino.h>
// #include "Definitions.h"
// 
// extern char text[RAM_TEXT_MAX][TEXT_SZ];
// 
// struct Preset;
// struct PresetParam;
// struct Fsw;
// struct FswParam;
// struct Pedal;
// 
// 
// 
// struct PresetParam {
//   static uint16_t hd_start();   // start of preset params in eeprom
//   static uint16_t get_addr(uint8_t id);
// 
//   union { struct {
//     unsigned velocity:7;
//     unsigned feature:5;
//     unsigned pedal:4;
//   };};
//   PresetParam();
// };
// 
// 
// 
// struct Fsw {
//   uint8_t colors[NUM_COLORS_PER_FSW];
// 
//   union { struct {
//     unsigned mode:3;
//     unsigned lp_mode:3;
//     unsigned state:2;
//     unsigned press_type:1;
//   };};
// 
//   Fsw();
// };
// 
// 
// 
// struct FswParam {
//   static uint16_t hd_start();   // start of preset params in eeprom
//   static uint16_t get_addr(uint8_t id);
// 
//   union { struct {
//     unsigned velocity:7;
//     unsigned feature:5;
//     unsigned pedal:4;
//   };};
//   FswParam();
// };
// 
// 
// 
// struct Pedal {
// };
// 
// 
// 
// #endif
