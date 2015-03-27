// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt for XX4 Library / "kvr/interrupt/XX4.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-07)
//   èâî≈ÅB
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT_XX4__
#define __KVR_INTERRUPT_XX4__

#define KVR_INTERRUPT_XX4_VERSION 10000UL // version 1.00.00

// äÑÇËçûÇ›ÇÃå¬êî
#define KVR_INTERRUPT_LENGTH 32

// äÑÇËçûÇ›äJén
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
	
	else if(num < 24){
		PCICR  |= _BV(PCIE2);
		PCMSK2 |= _BV(num - 16);
	}
	
	else {
		PCICR  |= _BV(PCIE3);
		PCMSK3 |= _BV(num - 24);
	}
}

// äÑÇËçûÇ›í‚é~
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
	
	else if(num < 24){
		PCMSK2 &= ~_BV(num - 16);
	}
	
	else {
		PCMSK3 &= ~_BV(num - 24);
	}
}

// äÑÇËçûÇ›èàóù
ISR(PCINT0_vect){ // PORTA
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK0 & _BV(i)){
			interrupt_callback(i);
		}
	}
}

ISR(PCINT1_vect){ // PORTB
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK1 & _BV(i)){
			interrupt_callback(i + 8);
		}
	}
}

ISR(PCINT2_vect){ // PORTC
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK2 & _BV(i)){
			interrupt_callback(i + 16);
		}
	}
}

ISR(PCINT3_vect){ // PORTD
	uint8_t i;
	
	for(i = 0; i < 8; ++i){
		if(PCMSK3 & _BV(i)){
			interrupt_callback(i + 24);
		}
	}
}

#endif
