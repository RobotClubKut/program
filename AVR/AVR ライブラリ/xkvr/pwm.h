// ======================================================================
// xkvr (XMEGA KUT AVR Library) / pwm.h / v1.1
// PWM ライブラリ
// ======================================================================
//
// * PWM の初期化
//   第一引数には、&TCC0, &TCC1, &TCD0, &TCE0, &TCF0 のどれかを指定します。
//   第二引数には、PWM を有効にするポートを4 ビットで指定します。
//   (0b1100 -> CD 有効, 0b1111 -> ABCD 有効)
//   
//   分周には、次のどれかを指定してください。
//   
//   * 1 分周 (分周なし; 125 kHz)
//   * 2 分周 (62.5 kHz)
//   * 4 分周 (30 kHz)
//   * 8 分周 (15 kHz)
//   * 64 分周 (2 kHz)
//   * 256 分周 (500 Hz)
//   * 1024 分周 (125 Hz)
//
//   void pwm_init(PWM のポートのアドレス, PWM 分周, 有効ポート);
//   
//   例:
//      pwm_init(&TCC0, 64, 0b1111);
//
// ======================================================================
// 
// * v1.0
//   初版。
//
// * v1.1 (2012/03/31 22:46)
//   PWM 分周を指定できるように使用変更。
//   過去バージョンとの互換性無し。
//
// ======================================================================
// 動作確認環境: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_PWM__
#define __XKVR_PWM__

// 32 MHz でない場合警告を出す
#if F_CPU != 32000000UL
#error "Only a clock of 32MHz is supported."
#endif

#define XKVR_PWM_VERSION 10100UL // version 1.01.00

#include <avr/io.h>

#include "base.h"

#if defined(XKVR_BASE_D3)
#include "pwm/D3.h"
#else
#error "This microcomputer is not supported."
#endif

void pwm_init(void * const tc, const uint16_t clk, const uint8_t pin){
	pwm_init_impl(tc, clk, pin);
}

#endif

// vim: se noet ts=4 sw=4 sts=0 ft=c :
