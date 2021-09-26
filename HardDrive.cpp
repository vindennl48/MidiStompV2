// #include "HardDrive.h"
// #include "I2C_EEPROM.h"
// 
// 
// char text[RAM_TEXT_MAX][TEXT_SZ] = {{' '}};
// 
// 
// /* ::Fsw:: */
// Fsw::Fsw() {
//   colors[0]  = 0;
//   colors[1]  = 1;
//   colors[2]  = 3;
// 
//   mode       = 0;
//   lp_mode    = 0;
//   state      = 0;
//   press_type = 0;
// }
// /* ::END Fsw:: */
// 
// 
// 
// /* ::FswParam:: */
// // Static
// uint16_t FswParam::hd_start() {
//   return HD_START_FSW_PARAMS;
// }
// 
// uint16_t FswParam::get_addr(uint8_t id) {
//   return GET_PARENT(hd_start(), id, sizeof(FswParam));
// }
// 
// // Self
// FswParam::FswParam() {
//   pedal    = NUM_PEDALS;
//   feature  = 0;
//   velocity = 0;
// }
// /* ::END FswParam:: */
