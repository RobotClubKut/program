// ======================================================================
// xkvr (XMEGA KUT AVR Library) / base.h / v1.0 (2012/03/30 8:05)
// �x�[�X���C�u����
// ======================================================================
// ����m�F��: ATxmega128D3 @ 32 MHz
// ======================================================================

#ifndef __XKVR_BASE__
#define __XKVR_BASE__

#define XKVR_BASE_VERSION 10000UL // version 1.00.00

// F_CPU ����`����Ă��Ȃ��ꍇ�A�x�����o��
#ifndef F_CPU
#error "F_CPU is not defined."
#endif

// 32 MHz �łȂ��ꍇ�x�����o��
#if F_CPU != 32000000UL
#error "Only a clock of 32MHz is supported."
#endif

// ATxmegaD3
#if defined(__AVR_ATxmega16D4__)  || \
	defined(__AVR_ATxmega32D4__)  || \
	defined(__AVR_ATxmega64D3__)  || \
	defined(__AVR_ATxmega128D3__) || \
	defined(__AVR_ATxmega192D3__) || \
	defined(__AVR_ATxmega256D3__)
#define XKVR_BASE_D3
#endif

#endif