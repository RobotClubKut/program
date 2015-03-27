// ======================================================================
// xkvr (XMEGA KUT AVR Library) / adc.h / v1.0.1
// AD 変換 ライブラリ
// ======================================================================
//
// ■ AD 変換の初期化
//    AD 変換ビット数は 1～12 の整数で指定する。
//    AREFA を基準電圧とする。
//
//    adc_init(AD 変換ビット数);
//
// ■ AD 変換
//    AD 変換をするポートは 1～15 の整数で表す (ADC* に対応)。
//    ADC0 は AREFA (基準電圧) として使用しているため、使用不可。
//
//    adc_convert(AD 変換ポート);
//
// ======================================================================
// 
// * v1.0
//   初版。
//
// * v1.0.1 (2012/03/30 17:07)
//   連続で AD 変換をすると、値が正常に取れないバグを修正。
//   共通ヘッダファイル "xkvr/base.h" を用いるように変更。
//
// ======================================================================
// 動作確認環境: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_ADC__
#define __XKVR_ADC__

#include <stddef.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/version.h>

#include "base.h"

// バージョン
#define XKVR_ADC_VERSION 10001UL // version 1.00.01

// avr-libc 1.6.7 にはバグが存在する。
// AD 変換のレジスタのメモリアドレスが違うため、AD 変換が動作しない。
// そのため、AD 変換で使うレジスタを再度定義しておく。
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

// AD 変換 ビット数
uint8_t adc_bit;

// 更正データを読み込む
uint16_t adc_read_cal(void);

// AD 変換の初期化
void adc_init(const uint8_t bit){
	
	if(bit > 12){ // 範囲外
		adc_bit = 12;
	}
	
	else {
		adc_bit = bit;
	}
	
	if(bit <= 8){
		ADCA.CTRLB = ADC_RESOLUTION_8BIT_gc; // 8 ビット右揃え
	}
	
	else {
		ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc; // 12 ビット右揃え
	}
	
	// AD 変換の更正情報を読み込む
	ADCA.CAL = adc_read_cal(); 
	
	// AD 変換の設定
	ADCA.CTRLA     = ADC_ENABLE_bm; // AD 変換を有効にする
	ADCA.REFCTRL   = ADC_REFSEL_AREFA_gc; // 基準電圧 AREFA
	ADCA.PRESCALER = ADC_PRESCALER_DIV16_gc; // 16 分周 (32 MHz / 16 = 2 MHz)
	ADCA.CH0.CTRL  = ADC_CH_INPUTMODE_SINGLEENDED_gc; // シングルエンド入力
}

// AD 変換の値の取得
uint16_t adc_convert(const uint8_t pin){
	ADCA.CH0.MUXCTRL  = pin << 3; // 番号 (ADC*)
	ADCA.CH0.CTRL    |= ADC_CH_START_bm; // AD 変換を開始
	
	// 変換終了を待つ
	loop_until_bit_is_set(ADCA.CH0.INTFLAGS, ADC_CH_CHIF_bp);
	
	// 変換完了フラグをクリア
	ADCA.CH0.INTFLAGS |= ADC_CH_CHIF_bm;
	
	if(adc_bit <= 8){
		return ADCA.CH0.RES >> (8 - adc_bit);
	}
	
	else {
		return ADCA.CH0.RES >> (12 - adc_bit);
	}
}

// 更正情報を読み込む
uint16_t adc_read_cal(void){ 
	uint16_t cal;
	
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	
	cal = pgm_read_word(PROD_SIGNATURES_START + offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));
	
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	
	return cal;
}

#endif

// vim: se noet ts=4 sw=4 sts=4 ft=c :
