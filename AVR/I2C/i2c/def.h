// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Define Library / "kvr/i2c/def.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   初版
//
// ------------------------------------------------------------------

#ifndef __KVR_I2C_DEF__
#define __KVR_I2C_DEF__

#include <stdint.h>

#define KVR_I2C_DEF_VERSION 10000UL // version 1.00.00

// I2C アドレス (7 bit)
typedef uint8_t i2c_addr7_t;

// I2C パケットサイズ (データ長含まず)
#define KVR_I2C_PACKET_SIZE 127

#endif
