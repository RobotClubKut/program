// ======================================================================
// xkvr (XMEGA KUT AVR Library) / clock.h / v1.1
// 動作クロック設定ライブラリ
// ======================================================================
//
// * 内部 32MHz 発振子で動作させる
//
//   void clock_internal_init();
//
// * 外部クロックで動作させる
//   8 MHz セラロックを 4 倍で動作させる (8 MHz x4 = 32 MHz)。
//
//   void clock_external_init();
//
// ======================================================================
// 
// * v1.0
//   初版。
//
// * v1.1
//   内部 32 MHz 発振器に DFLL (校正機能) を利用するように変更。
//
// ======================================================================
// 動作確認環境: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_CLOCK__
#define __XVKR_CLOCK__

// バージョン
#define XKVR_VERSION 10100UL // version 1.01.00

#include <avr/io.h>

// 内部 32MHz 発振器で動作させる
void clock_internal_init(void){
    
    // 内部 32 MHz / 32.768 kHz 発振器を許可
	// 32.768 kHz 発振器は DFLL で使用
    OSC.CTRL |= OSC_RC32KEN_bm | OSC_RC32MEN_bm;
    
    // 発信器が安定するまで待つ
    loop_until_bit_is_set(OSC.STATUS, OSC_RC32KRDY_bp);
    loop_until_bit_is_set(OSC.STATUS, OSC_RC32MRDY_bp);
	
	// DFLL を許可する
	DFLLRC32M.CTRL = DFLL_ENABLE_bm;
    
    // クロックを内部 32 MHz クロックに設定
    CPU_CCP  = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	
	// クロック設定を変更不可にする
	CPU_CCP  = CCP_IOREG_gc;
	CLK.LOCK = CLK_LOCK_bm;
}

// 外部クロックで動作させる
// 8 MHz 発振子 x4 = 32 MHz
void clock_external_init(void){
    
    // 外部クロックの設定
    // 2 - 12 MHz クリスタル & 始動時間 1K CLK
	// セラミック発振子は、始動時間 1K CLK を使用すること (手引書より)
    OSC.XOSCCTRL = OSC_FRQRANGE_2TO9_gc | OSC_XOSCSEL_XTAL_1KCLK_gc;
	
    // 外部発信器を許可
    OSC.CTRL |= OSC_XOSCEN_bm;
    
    // 外部発信器が安定するまで待つ
    loop_until_bit_is_set(OSC.STATUS, OSC_XOSCRDY_bp);
    
    // PLL の設定
    // PLL 供給元 = 外部クロック & 倍率 x4
    OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 4;
    
    // PLL を許可
    OSC.CTRL |= OSC_PLLEN_bm;
    
    // PLL が安定するまで待つ
    loop_until_bit_is_set(OSC.STATUS, OSC_PLLRDY_bp);
    
    // クロックを PLL に設定
    CPU_CCP  = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_PLL_gc;
	
	// クロック設定を変更不可にする
	CPU_CCP  = CCP_IOREG_gc;
	CLK.LOCK = CLK_LOCK_bm;
}

#endif

// vim: se noet ts=4 sw=4 sts=0 ft=c :
