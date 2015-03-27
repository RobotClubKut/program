/*  ATmega168P専用プログラム  */
/*  AVR PlayStationController */
/*  Dualshock2対応            */

/*
   SwitchRecv[]のカッコには0から3まで入る。
   SwitchRecv[]にはプレステのボタンが押されると16進数が
   帰ってくるようになっている。
   
   例えば使いたいボタンが△だとする。
   if(SwitchRecv[1] == 0x01);
   とすることで△ボタンが押したときの命令を書くことが可能。

   他のボタンは下記の表を参照

	SwitchRecv[0] ==
		0x01	SELECT		0x10	方向キー↑
		0x02	L3		0x20	方向キー→
		0x04	R3		0x40	方向キー↓
		0x08	START		0x80	方向キー←

	SwitchRecv[1] == 
		0x01	L2		0x10	△
		0x02	R2		0x20	○
		0x04	L1		0x40	×
		0x08	R1		0x80	□

	SwitchRecv[2]
		アナログスティックLのx軸0～255（中心127）

	SwitchRecv[3]
		アナログスティックLのy軸0～255（中心127）
*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* PSコントローラーボタン定義 */

#define l1         SwitchRecv[1]==0x04
#define r1		   SwitchRecv[1]==0x08
#define l2		   SwitchRecv[1]==0x01
#define r2		   SwitchRecv[1]==0x02
#define l3		   SwitchRecv[0]==0x02		//L3, R3はアナログスティックの押しこみボタン
#define r3		   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_x   SwitchRecv[2]   // 左0 < 中心127 < 右255 
#define analog_y   SwitchRecv[3]   // 上0 < 中心127 < 下255


volatile uint16_t SwitchRecv[8]; //SwitchRecv[]をグローバル変数で宣言

// ==========================================================================
// PlayStation コントローラー 関数
// ==========================================================================

#define PS_UP       4
#define PS_RIGHT    5
#define PS_DOWN     6
#define PS_LEFT     7
#define PS_L2       0
#define PS_R2       1
#define PS_L1       2
#define PS_R1       3
#define PS_TRIANGLE 4
#define PS_CIRCLE   5
#define PS_CROSS    6
#define PS_SQUARE   7


// 上キーが押されているか返す
inline bool ps_top(void){
	return SwitchRecv[0] & _BV(PS_UP);
}

// 右キーが押されているか返す
inline bool ps_right(void){
	return SwitchRecv[0] & _BV(PS_RIGHT);
}

// 下キーが押されているか返す
inline bool ps_bottom(void){
	return SwitchRecv[0] & _BV(PS_DOWN);
}

// 左キーが押されているか返す
inline bool ps_left(void){
	return SwitchRecv[0] & _BV(PS_LEFT);
}

// L2 キーが押されているか返す
inline bool ps_l2(void){
	return SwitchRecv[1] & _BV(PS_L2);
}

// R2 キーが押されているか返す
inline bool ps_r2(void){
	return SwitchRecv[1] & _BV(PS_R2);
}

// L1 キーが押されているか返す
inline bool ps_l1(void){
	return SwitchRecv[1] & _BV(PS_L1);
}

// R1 キーが押されているか返す
inline bool ps_r1(void){
	return SwitchRecv[1] & _BV(PS_R1);
}

// △キーが押されているか返す
inline bool ps_triangle(void){
	return SwitchRecv[1] & _BV(PS_TRIANGLE);
}

// ×キーが押されているか返す
inline bool ps_cross(void){
	return SwitchRecv[1] & _BV(PS_CROSS);
}

// ○キーが押されているか返す
inline bool ps_circle(void){
	return SwitchRecv[1] & _BV(PS_CIRCLE);
}

// □キーが押されているか返す
inline bool ps_square(void){
	return SwitchRecv[1] & _BV(PS_SQUARE);
}


/** UART設定 **/	  // 工場出荷時はCKDIV8(1/8MHz)となっているのでFusesからCKDIV8をはずす
#define FOSC 8000000  // 8MHz安定
#define BAUD 38400    // 38400bpsじゃないとATTiny2313から信号を受信できない
#define MYUBRR FOSC/16/BAUD-1 // UART分周率

/* USART設定 */
void usart_init(unsigned int ubrr){
  UBRR0H = (unsigned char)(ubrr>>8); // ボーレート上位8bit
  UBRR0L = (unsigned char)ubrr; // ボーレート下位8bit
  UCSR0A = (0<<U2X0); // 等速
  UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // 送受信許可、受信完了割り込み許可
  UCSR0C = (0<<UMSEL00)|(3<<UCSZ00)|(1<<USBS0)|(0<<UPM00);
  // フレーム設定 非同期通信 8ビット 1ストップビット パリティ無し
}

