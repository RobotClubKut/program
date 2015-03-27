// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Analog Digital Converter Library / "kvr/adc.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   ����
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
	ADCSRA = 0; // 1 MHz / 1 ���� = 1 MHz
#elif F_CPU == 8000000UL // 8 MHz
	ADCSRA = _BV(ADPS1) | _BV(ADPS0); // 8 MHz / 8 ���� = 1 MHz
#elif F_CPU == 20000000UL // 20 MHz
	ADCSRA = _BV(ADPS2) | _BV(ADPS0); // 20 MHz / 32 ���� = 625 kHz
#endif
	
	ADMUX   = 0; // ��d�� AREF
	ADCSRA |= _BV(ADEN) | _BV(ADSC); // AD �ϊ��L�� & AD �ϊ�����J�n
	
	// ����ϊ��̏I����҂�
	loop_until_bit_is_set(ADCSRA,ADIF);
}

uint16_t adc_convert(volatile const uint8_t pin){
	
	ADMUX = pin; // AD �ϊ��s�����w��
	
	// �ϊ��J�n
	ADCSRA &= ~_BV(ADIF);
	ADCSRA |=  _BV(ADSC);
	
	// �ϊ������܂ő҂�
	loop_until_bit_is_set(ADCSRA, ADIF);
	
	// ���ʂ�Ԃ�
	return ADC;
}

#endif
