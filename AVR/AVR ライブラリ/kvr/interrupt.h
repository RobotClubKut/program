// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Interrupt Library / "kvr/interrupt.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0 (2012-10-06)
//   ���ŁB
//
// ------------------------------------------------------------------
// * �Ή��}�C�R��
//
//   - 28 PIN
//     ATmega48/48A/48P/88/88A/88P/88PA/168/168A/168P/328/328P
//
//   - 40 PIN
//     ATmega164P/164A/324P/324A/324PA/644/644P/644A/644PA/1284P
//
//   - 20 PIN
//     ATtiny2313/2313A
//
// ------------------------------------------------------------------

#ifndef __KVR_INTERRUPT__
#define __KVR_INTERRUPT__

#define KVR_INTERRUPT_VERSION 10000UL // version 1.00.00

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "base.h"

// ------------------------------------------------------------------

// ���荞�݂̏�����
void interrupt_init(void);

// ���荞�݂̊J�n
void interrupt_start(
	volatile const uint8_t num,
	void (* volatile const callback)(void)
);

// ���荞�݂̒�~
void interrupt_stop(
	volatile const uint8_t num
);

// ���荞�݃R�[���o�b�N�֐�
void interrupt_callback(
	volatile const uint8_t num
);

// ------------------------------------------------------------------
// �}�C�R���ʎ����̌Ăяo��
// ------------------------------------------------------------------

static void interrupt_start_impl(
	volatile const uint8_t num
);

static void interrupt_stop_impl(
	volatile const uint8_t num
);

// ------------------------------------------------------------------

#if   defined(KVR_BASE_XX4)
#include "interrupt/XX4.h"
#elif defined(KVR_BASE_XX8)
#include "interrupt/XX8.h"
#elif defined(KVR_BASE_2313)
#include "interrupt/2313.h"
#else
#error "This microprocessor is not supported."
#endif

// ------------------------------------------------------------------

// �֐��|�C���^
static void (* volatile interrupt_callback_func[KVR_INTERRUPT_LENGTH])(void);

// ------------------------------------------------------------------

// ���荞�݂̏�����
void interrupt_init(void){
	uint8_t i;	

	sei();

	for(i = 0; i < KVR_INTERRUPT_LENGTH; ++i){
		interrupt_callback_func[i] = NULL;
	}
}

// ���荞�݂̊J�n
void interrupt_start(
	volatile const uint8_t num,
	void (* volatile const callback)(void)
	)
{
	interrupt_callback_func[num] = callback;
	interrupt_start_impl(num);
}

// ���荞�݂̒�~
void interrupt_stop(
	volatile const uint8_t num
	)
{
	interrupt_callback_func[num] = NULL;
	interrupt_stop_impl(num);
}

// ���荞�݃R�[���o�b�N�֐�
void interrupt_callback(
	volatile const uint8_t num
	)
{
	if(interrupt_callback_func[num]){
		interrupt_callback_func[num]();
	}
}

// ------------------------------------------------------------------

#undef KVR_INTERRUPT_LENGTH

#endif
