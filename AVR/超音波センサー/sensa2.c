#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h> 
#include <util/delay.h>

#include "kvr/usart.h"
#include "kvr/adc.h"



	int cnt=0, flag = 0;
    unsigned char seg[10]= {0b00010001, 0b11010111,
							0b00110010, 0b10010010,
							0b11010100, 0b10011000,
							0b00011000, 0b11010001,
							0b00010000, 0b10010000};



ISR ( TIMER2_COMPA_vect ){
    static unsigned char sel=0;
    unsigned char dig1, dig10, dig100, dig1000;
//    static unsigned int i;

	    dig1    = seg[cnt % 10];
	    dig10   = seg[(cnt / 10) % 10];
	    dig100  = seg[(cnt / 100) % 10];
	    dig1000  = seg[(cnt / 1000) % 10];


    switch(sel){
        case 0: PORTD = 0b00100000;
                PORTB = dig1;
                break;
        case 1: PORTD = 0b00010000;
                PORTB = dig10;
                break;
        case 2: PORTD = 0b00001000;
                PORTB = dig100;
                break;
		case 3: PORTD = 0b00000100;
                PORTB = dig1000;
                break;
    }
    sel++;
    if(sel == 4){

		sel = 0;

	}

	
//		i++;
//		if(i == 1000){ cnt++; i = 0; }


}


ISR(PCINT2_vect, ISR_NOBLOCK){
	
	if(PINC & _BV(0)){
		// チャタリング防止

		while(1){
			if(!(PINC & _BV(0))){
				_delay_ms(10);

				if(!(PINC & _BV(0))){
					break;
				}
			}
		}

		if(flag == 0){
			flag = 1;
		}
		else if(flag == 1){
			flag = 2;
		}
		else if(flag == 2){
			flag = 0;
		}

	}

}


int onpa(){

//16bit timer設定
	TCCR1A = 0;
	TCCR1B = 3;	//3なので64分周

	double t, c;
	int n;
	int cnt, kyori;

		_delay_ms(15);

		DDRC = 0b10000000;
		PORTC |= _BV(7);
		_delay_ms(1);
		PORTC &= ~_BV(7);
		cnt = 0;
		DDRC = 0b00000000;

		while(!(PINC & _BV(7))){
			TCNT1 = 0;
		
		}
	
		while(PINC & _BV(7)){}

		n = TCNT1;

		printf("%d\n", n);


//時間
//	t = n * 0.00694;

//音速
//	c = 331.5 * ((273 + ondo()) / 273);
//	c = 331.5 + 0.6 * ondo();

	kyori = n/7.8;
//距離
//	kyori = c * 100 * t / 2;
	printf("c = %d\n", kyori);

	return kyori;






}


int ondo(){

	int i, namadeta[30], deta10 = 0;
	int vint, temperature, deta;

		// AD 変換 10回読み込み
		for(i = 0; i < 25; i++){

			namadeta[i] = adc_convert(0);

//			printf("[i] = %d ", namadeta[i]);

    	}

		//10回の平均値
		for(i = 0; i < 25; i++){

			deta10 = namadeta[i] + deta10;
//			printf("deta10 = %d ", deta10);

			deta = deta10 / 25;

		}

		deta10 = 0;

//3.418mV
		
//		printf("%d ", cnt);

		//入力電圧
		vint = deta * 3.418;

		temperature = (vint - 480) / 10; //温度変更

//		printf("T = %d ", temperature);

    	// 結果を送信
//        printf("V = %d\n", vint);



	return temperature;

}

int seki(){

	int idata;
	float dst1;
	double data1, data2;

	idata = adc_convert(1);




	return idata;


}


int main(){

	DDRA = 0b10000000;
	DDRB = 0b11111111;
	DDRC = 0b00110000;
	DDRD = 0b00111100;

	PCICR  = 0b00000100;
	PCMSK2 = 0b00000001;


    TCCR2A = 0b00000010;    
    TCCR2B = 0b00000111;    
    OCR2A = 5;              
    TIMSK2 = 0b00000010;    
	sei();                  //全体割り込み許可





	adc_init();
	    // USART0, 9600 bps
    usart_init(0, 9600);
	    // USART0 を標準出力に設定
    usart_stdout(0);

	int cnt1;

	while(1){






		while(flag == 0){
			if(PINC &_BV(6)){
				cnt = onpa();

			PORTA |= _BV(7);
			_delay_ms(30);
			PORTA &= ~_BV(7);
			_delay_ms(30);
			}
			else{

				PORTA &= ~_BV(7);
			}
		}

		while(flag == 1){
			if(PINC &_BV(6)){
				cnt = ondo();

			PORTA |= _BV(7);

			}
			else{

				PORTA &= ~_BV(7);
			}
		}

		while(flag == 2){
			if(PINC &_BV(6)){
				cnt = seki();

			PORTA |= _BV(7);

			}
			else{

				PORTA &= ~_BV(7);
			}
		}
		
	}
}
