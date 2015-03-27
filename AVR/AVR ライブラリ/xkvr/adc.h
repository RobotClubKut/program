// ======================================================================
// xkvr (XMEGA KUT AVR Library) / adc.h / v1.0.1
// AD �ϊ� ���C�u����
// ======================================================================
//
// �� AD �ϊ��̏�����
//    AD �ϊ��r�b�g���� 1�`12 �̐����Ŏw�肷��B
//    AREFA ����d���Ƃ���B
//
//    adc_init(AD �ϊ��r�b�g��);
//
// �� AD �ϊ�
//    AD �ϊ�������|�[�g�� 1�`15 �̐����ŕ\�� (ADC* �ɑΉ�)�B
//    ADC0 �� AREFA (��d��) �Ƃ��Ďg�p���Ă��邽�߁A�g�p�s�B
//
//    adc_convert(AD �ϊ��|�[�g);
//
// ======================================================================
// 
// * v1.0
//   ���ŁB
//
// * v1.0.1 (2012/03/30 17:07)
//   �A���� AD �ϊ�������ƁA�l������Ɏ��Ȃ��o�O���C���B
//   ���ʃw�b�_�t�@�C�� "xkvr/base.h" ��p����悤�ɕύX�B
//
// ======================================================================
// ����m�F��: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_ADC__
#define __XKVR_ADC__

#include <stddef.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/version.h>

#include "base.h"

// �o�[�W����
#define XKVR_ADC_VERSION 10001UL // version 1.00.01

// avr-libc 1.6.7 �ɂ̓o�O�����݂���B
// AD �ϊ��̃��W�X�^�̃������A�h���X���Ⴄ���߁AAD �ϊ������삵�Ȃ��B
// ���̂��߁AAD �ϊ��Ŏg�����W�X�^���ēx��`���Ă����B
// http://savannah.nongnu.org/bugs/?28574

#if __AVR_LIBC_VERSION__ <= 10607UL // <= 1.6.7
#if defined(XKVR_BASE_D3)

/* Analog-to-Digital Converter */
typedef struct ADC2_struct
{
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t REFCTRL;  /* Reference Control */
    register8_t EVCTRL;  /* Event Control */
    register8_t PRESCALER;  /* Clock Prescaler */
    register8_t reserved_0x05;
    register8_t INTFLAGS;  /* Interrupt Flags */
    register8_t reserved_0x07;
    register8_t reserved_0x08;
    register8_t reserved_0x09;
    register8_t reserved_0x0A;
    register8_t reserved_0x0B;
    _WORDREGISTER(CAL);  /* Calibration Value */
    register8_t reserved_0x0E;
    register8_t reserved_0x0F;
    _WORDREGISTER(CH0RES);  /* Channel 0 Result */
    register8_t reserved_0x12;
    register8_t reserved_0x13;
    register8_t reserved_0x14;
    register8_t reserved_0x15;
    register8_t reserved_0x16;
    register8_t reserved_0x17;
    _WORDREGISTER(CMP);  /* Compare Value */
    register8_t reserved_0x1A;
    register8_t reserved_0x1B;
    register8_t reserved_0x1C;
    register8_t reserved_0x1D;
    register8_t reserved_0x1E;
    register8_t reserved_0x1F;
    ADC_CH_t CH0;  /* ADC Channel 0 */
} ADC2_t;

#undef ADCA
#define ADCA    (*(ADC2_t *) 0x0200)  /* Analog to Digital Converter A */

#endif
#endif

// AD �ϊ� �r�b�g��
uint8_t adc_bit;

// �X���f�[�^��ǂݍ���
uint16_t adc_read_cal(void);

// AD �ϊ��̏�����
void adc_init(const uint8_t bit){
	
	if(bit > 12){ // �͈͊O
		adc_bit = 12;
	}
	
	else {
		adc_bit = bit;
	}
	
	if(bit <= 8){
		ADCA.CTRLB = ADC_RESOLUTION_8BIT_gc; // 8 �r�b�g�E����
	}
	
	else {
		ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc; // 12 �r�b�g�E����
	}
	
	// AD �ϊ��̍X������ǂݍ���
	ADCA.CAL = adc_read_cal(); 
	
	// AD �ϊ��̐ݒ�
	ADCA.CTRLA     = ADC_ENABLE_bm; // AD �ϊ���L���ɂ���
	ADCA.REFCTRL   = ADC_REFSEL_AREFA_gc; // ��d�� AREFA
	ADCA.PRESCALER = ADC_PRESCALER_DIV16_gc; // 16 ���� (32 MHz / 16 = 2 MHz)
	ADCA.CH0.CTRL  = ADC_CH_INPUTMODE_SINGLEENDED_gc; // �V���O���G���h����
}

// AD �ϊ��̒l�̎擾
uint16_t adc_convert(const uint8_t pin){
	ADCA.CH0.MUXCTRL  = pin << 3; // �ԍ� (ADC*)
	ADCA.CH0.CTRL    |= ADC_CH_START_bm; // AD �ϊ����J�n
	
	// �ϊ��I����҂�
	loop_until_bit_is_set(ADCA.CH0.INTFLAGS, ADC_CH_CHIF_bp);
	
	// �ϊ������t���O���N���A
	ADCA.CH0.INTFLAGS |= ADC_CH_CHIF_bm;
	
	if(adc_bit <= 8){
		return ADCA.CH0.RES >> (8 - adc_bit);
	}
	
	else {
		return ADCA.CH0.RES >> (12 - adc_bit);
	}
}

// �X������ǂݍ���
uint16_t adc_read_cal(void){ 
	uint16_t cal;
	
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	
	cal = pgm_read_word(PROD_SIGNATURES_START + offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
	
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	
	return cal;
}

#endif

// vim: se noet ts=4 sw=4 sts=4 ft=c :
