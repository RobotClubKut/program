// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Analog Digital Converter Library / "kvr/adc.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   初版
//
// ------------------------------------------------------------------
// * 対応マイコン
//
//   - 28 PIN
//     ATmega48/48A/48P/88/88A/88P/88PA/168/168A/168P/328/328P
//
//   - 40 PIN
//     ATmega164P/164A/324P/324A/324PA/644/644P/644A/644PA/1284P
//
// ------------------------------------------------------------------

#ifndef __KVR_ADC__
#define __KVR_ADC__

#define KVR_ADC_VERSION 10000UL // version 1.00.00

#include <stdint.h>
#include <avr/io.h>

#include "base.h"

void     adc_init(void);
uint16_t adc_convert(volatile const uint8_t pin);

void adc_init(void){

#if F_CPU == 1000000UL // 1 MHz
	ADCSRA = 0; // 1 MHz / 1 分周 = 1 MHz
#elif F_CPU == 8000000UL // 8 MHz
	ADCSRA = _BV(ADPS1) | _BV(ADPS0); // 8 MHz / 8 分周 = 1 MHz
#elif F_CPU == 20000000UL // 20 MHz
	ADCSRA = _BV(ADPS2) | _BV(ADPS0); // 20 MHz / 32 分周 = 625 kHz
#endif
	
	ADMUX   = 0; // 基準電圧 AREF
	ADCSRA |= _BV(ADEN) | _BV(ADSC); // AD 変換有効 & AD 変換初回開始
	
	// 初回変換の終了を待つ
	loop_until_bit_is_set(ADCSRA,ADIF);
}

uint16_t adc_convert(volatile const uint8_t pin){
	
	ADMUX = pin; // AD 変換ピンを指定
	
	// 変換開始
	ADCSRA &= ~_BV(ADIF);
	ADCSRA |=  _BV(ADSC);
	
	// 変換完了まで待つ
	loop_until_bit_is_set(ADCSRA, ADIF);
	
	// 結果を返す
	return ADC;
}

#endif
