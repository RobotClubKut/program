#define F_CPU 8000000

#include "kvr/usart.h"
#include "kvr/adc.h"

#include <avr/io.h>
#include <util/delay.h>

#define DEBUG 0

#define r_b_motor	OCR0A
#define r_f_motor	OCR0B
#define l_b_motor	OCR2A
#define l_f_motor	OCR2B

int IIR(int n,char p){
	static int z[4][15]={0};//処理の後に代入させる
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[3][15] = {0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1][p] << 8) * a2;
	a1 = (z[0][p] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3][p] << 8) * b2;
	b1 = (z[2][p] << 8) * b1;
	
	z[1][p] = z[0][p];
	z[0][p] = n >> 2;
	z[3][p] = z[2][p];
	z[2][p] = add[0][p];
	
	add[0][p] = add[1][p] + (a0 >> 4);
	add[0][p] = add[0][p] >> 8;
	add[1][p] = (a1 >> 4) + b1 + add[2][p];
	add[2][p] = (a2 >> 4) - b2;
	
	return add[0][p];
}

void adc(int *a,int *b){
	*a = adc_convert(1) >> 1;
	*b = adc_convert(2) >> 1;
}

void go_st(int n){
	r_f_motor = n;
	l_f_motor = n;
	r_b_motor = 0x00;
	l_b_motor = 0x00;
	
	return;
}

void lt_right(int n){
	r_f_motor = n/2;
	l_f_motor = n;
	r_b_motor = 0x00;
	l_b_motor = 0x00;
	
	return;
}

void lt_left(int n){
	r_f_motor = n;
	l_f_motor = n/2;
	r_b_motor = 0x00;
	l_b_motor = 0x00;
	
	return;
}

void roll_left(void){
	r_f_motor = 0x00;
	l_f_motor = 0xff;
	r_b_motor = 0xff;
	l_b_motor = 0x00;
	
	return;
}

void roll_left(void){
	r_f_motor = 0xff;
	l_f_motor = 0x00;
	r_b_motor = 0x00;
	l_b_motor = 0xff;
	
	return;
}

void MCU_init(void){
	int adc_1 = 0;	
	// ポートの入出力の設定
	DDRB = 0xff;
	DDRC = 0b11111001;
	DDRD = 0xff;

	// PWM の設定

	// OCR0A, OCR0B の設定
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000011;

	// OCR2A, OCR2B の設定
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000011;

	usart_init(0,9600);
	usart_stdout(0);
	adc_init();
}

void debug_mode(void){
	while(DEBUG){
		_delay_ms(500);
		printf("1: %d\n",IIR(adc_convert(1) >> 1,1));
		printf("2: %d\n",IIR(adc_convert(2) >> 1,2));
	}
}

void move(void){
	int r,l;
	while(1){
		adc(&r,&l);
		
		if(r == l){//center
			go_st(0xff);
		}
		else if(l < r){//right
			lt_right(0xff);
		}
		else if(r > l){//left
			lt_left(0xff);
		}
		else{//conner
			if(r == 1){//right
				roll_right();
			}
			else if(l == 1){//left
				roll_left();
			}
		}
	}
	return;
}

int main(void){
	MCU_init();
	debug_mode();
	move();
	
	return 0;
}
