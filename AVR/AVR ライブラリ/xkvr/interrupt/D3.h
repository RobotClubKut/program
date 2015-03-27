// ======================================================================
// xkvr (XMEGA KUT AVR Library) / interrupt/D3.h / v1.0
// 割り込み ライブラリ (xmegaD3 系実装)
// ======================================================================
// 使用方法については、xkvr/interrupt.h を参照
// ======================================================================
//
// * v1.0 (2012/03/30 7:53)
//   初版
//
// ======================================================================


#ifndef __XKVR_INTERRUPT_D3__
#define __XKVR_INTERRUPT_D3__


// ----------------------------------------------------------------------
// * 内部変数
// ----------------------------------------------------------------------

// 割り込みで呼び出す関数
static void (* volatile interrupt_func_porta[16])(void); // PORTA
static void (* volatile interrupt_func_portb[16])(void); // PORTB
static void (* volatile interrupt_func_portc[16])(void); // PORTC
static void (* volatile interrupt_func_portd[16])(void); // PORTD
static void (* volatile interrupt_func_porte[16])(void); // PORTE
static void (* volatile interrupt_func_portf[16])(void); // PORTF
static void (* volatile interrupt_func_portr[4])(void);  // PORTR


// ----------------------------------------------------------------------
// * 内部関数
// ----------------------------------------------------------------------

// 割り込みの初期化
static void interrupt_init_impl(void){
	int i;
	
	for(i = 0; i < 16; ++i){
		interrupt_func_porta[i] = NULL;
	}
	
	for(i = 0; i < 16; ++i){
		interrupt_func_portb[i] = NULL;
	}
	
	for(i = 0; i < 16; ++i){
		interrupt_func_portc[i] = NULL;
	}
	
	for(i = 0; i < 16; ++i){
		interrupt_func_portd[i] = NULL;
	}
	
	for(i = 0; i < 16; ++i){
		interrupt_func_porte[i] = NULL;
	}
	
	for(i = 0; i < 16; ++i){
		interrupt_func_portf[i] = NULL;
	}
	
	for(i = 0; i < 4; ++i){
		interrupt_func_portr[i] = NULL;
	}
}

// 割り込み開始
void interrupt_start_ex_impl(
	volatile PORT_t * const port,
	volatile const uint8_t num,
	volatile const uint8_t int_num,
	void (* volatile func)(void))
{
	if(port == &PORTA){ // PORTA
		interrupt_func_porta[int_num * 8 + num] = func;
	}
	
	else if(port == &PORTB){ // PORTB
		interrupt_func_portb[int_num * 8 + num] = func;
	}
	
	else if(port == &PORTC){ // PORTC
		interrupt_func_portc[int_num * 8 + num] = func;
	}
	
	else if(port == &PORTD){ // PORTD
		interrupt_func_portd[int_num * 8 + num] = func;
	}
	
	else if(port == &PORTE){ // PORTE
		interrupt_func_porte[int_num * 8 + num] = func;
	}
	
	else if(port == &PORTF){ // PORTF
		interrupt_func_portf[int_num * 8 + num] = func;
	}
	
	else { // PORTR
		interrupt_func_portr[int_num * 2 + num] = func;
	}
}

// ------------------------------------------------------------------
// * 割り込み処理
// ------------------------------------------------------------------

// PORTA INT0
ISR(PORTA_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTA.IN & _BV(i) && interrupt_func_porta[i] != NULL){
			interrupt_func_porta[i]();
		}
	}
}

// PORTA INT1
ISR(PORTA_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTA.IN & _BV(i) && interrupt_func_porta[i + 8] != NULL){
			interrupt_func_porta[i + 8]();
		}
	}
}

// PORTB INT0
ISR(PORTB_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTB.IN & _BV(i) && interrupt_func_portb[i] != NULL){
			interrupt_func_portb[i]();
		}
	}
}

// PORTB INT1
ISR(PORTB_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTB.IN & _BV(i) && interrupt_func_portb[i + 8] != NULL){
			interrupt_func_portb[i + 8]();
		}
	}
}

// PORTC INT0
ISR(PORTC_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTC.IN & _BV(i) && interrupt_func_portc[i] != NULL){
			interrupt_func_portc[i]();
		}
	}
}

// PORTC INT1
ISR(PORTC_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTC.IN & _BV(i) && interrupt_func_portc[i + 8] != NULL){
			interrupt_func_portc[i + 8]();
		}
	}
}

// PORTD INT0
ISR(PORTD_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTD.IN & _BV(i) && interrupt_func_portd[i] != NULL){
			interrupt_func_portd[i]();
		}
	}
}

// PORTD INT1
ISR(PORTD_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTD.IN & _BV(i) && interrupt_func_portd[i + 8] != NULL){
			interrupt_func_portd[i + 8]();
		}
	}
}

// PORTE INT0
ISR(PORTE_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTE.IN & _BV(i) && interrupt_func_porte[i] != NULL){
			interrupt_func_porte[i]();
		}
	}
}

// PORTE INT1
ISR(PORTE_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTE.IN & _BV(i) && interrupt_func_porte[i + 8] != NULL){
			interrupt_func_porte[i + 8]();
		}
	}
}

// PORTF INT0
ISR(PORTF_INT0_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTF.IN & _BV(i) && interrupt_func_portf[i] != NULL){
			interrupt_func_portf[i]();
		}
	}
}

// PORTF INT1
ISR(PORTF_INT1_vect){
	int i;
	
	for(i = 0; i < 8; ++i){
		if(PORTF.IN & _BV(i) && interrupt_func_portf[i + 8] != NULL){
			interrupt_func_portf[i + 8]();
		}
	}
}

// PORTR INT0
ISR(PORTR_INT0_vect){
	int i;
	
	for(i = 0; i < 2; ++i){
		if(PORTR.IN & _BV(i) && interrupt_func_portr[i] != NULL){
			interrupt_func_portr[i]();
		}
	}
}

// PORTR INT1
ISR(PORTR_INT1_vect){
	int i;
	
	for(i = 0; i < 2; ++i){
		if(PORTR.IN & _BV(i) && interrupt_func_portr[i + 2] != NULL){
			interrupt_func_portr[i + 2]();
		}
	}
}

#endif