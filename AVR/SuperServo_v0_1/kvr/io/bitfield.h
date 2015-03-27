// ------------------------------------------------------------------
// kvr / KUT AVR Library
// IO Bitfield Library / "kvr/io/bitfield.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   èâî≈ÅB
//
// ------------------------------------------------------------------

#ifndef __KVR_IO_BITFIELD__
#define __KVR_IO_BITFIELD__

#define KVR_IO_BITFIELD_VERSION 10000 // version 1.00.00

#include <avr/io.h>

#include "../base.h"

typedef struct{
	uint8_t b0 : 1;
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;
} IO_BITFIELD;

#define BF_PORTA (*(volatile IO_BITFIELD *)(&PORTA))
#define BF_PORTB (*(volatile IO_BITFIELD *)(&PORTB))
#define BF_PORTC (*(volatile IO_BITFIELD *)(&PORTC))
#define BF_PORTD (*(volatile IO_BITFIELD *)(&PORTD))
#define BF_PINA  (*(volatile IO_BITFIELD *)(&PINA))
#define BF_PINB  (*(volatile IO_BITFIELD *)(&PINB))
#define BF_PINC  (*(volatile IO_BITFIELD *)(&PINC))
#define BF_PIND  (*(volatile IO_BITFIELD *)(&PIND))
#define BF_DDRA  (*(volatile IO_BITFIELD *)(&DDRA))
#define BF_DDRB  (*(volatile IO_BITFIELD *)(&DDRB))
#define BF_DDRC  (*(volatile IO_BITFIELD *)(&DDRC))
#define BF_DDRD  (*(volatile IO_BITFIELD *)(&DDRD))

#if defined(KVR_BASE_2313)
#include "bitfield/2313.h"
#elif defined(KVR_BASE_XX8)
#include "bitfield/XX8.h"
#elif defined(KVR_BASE_XX4)
#include "bitfield/XX4.h"
#else
#error "This microprocessor is not supported."
#endif

#endif
