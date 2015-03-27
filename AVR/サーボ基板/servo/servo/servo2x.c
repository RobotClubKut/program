#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include"servo.h"
static int timer2_count = 0;

//�^�C�}2�I�[�o�[�t���[���荞��
ISR(TIMER2_OVF_vect)
{
	if(timer2_count < 4)
	{
		TCNT2 = OCR2B-1;
		timer2_count++;
		_delay_us(65);
		TCNT2 = 131;
	}
	else
	{
		timer2_count = 0;
	}
}

//servo2x�������֐�
void servo2x_init(void)
{
	//OCR2A,OCR2B �̐ݒ�
	TCCR2A = 0b10100011;	//8�r�b�g����PWM
	TCCR2B = 0b00000110;	//256����

	TIMSK2 = 0b00000001;	//�^�C�}0�I�[�o�[�t���[���荞�݋���
	sei();
}
void servo2b_set(int32_t angle_deg)
{
	OCR2B = 31.25*angle_deg/120+31.25;
}

void servo2a_set(int32_t angle_deg)
{
	OCR2A = 31.25*angle_deg/120+31.25;
}
