// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt for 2313 Library / "kvr/interrupt/2313.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-07)
//   ���ŁB
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT_2313__
#define __KVR_INTERRUPT_2313__

#define KVR_INTERRUPT_2313_VERSION 10000UL // version 1.00.00

// ���荞�݂̌�
#define KVR_INTERRUPT_LENGTH 8

// ���荞�݊J�n
static void interrupt_start_impl(
	volatile const uint8_t num
	)
{
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(num);
}

// ���荞�ݒ�~
static void interrupt_stop_impl(
	volatile const uint8_t num
	)
{
	PCMSK &= ~_BV(num);
}

// ���荞�ݏ���
ISR(PCINT_vect){
	uint8_t i;

	for(i = 0; i < 8; ++i){
		if(PCMSK & _BV(i)){
			interrupt_callback(i);
		}
	}
}

#endif
