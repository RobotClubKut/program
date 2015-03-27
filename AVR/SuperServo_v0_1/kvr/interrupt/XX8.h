// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt for XX8 Library / "kvr/interrupt/XX8.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-07)
//   ���ŁB
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT_XX8__
#define __KVR_INTERRUPT_XX8__

#define KVR_INTERRUPT_XX8_VERSION 10000UL // version 1.00.00

// ���荞�݂̌�
#define KVR_INTERRUPT_LENGTH 24

// ���荞�݊J�n
static void interrupt_start_impl(
	volatile const uint8_t num
	)
{
	if(num < 8){
		PCICR  |= _BV(PCIE0);
		PCMSK0 |= _BV(num);
	}
	
	else if(num < 16){
		PCICR  |= _BV(PCIE1);
		PCMSK1 |= _BV(num - 8);
	}
	
	else {
		PCICR  |= _BV(PCIE2);
		PCMSK2 |= _BV(num - 16);
	}
}

// ���荞�ݒ�~
static void interrupt_stop_impl(
	volatile const uint8_t num
	)
{
	if(num < 8){
		PCMSK0 &= ~_BV(num);
	}
	
	else if(num < 16){
		PCMSK1 &= ~_BV(num - 8);
	}
	
	else {
		PCMSK2 &= ~_BV(num - 16);
	}
}

// ���荞�ݏ���
ISR(PCINT0_vect){ // PORTB
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK0 & _BV(i)){
			interrupt_callback(i);
		}
	}
}

ISR(PCINT1_vect){ // PORTC
	uint8_t i;
	
	for(i = 0; i < 7; ++i){ // PCINT 15 �͑��݂��Ȃ��ׁAi < 7
		if(PCMSK1 & _BV(i)){
			interrupt_callback(i + 8);
		}
	}
}

ISR(PCINT2_vect){ // PORTD
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK2 & _BV(i)){
			interrupt_callback(i + 16);
		}
	}
}

#endif
