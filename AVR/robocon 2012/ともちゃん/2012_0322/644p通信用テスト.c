#define F_CPU 8000000

#include<avr/io.h>
#include<util/delay.h>

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

void s_return(){
	if(PINB == 0x00){
		PORTB = 0x00;
	}
	else if(PINB == 0x01){
		PORTB = 0x01*8;
		while(PINB == 0x01)_delay_ms(10);
	}
	else if(PINB == 0x02){
		PORTB = 0x02*8;
		while(PINB == 0x02)_delay_ms(10);
	}
	else if(PINB == 0x03){
		PORTB = 0x03*8;
		while(PINB == 0x03)_delay_ms(10);
	}
	else if(PINB == 0x04){
		PORTB = 0x04*8;
		while(PINB == 0x04)_delay_ms(10);
	}
	else if(PINB == 0x05){
		PORTB = 0x05*8;
		while(PINB == 0x05)_delay_ms(10);
	}
	else if(PINB == 0x06){
		PORTB = 0x06*8;
		while(PINB == 0x06)_delay_ms(10);
	}
	else if(PINB == 0x07){
		PORTB = 0x07*8;
		while(PINB == 0x07)_delay_ms(10);
	}
}


void main(){
	DDRB = 0b11111000;
	DDRD = 0xff;
	DDRA = 0x00;
	DDRC = 0x00;
	while(1){
		PORTB = 0x00;
		s_return();
	}

}
