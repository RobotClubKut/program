// ======================================================================
// xkvr (XMEGA KUT AVR Library) / interrupt.h / v1.0
// ���荞�� ���C�u����
// ======================================================================
// 
// * interrupt_init();
//   ���荞�݂̏������B
//   �|�[�g�ʂ̊��荞�ݐݒ������O�ɁA�Ăяo���K�v������B
//
// * interrupt_start(�|�[�g, �|�[�g�ԍ�, �֐�)
//   ���荞�݂��J�n����B
//   �Ăяo�����֐��́A�����Ɩ߂�l�������Ă͂����Ȃ��B
//   
//   ��:
//      // PB4 �Ŋ��荞�݂�����������Afunc ���Ăяo���B
//      interrupt_start(&PORTB, 4, func);
//
// * interrupt_start_ex
//   ���荞�݂��J�n����B
//   ���荞�݃��x���ȂǁA�ڍׂȐݒ肪�\�B
//   �g�p���@�̓\�[�X�R�[�h���Q�ƁB
//
// ======================================================================
//
// * v1.0 (2012/03/30 8:05)
//   ����
//
// ======================================================================
// ����m�F��: ATxmega128D3 @ 32 MHz
// ======================================================================


#ifndef __XKVR_INTERRUPT__
#define __XKVR_INTERRUPT__


// ----------------------------------------------------------------------

#if F_CPU != 32000000UL
#error "Only a clock of 32MHz is supported."
#endif

#define XKVR_INTERRUPT_VERSION 10000UL // version 1.00.00

// ----------------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>

#include "base.h"

#if defined(XKVR_BASE_D3)
#include "interrupt/D3.h"
#endif

// ----------------------------------------------------------------------

typedef enum {
	InterruptHigh   = 0,
	InterruptMiddle = 1,
	InterruptLow    = 2
} InterruptLevel;

// ���荞�ݏ�����
void interrupt_init(void){

	// ���x���� ���荞�݋���
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	
	// �S�̊��荞�݋���
	sei();
	
	// �}�C�R���ʏ�����
	interrupt_init_impl();
}

// ���荞�݊J�n
void interrupt_start_ex(
	volatile PORT_t * const port,
	volatile const uint8_t num,
	volatile InterruptLevel level,
	volatile const uint8_t int_num,
	void (* volatile func)(void))
{
	const uint8_t intctrl[2][3] = {
		{
			PORT_INT0LVL_LO_gc,
			PORT_INT0LVL_MED_gc,
			PORT_INT0LVL_HI_gc
		},
		{
			PORT_INT1LVL_LO_gc,
			PORT_INT1LVL_MED_gc,
			PORT_INT1LVL_HI_gc
		}
	};
	
	// �|�[�g���荞�݋���
	port->INTCTRL |= intctrl[int_num][(uint8_t)level];
	
	// ���荞�݃|�[�g�ԍ��w��
	if(int_num == 0){
		port->INT0MASK |= _BV(num);
	}
	
	else {
		port->INT1MASK |= _BV(num);
	}
	
	interrupt_start_ex_impl(port, num, int_num, func);
}

// ���荞�݊J�n
void interrupt_start(
	volatile PORT_t * const port,
	volatile const uint8_t num,
	void (*func)(void))
{
	interrupt_start_ex(port, num, InterruptMiddle, 0, func);
}

#endif