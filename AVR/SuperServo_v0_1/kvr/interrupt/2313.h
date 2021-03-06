// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt for 2313 Library / "kvr/interrupt/2313.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-07)
//   初版。
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT_2313__
#define __KVR_INTERRUPT_2313__

#define KVR_INTERRUPT_2313_VERSION 10000UL // version 1.00.00

// 割り込みの個数
#define KVR_INTERRUPT_LENGTH 8

// 割り込み開始
static void interrupt_start_impl(
	volatile const uint8_t num
	)
{
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(num);
}

// 割り込み停止
static void interrupt_stop_impl(
	volatile const uint8_t num
	)
{
	PCMSK &= ~_BV(num);
}

// 割り込み処理
ISR(PCINT_vect){
	uint8_t i;

	for(i = 0; i < 8; ++i){
		if(PCMSK & _BV(i)){
			interrupt_callback(i);
		}
	}
}

#endif
