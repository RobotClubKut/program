// ======================================================================
// xkvr (XMEGA KUT AVR Library) / pwm/D3.h / v1.0
// PWM ���C�u���� (xmegaD3 �n����)
// ======================================================================
// �g�p���@�ɂ��ẮAxkvr/pwm.h ���Q��
// ======================================================================
//
// * v1.0 (2012/03/31 22:48)
//   ����
//
// ======================================================================

#ifndef __XKVR_PWM_D3__
#define __XKVR_PWM_D3__

#define XKVR_PWM_D3_VERSION 10000UL // version 1.00.00

void pwm_init_impl(
	void * const tc,
	const uint16_t clk,
	const uint8_t pin)
{
	uint8_t clksel;
	
	clksel =
		clk ==   1 ? TC_CLKSEL_DIV1_gc   :
		clk ==   2 ? TC_CLKSEL_DIV2_gc   :
		clk ==   4 ? TC_CLKSEL_DIV4_gc   :
		clk ==   8 ? TC_CLKSEL_DIV8_gc   :
		clk ==  64 ? TC_CLKSEL_DIV64_gc  :
		clk == 256 ? TC_CLKSEL_DIV256_gc :
		             TC_CLKSEL_DIV1024_gc;
	
	// TCC0 (�|�[�gC; OC0A, OC0B, OC0C, OC0D) �̐ݒ�
	if(tc == &TCC0){
		TCC0.PER   = 0x00ff; // ���܂��Ȃ�
		TCC0.CTRLA = clksel;
		TCC0.CTRLB = TC_WGMODE_SS_gc | (pin << 4); // �g�` & �L���|�[�g�̐ݒ�
	}
	
	// TCC1 (�|�[�gC; OC1A, OC1B) �̐ݒ�
	else if(tc == &TCC1){
		TCC1.PER   = 0x00ff; // ���܂��Ȃ�
		TCC1.CTRLA = clksel;
		TCC1.CTRLB = TC_WGMODE_SS_gc | (pin << 4); // �g�` & �L���|�[�g�̐ݒ�
	}
	
	// TCD0 (�|�[�gD; OC0A, OC0B, OC0C, OC0D) �̐ݒ�
	else if(tc == &TCD0){
		TCD0.PER   = 0x00ff; // ���܂��Ȃ�
		TCD0.CTRLA = clksel;
		TCD0.CTRLB = TC_WGMODE_SS_gc | (pin << 4); // �g�` & �L���|�[�g�̐ݒ�
	}
	
	// TCE0 (�|�[�gE; OC0A, OC0B, OC0C, OC0D) �̐ݒ�
	else if(tc == &TCE0){
		TCE0.PER   = 0x00ff; // ���܂��Ȃ�
		TCE0.CTRLA = clksel;
		TCE0.CTRLB = TC_WGMODE_SS_gc | (pin << 4); // �g�` & �L���|�[�g�̐ݒ�
	}
	
	// TCF0 (�|�[�gF; OC0A, OC0B, OC0C, OC0D) �̐ݒ�
	else {
		TCF0.PER   = 0x00ff; // ���܂��Ȃ�
		TCF0.CTRLA = clksel;
		TCF0.CTRLB = TC_WGMODE_SS_gc | (pin << 4); // �g�` & �L���|�[�g�̐ݒ�
	}
}

#endif
