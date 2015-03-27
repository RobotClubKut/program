// ------------------------------------------------------------------
// kvr / KUT AVR Library
// I2C Common Library / "kvr/i2c/common.h" / v1.0
// Author: KUT RobotClub, MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ‰”Å
//
// ------------------------------------------------------------------

#ifndef __KVR_I2C_COMMON__
#define __KVR_I2C_COMMON__

#define KVR_I2C_COMMON_VERSION 10000UL // version 1.00.00

// ----- write ------------------------------------------------------

static void i2c_common_write_uint16(
	void (* const write_uint8)(uint8_t),
	const uint16_t data
	)
{
	write_uint8((uint8_t)((data >> 8) & 0xff));
	write_uint8((uint8_t)( data       & 0xff));
}

static void i2c_common_write_uint32(
	void (* const write_uint8)(uint8_t),
	const uint32_t data
	)
{
	write_uint8((uint8_t)((data >> 24) & 0xff));
	write_uint8((uint8_t)((data >> 16) & 0xff));
	write_uint8((uint8_t)((data >>  8) & 0xff));
	write_uint8((uint8_t)( data        & 0xff));
}

static void i2c_common_write_uint64(
	void (* const write_uint8)(uint8_t),
	const uint64_t data
	)
{
	write_uint8((uint8_t)((data >> 56) & 0xff));
	write_uint8((uint8_t)((data >> 48) & 0xff));
	write_uint8((uint8_t)((data >> 40) & 0xff));
	write_uint8((uint8_t)((data >> 32) & 0xff));
	write_uint8((uint8_t)((data >> 24) & 0xff));
	write_uint8((uint8_t)((data >> 16) & 0xff));
	write_uint8((uint8_t)((data >>  8) & 0xff));
	write_uint8((uint8_t)( data        & 0xff));
}

#define i2c_common_write_int16 i2c_common_write_uint16
#define i2c_common_write_int32 i2c_common_write_uint32
#define i2c_common_write_int64 i2c_common_write_uint64

#define i2c_common_write_char     i2c_common_write_uint8
#define i2c_common_write_short    i2c_common_write_int16
#define i2c_common_write_int      i2c_common_write_int16
#define i2c_common_write_long     i2c_common_write_int32
#define i2c_common_write_longlong i2c_common_write_int64

// ----- read -------------------------------------------------------

static uint16_t i2c_common_read_uint16(
	uint8_t (* const read_uint8)(void)
	)
{
	uint16_t t = 0;
	
	t |= (uint16_t)read_uint8() << 8;
	t |=           read_uint8();
	
	return t;
}

static uint32_t i2c_common_read_uint32(
	uint8_t (* const read_uint8)(void)
	)
{
	uint32_t t = 0;
	
	t |= (uint32_t)read_uint8() << 24;
	t |= (uint32_t)read_uint8() << 16;
	t |= (uint32_t)read_uint8() <<  8;
	t |=           read_uint8();
	
	return t;
}

static uint64_t i2c_common_read_uint64(
	uint8_t (* const read_uint8)(void)
	)
{
	uint64_t t = 0;
	
	t |= (uint64_t)read_uint8() << 56;
	t |= (uint64_t)read_uint8() << 48;
	t |= (uint64_t)read_uint8() << 40;
	t |= (uint64_t)read_uint8() << 32;
	t |= (uint64_t)read_uint8() << 24;
	t |= (uint64_t)read_uint8() << 16;
	t |= (uint64_t)read_uint8() <<  8;
	t |=           read_uint8();
	
	return t;
}

#define i2c_common_read_int16 i2c_common_read_uint16
#define i2c_common_read_int32 i2c_common_read_uint32
#define i2c_common_read_int64 i2c_common_read_uint64

#define i2c_common_read_char     i2c_common_read_uint8
#define i2c_common_read_short    i2c_common_read_int16
#define i2c_common_read_int      i2c_common_read_int16
#define i2c_common_read_long     i2c_common_read_int32
#define i2c_common_read_longlong i2c_common_read_int64

#endif
