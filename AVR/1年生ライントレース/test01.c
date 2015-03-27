#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	
	// �|�[�g�̓��o�͂̐ݒ�
	DDRB = 0xff;
	DDRC = 0b11000001;
	DDRD = 0xff;

	// PWM �̐ݒ�

	// OCR0A, OCR0B �̐ݒ�
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000011;

	// OCR2A, OCR2B �̐ݒ�
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000011;
	
	// ���C���̏���
	while(1){
		if(PINC == 0b00001000){
		
			OCR0A = 0;
			OCR2A = 200;

			OCR0B = 0;
			OCR2B = 200;
		}
		else{
			OCR0A = 100;
			OCR2A = 0;

			OCR0B = 0;
			OCR2B = 100;
		}
	}

	return 0;
}
