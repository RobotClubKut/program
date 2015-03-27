// ======================================================================
// xkvr (XMEGA KUT AVR Library) / interrupt.h / v1.0
// 割り込み ライブラリ
// ======================================================================
// 
// * interrupt_init();
//   割り込みの初期化。
//   ポート別の割り込み設定をする前に、呼び出す必要がある。
//
// * interrupt_start(ポート, ポート番号, 関数)
//   割り込みを開始する。
//   呼び出される関数は、引数と戻り値を持ってはいけない。
//   
//   例:
//      // PB4 で割り込みが発生したら、func を呼び出す。
//      interrupt_start(&PORTB, 4, func);
//
// * interrupt_start_ex
//   割り込みを開始する。
//   割り込みレベルなど、詳細な設定が可能。
//   使用方法はソースコードを参照。
//
// ======================================================================
//
// * v1.0 (2012/03/30 8:05)
//   初版
//
// ======================================================================
// 動作確認環境: ATxmega128D3 @ 32 MHz
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

// 割り込み初期化
void interrupt_init(void){

	// レベル別 割り込み許可
	PMIC.CTRL = PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	
	// 全体割り込み許可
	sei();
	
	// マイコン別初期化
	interrupt_init_impl();
}

// 割り込み開始
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
	
	// ポート割り込み許可
	port->INTCTRL |= intctrl[int_num][(uint8_t)level];
	
	// 割り込みポート番号指定
	if(int_num == 0){
		port->INT0MASK |= _BV(num);
	}
	
	else {
		port->INT1MASK |= _BV(num);
	}
	
	interrupt_start_ex_impl(port, num, int_num, func);
}

// 割り込み開始
void interrupt_start(
	volatile PORT_t * const port,
	volatile const uint8_t num,
	void (*func)(void))
{
	interrupt_start_ex(port, num, InterruptMiddle, 0, func);
}

#endif