// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt for 2313 Library / "kvr/interrupt/2313.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-07)
//   ‰”ÅB
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT_2313__
#define __KVR_INTERRUPT_2313__

#define KVR_INTERRUPT_2313_VERSION 10000UL // version 1.00.00

// Š„‚è‚İ‚ÌŒÂ”
#define KVR_INTERRUPT_LENGTH 8

// Š„‚è‚İŠJn
static void interrupt_start_impl(
	volatile const uint8_t num
	)
{
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(num);
}

// Š„‚è‚İ’â~
static void interrupt_stop_impl(
	volatile const uint8_t num
	)
{
	PCMSK &= ~_BV(num);
}

// Š„‚è‚İˆ—
ISR(PCINT_vect){
	uint8_t i;

	for(i = 0; i < 8; ++i){
		if(PCMSK & _BV(i)){
			interrupt_callback(i);
		}
	}
}

#endif
