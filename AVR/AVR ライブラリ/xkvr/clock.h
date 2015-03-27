// ======================================================================
// xkvr (XMEGA KUT AVR Library) / clock.h / v1.1
// ����N���b�N�ݒ胉�C�u����
// ======================================================================
//
// * ���� 32MHz ���U�q�œ��삳����
//
//   void clock_internal_init();
//
// * �O���N���b�N�œ��삳����
//   8 MHz �Z�����b�N�� 4 �{�œ��삳���� (8 MHz x4 = 32 MHz)�B
//
//   void clock_external_init();
//
// ======================================================================
// 
// * v1.0
//   ���ŁB
//
// * v1.1
//   ���� 32 MHz ���U��� DFLL (�Z���@�\) �𗘗p����悤�ɕύX�B
//
// ======================================================================
// ����m�F��: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_CLOCK__
#define __XVKR_CLOCK__

// �o�[�W����
#define XKVR_VERSION 10100UL // version 1.01.00

#include <avr/io.h>

// ���� 32MHz ���U��œ��삳����
void clock_internal_init(void){
    
    // ���� 32 MHz / 32.768 kHz ���U�������
	// 32.768 kHz ���U��� DFLL �Ŏg�p
    OSC.CTRL |= OSC_RC32KEN_bm | OSC_RC32MEN_bm;
    
    // ���M�킪���肷��܂ő҂�
    loop_until_bit_is_set(OSC.STATUS, OSC_RC32KRDY_bp);
    loop_until_bit_is_set(OSC.STATUS, OSC_RC32MRDY_bp);
	
	// DFLL ��������
	DFLLRC32M.CTRL = DFLL_ENABLE_bm;
    
    // �N���b�N����� 32 MHz �N���b�N�ɐݒ�
    CPU_CCP  = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	
	// �N���b�N�ݒ��ύX�s�ɂ���
	CPU_CCP  = CCP_IOREG_gc;
	CLK.LOCK = CLK_LOCK_bm;
}

// �O���N���b�N�œ��삳����
// 8 MHz ���U�q x4 = 32 MHz
void clock_external_init(void){
    
    // �O���N���b�N�̐ݒ�
    // 2 - 12 MHz �N���X�^�� & �n������ 1K CLK
	// �Z���~�b�N���U�q�́A�n������ 1K CLK ���g�p���邱�� (��������)
    OSC.XOSCCTRL = OSC_FRQRANGE_2TO9_gc | OSC_XOSCSEL_XTAL_1KCLK_gc;
	
    // �O�����M�������
    OSC.CTRL |= OSC_XOSCEN_bm;
    
    // �O�����M�킪���肷��܂ő҂�
    loop_until_bit_is_set(OSC.STATUS, OSC_XOSCRDY_bp);
    
    // PLL �̐ݒ�
    // PLL ������ = �O���N���b�N & �{�� x4
    OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 4;
    
    // PLL ������
    OSC.CTRL |= OSC_PLLEN_bm;
    
    // PLL �����肷��܂ő҂�
    loop_until_bit_is_set(OSC.STATUS, OSC_PLLRDY_bp);
    
    // �N���b�N�� PLL �ɐݒ�
    CPU_CCP  = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_PLL_gc;
	
	// �N���b�N�ݒ��ύX�s�ɂ���
	CPU_CCP  = CCP_IOREG_gc;
	CLK.LOCK = CLK_LOCK_bm;
}

#endif

// vim: se noet ts=4 sw=4 sts=0 ft=c :
