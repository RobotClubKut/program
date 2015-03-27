#define F_CPU 8000000

#include<avr/io.h>
#include<util/delay.h>

#define LTS PINC&_BV(0)	//���t�g�^�b�`�Z���T�[
#define FTSR PINC&_BV(1) //�O���^�b�`�Z���T�[�E
#define FTSL PINC&_BV(2) //�O���^�b�`�Z���T�[��


void return{//xmega�ւ�return����
	DDRB |= 0x04;
	PORTB |= 0x04;//PB2
}

void s_fnc0(){//���t�g�Z���T�[�̔�����
	DDRB |= 0x18;
	if(LTS){
	}
	else if(FTSR || FTSL){//�ǂ��炩�̌X�������m������
		if(!FTSR)
		if(!FTSL)
	}
}


void lift0(int f,int b){//f�� b��
	if(f == 0 && b == 0){
		PORTB |= 0x01;
	}
	else{
		PORTB = 0x00;
		OCR0A = f;
		OCR0B = b;
	}
}

void lift1(int f,int b){//f�O b���
	if(f == 0 && b == 0){
		PORTB |= 0x02;
	}
	else{
		PORTB = 0x00;
		OCR2A = f;
		OCR2B = b;
	}
}

void mode0(){
}
void mode1(){
}
void mode2(){
}
void mode3(){
}
void mode4(){
}
void mode5(){
}
void mode6(){
}
void mode7(){
}

void pwm_set(){
	TCCR0A = 0b10100011;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0b00000001;
	TCCR1A = 0;  	  // OCR1A OCR1B �̐ݒ�
	TCCR1B = 3;
	TCCR2A = 0b10100011;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0b00000001;
	DDRD |= 0xf0;
	DDRB |= 0x18;
}

void pwm_reset(){
	TCCR0A = 0;  // OCR0A OCR0B �̐ݒ�
	TCCR0B = 0;
	TCCR1A = 0;  	  // OCR1A OCR1B �̐ݒ�
	TCCR1B = 0;
	TCCR2A = 0;  // OCR2A OCR2B �̐ݒ�
	TCCR2B = 0;
}

void dis_init(){
	DDRB |= 0x03;
}

void dis(){
	PORTB |= 0x03;
}

void init(){
	dis_init();
	pwm_set();
}

void main(){
	DDRB = 0xff;
	DDRD = 0xff;
	DDRA = 0x00;
	DDRC = 0x00;
	while(1){
		if(PINA == 0x00){
			mode0();
		}
		else if(PINA == 0x01){
			mode1();
		}
		else if(PINA == 0x02){
			mode2();
		}
		else if(PINA == 0x03){
			mode3();
		}
		else if(PINA == 0x04){
			mode4();
		}
		else if(PINA == 0x05){
			mode5();
		}
		else if(PINA == 0x06){
			mode6();
		}
		else if(PINA == 0x07){
			mode7();
		}
	}

}
