#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static int timer0_count = 0;
static int timer2_count = 0;

void servo_init(void)
{
//	servo0x_init();
	servo1x_init();
//	servo2x_init();
}
void servo1x_init(void)
{
	//OCR1A,OCR1B (16bit)�̐ݒ�
	TCCR1A = 0b10100010;	//����PWM(TOP�l = ICR1)
							//��r��v��Low�ABOTTOM(TCNT = 0)��High
	TCCR1B = 0b00011010;	//8����
	ICR1 = 20000;			//TCNT = 20000��TCNT = 0
}
void servo1b_set(int32_t angle_deg)
{
	OCR1B = 25*angle_deg/3+1000;
}
void servo1a_set(int32_t angle_deg)
{
	OCR1A = 25*angle_deg/3+1000;
}
/*
//�^�C�}0�I�[�o�[�t���[���荞��
ISR(TIMER0_OVF_vect)
{
	if(timer0_count < 4)
	{
		TCNT0 = OCR0B-1;
		timer0_count++;
		_delay_us(65);
		TCNT0 = 131;
	}
	else
	{
		timer0_count = 0;
	}
}

//servo0x�������֐�
void servo0x_init(void)
{
	//OCR0A,OCR0B �̐ݒ�
	TCCR0A = 0b10100011;	//8�r�b�g����PWM
	TCCR0B = 0b00000100;	//256����

	TIMSK0 = 0b00000001;	//�^�C�}0�I�[�o�[�t���[���荞�݋���
	//sei();
}
void servo0b_set(int32_t angle_deg)
{
	OCR0B = 31.25*angle_deg/120+31.25;
}

void servo0a_set(int32_t angle_deg)
{
	OCR0A = 31.25*angle_deg/120+31.25;
}

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
	//sei();
}
void servo2b_set(int32_t angle_deg)
{
	OCR2B = 31.25*angle_deg/120+31.25;
}

void servo2a_set(int32_t angle_deg)
{
	OCR2A = 31.25*angle_deg/120+31.25;
}
*/