/* UARTで文字列送信 */
void usart_sendStr(char *str){
  while(*str != '\0'){
    loop_until_bit_is_set(UCSR0A,UDRE0); // 送信データレジスタ空きまで待機
    UDR0 = *str++; // 1文字送信、1文字進む
  }
}

/* ATTiny2313からPSコントローラーの信号を受信 */
ISR(USART0_RX_vect){

    static uint16_t buff;
    uint16_t data,temp;

    data = UDR0;

    if(!(data & 0x08)){
        buff = data;
        return;
    }
    if((data & 0x07)==(buff & 0x07)){
        temp  = buff & 0xF0;
        temp |= data >> 4;
        SwitchRecv[data & 0x07] = temp;
    }
}

void buzzer_on(void){
	PORTD |= _BV(5);
}

void buzzer_off(void){
	PORTD &= ~_BV(5);
}

void buzzer_times(int n){
	int i;

	for(i = 0; i < n; ++i){
		buzzer_on();

		_delay_ms(100);

		buzzer_off();

		_delay_ms(80);
	}
}

/*-------モータ---------*/
/*
	PB0,PB1,PB2がモーターA(右)
	PB3,PB4,PB5がモーターB(左)
*/

void motaA_front(int s){
	PORTB |= _BV(0);
	PORTB &= ~_BV(1);
	PORTB &= ~_BV(2);

//	OCR0A = s;  
//	OCR0B = 0x00; 
}

void motaA_back(int s){
	PORTB &= ~_BV(0);
	PORTB |= _BV(1);
	PORTB &= ~_BV(2);
	
//	OCR0A = 0x00;  
//	OCR0B = s; 
}

void motaA_stop(){
	PORTB &= ~_BV(0);
	PORTB &= ~_BV(1);
	PORTB |= _BV(2);

//	OCR0A = 0x00;  
//	OCR0B = 0x00; 

}

void dengi(){

	PORTB = 0x1b;

}

void motaB_front(int s){
	PORTB |=  _BV(3);
	PORTB &= ~_BV(4);
	PORTB &= ~_BV(5);

//	OCR2A = s;  // PB3のPWM値
//	OCR2B = 0x00;  // PD3のPWM値
}

void motaB_back(int s){
	PORTB &= ~_BV(3);
	PORTB |= _BV(4);
	PORTB &= ~_BV(5);

//	OCR2A = 0x00;  // PB3のPWM値
//	OCR2B = s;  // PD3のPWM値
}

void motaB_stop(){
	PORTB &= ~_BV(3);
	PORTB &= ~_BV(4);

	PORTB |= _BV(5);

//	OCR2A = 0x00;  
//	OCR2B = 0x00; 
}






/*-----------メイン-------------*/

int main(void){

	int s = 255;	

	DDRA = 0b00000000;
	DDRB = 0b11111111;
	DDRC = 0b00000000;
	DDRD = 0b11111111;

/*	// OCR0A OCR0B の設定
	TCCR0A = 0b10100011;  
	TCCR0B = 0b00000001;
	// OCR2A OCR2B の設定
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000001;
*/
	buzzer_on();
	_delay_ms(500);

	usart_init(MYUBRR);   // USART設定

    sei();    //割り込み許可(許可しないとPSコントローラーの信号が受けれない)
	
	buzzer_off();
	
	while(1){
/*---------------足回り------------------*/
		if(ps_top()){
			while(ps_top()){
				motaA_front(s);
				motaB_front(s);
			}
		}else if(ps_bottom()){
			while(ps_bottom()){
				motaA_back(s);
				motaB_back(s); 
			}
		}else if(ps_right()){
			while(ps_right()){
				motaA_back(s);
				motaB_front(s);
			}
		}else if(ps_left()){
			while(ps_left()){
				motaA_front(s);
				motaB_back(s);
			}
		}else {
//			motaA_stop();
//			motaB_stop();
			dengi();

		}


/*----------
---アナログスティック------------*/

/*		if(analog_y < 100){
			PORTD = 0x0f;
			PORTA = 0x00;
		}else if( analog_y > 155){
			PORTD = 0xf0;
			PORTA = 0x00;
		}else {
			PORTA = 0xff;
		}


		OCR0A = analog_y;  
		// PD6のPWM値　それぞれ値をいじればPWMの出力が変化するのが分かるはず
		OCR0B = 0x00;  
		// PD5のPWM値　条件文などを作ればOCR0Bなどの値を入力によって変えれるので実験してみてください
		OCR2A = analog_x;  // PB3のPWM値
		OCR2B = 0x01;  // PD3のPWM値

*/
	}




	
//	return 0;
}

