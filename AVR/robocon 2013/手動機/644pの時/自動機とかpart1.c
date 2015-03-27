/*  ATmega644P専用プログラム  */
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdbool.h>


/* PSコントローラーボタン定義 */

#define l1         SwitchRecv[1]==0x04
#define r1		   SwitchRecv[1]==0x08
#define l2		   SwitchRecv[1]==0x01
#define r2		   SwitchRecv[1]==0x02
#define l3		   SwitchRecv[0]==0x02		//L3, R3はアナログスティックの押しこみボタン
#define r3		   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_r_x   SwitchRecv[2]   // 左0 < 中心127 < 右255 
#define analog_r_y   SwitchRecv[3]   // 上0 < 中心127 < 下255
#define analog_l_x   SwitchRecv[4]   // 左0 < 中心127 < 右255 
#define analog_l_y   SwitchRecv[5]   // 上0 < 中心127 < 下255


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


/**********タッチセンサー関連**********/
bool up_touch(void){
	return PINB & _BV(0);
}

bool down_touch(void){
	return PINB & _BV(1);
}

bool right_touch(void){
	return PINB & _BV(2);
}

bool left_touch(void){
	return PINB & _BV(5);
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

/* NoOperation */
void nop(int count){
	int i;
	for(i = 0; i < count; i++){
		_delay_ms(100);
	}
}

/* intの桁数を返す */
char getDigit(int n){
  char i;
  i = 0;
  while(n>0){
    n /= 10;
    i++;
  }
  return i;
}

/* int->String変換 */
char *intToStr(int n, char *buf){ // 変換する数、作業領域
  int i, digit;

  if(n == 0){
	buf[0] = '0';
	buf[1] = '\0';
	return buf;
  }

  digit = getDigit(n); // 桁数
  for(i = digit-1; i >= 0; i--){ // intは最大5桁
    buf[i] = n%10+'0';
    n /= 10;
  }
  buf[digit] = '\0'; // 行末改行
  return buf;
}

/* USARTで文字列送信 */
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

int A0_number;

int A0_number, B0_number;
int A1_number, B1_number;
int A2_number, B2_number;
   	char buf[6];

















/*----------------------足回りモーター関数---------------------------*/
//0A,0B: 右モーター
//2A,2B: 左モーター

void strat0(int s, int st){
	int i, a = 0;
	A0_number = s;
	B0_number = 0;
	A2_number = s;
	B2_number = 0;

	for(i = 0; i < st; i++){
/*
		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // 改行




*/

		A0_number = A0_number + 1;
		A2_number = A2_number + 1;
//		a = a + 1;		
/*
		if(a > 10){

			A2_number = A2_number + 1;

		}
*/
		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_top()){
			break;
		}
	}
}

void strat1(int s){

/*

		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // 改行
*/
		A0_number = s - 5;
		B0_number = 0;
		A2_number = s;
		B2_number = 0;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);


}

void strat_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 128; i++){


/*

		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // 改行





*/





		B0_number = B0_number + 2;
		B2_number = B2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}




void back0(int s, int bt){
	int i, a = 0;

	A0_number = 0;
	B0_number = s;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < bt; i++){

		B0_number = B0_number + 1;
		B2_number = B2_number + 1;

//		a = a + 1;		
/*
		if(a > 10){

		B2_number = B2_number + 1;


		}
*/

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_bottom()){
			break;
		}
	}
}

void back1(int s){

		A0_number = 0;
		B0_number = s;
		A2_number = 0;
		B2_number = s - 5;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void back_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 128; i++){

		A0_number = A0_number + 2;
		A2_number = A2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}








void left0(int s, int t){
	int i;

	A0_number = s;
	B0_number = 0;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < t; i++){

		A0_number = A0_number + 1;
		B2_number = B2_number + 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_left()){
			break;
		}
	}
}

void left1(int s){

		A0_number = s;
		B0_number = 0;
		A2_number = 0;
		B2_number = s;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void left_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 128; i++){

		B0_number = B0_number + 2;
		A2_number = A2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}











void right0(int s, int t){
	int i;

	A0_number = 0;
	B0_number = s;
	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number + 1;
		A2_number = A2_number + 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(2);

		if(!ps_right()){
			break;
		}
	}
}

void right1(int s){

		A0_number = 0;
		B0_number = s;
		A2_number = s;
		B2_number = 0;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);

}

void right_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 128; i++){

		A0_number = A0_number + 2;
		B2_number = B2_number + 2;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB &=  ~_BV(1);
		PORTB &=  ~_BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD &=  ~_BV(2);
		PORTD &=  ~_BV(3);
		_delay_ms(1);

	}
}





void stop(){

	A0_number = 255;
	B0_number = 255;
	A2_number = 255;
	B2_number = 255;

	OCR0A = A0_number;
	OCR0B = B0_number;
	PORTB &=  ~_BV(1);
	PORTB &=  ~_BV(2);


	OCR2A = A2_number;
	OCR2B = B2_number;
	PORTD &=  ~_BV(1);
	PORTD &=  ~_BV(2);
}






/*--------------アームモータ関数---------------*/


void arm_one_strat0(int s, int t){
	int i;

	A1_number = 0;
	B1_number = s;

	for(i = 0; i < t; i++){

		B1_number = B1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB |= _BV(6);
		PORTB |= _BV(7);

		_delay_ms(2);
	}
}

void arm_one_strat1(int s){

	A1_number = 0;
	B1_number = s;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB |= _BV(6);
	PORTB |= _BV(7);
}

void arm_one_strat_stop(){
	int i;

	A1_number = 0;
	B1_number = 255;

	for(i = 0; i < 128; i++){

		A1_number = A1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB &=  ~_BV(6);
		PORTB &=  ~_BV(7);

		_delay_ms(1);

	}
}





void arm_one_back0(int s, int t){
	int i;

	A1_number = s;
	B1_number = 0;

	for(i = 0; i < t; i++){

		A1_number = A1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB |= _BV(6);
		PORTB |= _BV(7);

		_delay_ms(2);
	}
}

void arm_one_back1(int s){

	A1_number = s;
	B1_number = 0;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB |= _BV(6);
	PORTB |= _BV(7);

}

void arm_one_back_stop(){
	int i;

	A1_number = 255;
	B1_number = 0;

	for(i = 0; i < 128; i++){

		B1_number = B1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTB &=  ~_BV(6);
		PORTB &=  ~_BV(7);

		_delay_ms(1);

	}
}









void arm_twe_strat1(){

		PORTC &=  ~_BV(0);
		PORTC |=  _BV(1);

		PORTC |=  _BV(2);
		PORTC &= ~_BV(3);

}



void arm_twe_back1(){

		PORTC |=  _BV(0);
		PORTC &=  ~_BV(1);

		PORTC &= ~_BV(2);
		PORTC |=  _BV(3);


}



void stop2(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTB &=  ~_BV(6);
	PORTB &=  ~_BV(7);


	PORTC |=  _BV(0);
	PORTC |=  _BV(1);
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


/*
void strat0_srow2(int t){

	int i;

	A0_number = 100;
	B0_number = 100;
	A2_number = 100;
	B2_number = 100;

	for(i = 0; i < t; i++){


			usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 


		B0_number = B0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);

	}
}
*/



void strat0_srow(int t){

	int i;

//	A0_number = s;
	B0_number = 0;
//	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){
/*
		usart_sendStr("  ");
		usart_sendStr("0A:"); 
 		usart_sendStr(intToStr(A0_number,buf)); 
		usart_sendStr("  ");
		usart_sendStr("0B:"); 
 		usart_sendStr(intToStr(B0_number,buf));
		usart_sendStr("  ");
		usart_sendStr("2A:");
  	    usart_sendStr(intToStr(A2_number,buf));
		usart_sendStr("  "); 
		usart_sendStr("2B:"); 
	 	usart_sendStr(intToStr(B2_number,buf));; 

		usart_sendStr("\r\n"); // 改行


*/





		A0_number = A0_number - 1;
		A2_number = A2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);

	}
}

void back0_srow(int t){

	int i;

	A0_number = 0;
//	B0_number = 0;
	A2_number = 0;
//	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

void left0_srow(int t){

	int i;

//	A0_number = 0;
	B0_number = 0;
	A2_number = 0;
//	B2_number = 0;

	for(i = 0; i < t; i++){

		A0_number = A0_number - 1;
		B2_number = B2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

void right0_srow(int t){

	int i;

	A0_number = 0;
//	B0_number = 0;
//	A2_number = 0;
	B2_number = 0;

	for(i = 0; i < t; i++){

		B0_number = B0_number - 1;
		A2_number = A2_number - 1;

		OCR0A = A0_number;
		OCR0B = B0_number;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = A2_number;
		OCR2B = B2_number;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);
		_delay_ms(3);
	}
}

int flag_stop1 = 0;
int flag_stop2 = 0;

/*---------------------スロー足回り-----------------*/
void slow_move(){
			
		while(ps_l1()){

			leaf();

			if(ps_top()){
/*
					usart_sendStr("  ");
					usart_sendStr("上キー"); 
					usart_sendStr("\r\n"); // 改行
*/
				if(flag_stop1 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}
					flag_stop1 = 0;
				if(A0_number > 110){

					strat0_srow(A0_number - 100);
				}else{
					strat0(0, 100); //(PWM初期値, カウンター)
				}

				while(1){
					strat1(100); //(PWM)

					if(!ps_top()){
						strat_stop();
						break;
					}

					if(!ps_l1()){
						strat0(100,155);
						break;
					}
				}
			}else if(ps_bottom()){
				if(flag_stop1 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}
				
				flag_stop1 = 0;

				if(B0_number > 110){
					back0_srow(B0_number - 100);
				}else{
					back0(0, 100); //(PWM初期値, カウンター)
				}

				while(1){
					back1(100); //(PWM)

					if(!ps_bottom()){
						back_stop();
						break;
					}

					if(!ps_l1()){
						back0(100,155);
						break;
					}
				}

			}else {
				flag_stop1 = 1;
				stop();
			}



			if(ps_left()){

				if(flag_stop2 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}

				flag_stop2 = 0;

				if(A0_number > 110){
					left0_srow(A0_number - 100);
				}else{
					left0(0, 100); //(PWM初期値, カウンター)
				}

				while(1){
					left1(100);

					if(!ps_left()){
						left_stop();
						break;
					}

					if(!ps_l1()){
						left0(100,155);
						break;
					}
				}
			}else if(ps_right()){

				if(flag_stop2 == 1){
					A0_number = 100;
					B0_number = 100;
					A2_number = 100;
					B2_number = 100;
//					strat0(0,1);

				}

				flag_stop2 = 0;

				if(B0_number > 110){
					right0_srow(B0_number - 100);
				}else{
					right0(0, 100); //(PWM初期値, カウンター)
				}

				while(1){
					right1(100);

					if(!ps_right()){
						right_stop();
						break;
					}

					if(!ps_l1()){
						right0(100,155);
						break;
					}
				}

			}else {
				flag_stop2 = 1;
				stop();

			}









			if(ps_triangle()){
//				arm_twe_strat1();
				arm_one_strat0(0, 255); //(PWM初期値, カウンター)


				while(1){
					arm_one_strat1(255); //(PWM)
//					arm_twe_strat1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();
					}

					if(!ps_triangle()){
						arm_one_strat_stop();
						break;
					}
				}
			}else if(ps_cross()){
				arm_one_back0(0, 255);
//				arm_twe_back1();	
				while(1){
					arm_one_back1(255);
//					arm_twe_back1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();


					}



					if(!ps_cross()){
						arm_one_back_stop();
						break;
					}
				}

			}else {
//				stop2();

			}


			if(ps_triangle()){
					arm_one_strat1(255); //(PWM)


			}else if(ps_cross()){
					arm_one_back1(255);



			}

			
			if(ps_r2()){

				arm_twe_back1();
			}else if(ps_r1()){

				arm_twe_strat1();


			}else {
				stop2();
			}



		}
}

void leaf_on(){
	PORTC |= _BV(7);

	_delay_ms(600);

	PORTC &=~_BV(7);
}

void leaf_off(){
	PORTC |= _BV(6);

	_delay_ms(600);

	PORTC &=~_BV(6);
}

	bool token = false; // トークンをとっているか
//	bool basket = false; // 籠をとっているか

void leaf(){
		if(ps_circle()){
			
			// トークンを掴んでいる場合
			if(token){
				leaf_off();
				token = false;
			}
			
			// トークンを掴んでいない場合
			else {
				leaf_on();
				token = true;
			}

			while(ps_circle());
		}

}

/**********PORT配置**********/
// 644Pのとき

// PA0 
// PA1 
// PA2 
// PA3 
// PA4 

// PB0: 
// PB1: BHS (右モーター)
// PB2: AHS (右モーター)
// PB3: ALS (右モーター)
// PB4: BLS (右モーター)
// PB5:
// PB6: AHS (中心モーター)
// PB7: BHS (中心モーター)

// PC0: ALS (ワイヤーモーター)
// PC1: BLS (ワイヤーモーター)
// PC2: AHS (ワイヤーモーター)
// PC3: BHS (ワイヤーモーター)
// PC4:
// PC5:
// PC6:
// PC7:

// PD0: コントローラー受信
// PD1:
// PD2: AHS (左モーター)
// PD3: BHS (左モーター)
// PD4: BLS (中心モーター)
// PD5: ALS (中心モーター)
// PD6: BLS (左モーター)
// PD7: ALS (左モーター)


/**********メイン関数**********/
int main(){

	token = false; // トークンをとっているか


	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	DDRC = 0b11111111;

    usart_init(MYUBRR);   // USART設定
   	//adc_init();           // ADConverter設定

	//int ad,ad2,ad3;
//    char buf[6];
/*	
	int s = 255;// モーター数値
	int sig_up = 0, sig_side = 0; 
	int center_r_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_r_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int center_l_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_l_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;
*/
	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;	
	TCCR1A = 0b10100001;  // OCR1A OCR1B の設定
	TCCR1B = 0b00000011;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;

   	sei();    //割り込み許可(許可しないとPSコントローラーの信号が受けれない)

    //ANALOGが押されてないとノイズが乗るのでANALOGを押しスタートを押すまでは待機.
	while(analog_r_x == 0 || analog_r_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");

	}
/*
	//動作確認のためブザー使ったら(・∀・)ｲｲﾈ!!？
	PORTB = _BV(0);   
	_delay_ms(1000);
	PORTB ^= _BV(0);
*/
//		wwww(s);

	int sum;
	int flag_sro = 0;

	while(1){

		leaf(); //アーム開閉


/*-------------------アーム制御-------------------*/

			if(ps_cross()){
//				arm_twe_strat1();
				arm_one_strat0(0, 255); //(PWM初期値, カウンター)


				while(1){
					arm_one_strat1(255); //(PWM)
//					arm_twe_strat1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();
					}

					if(!ps_cross()){
						arm_one_strat_stop();
						break;
					}
				}
			}else if(ps_triangle()){
				arm_one_back0(0, 255);
//				arm_twe_back1();	
				while(1){
					arm_one_back1(255);
//					arm_twe_back1();

					if(ps_r2()){

						arm_twe_back1();
					}else if(ps_r1()){

						arm_twe_strat1();


					}



					if(!ps_triangle()){
						arm_one_back_stop();
						break;
					}
				}

			}else {
//				stop2();

			}

/*
			if(ps_triangle()){
					arm_one_strat1(255); //(PWM)


			}else if(ps_cross()){
					arm_one_back1(255);



			}
*/
			
			if(ps_r2()){

				arm_twe_back1();
			}else if(ps_r1()){

				arm_twe_strat1();


			}else {
				stop2();
			}
			
			
			
			


		if(!(SwitchRecv[0] == 0xff)){
			flag_stop1 = 1;
			flag_stop2 = 1;
			stop();
		}



		flag_sro = 0;

		if(ps_l1()){

			slow_move();// スロー

			flag_sro = 1;
		}

/*-------------------MAX足回り------------------*/

		if(ps_top()){
/*			usart_sendStr("  ");
			usart_sendStr("上キー"); 
			usart_sendStr("\r\n"); // 改行
*/
			flag_stop1 = 0;		

			if(flag_sro == 0){
				strat0(0,255); //(PWM初期値, カウンター)
			}

			while(1){
				strat1(255); //(PWM数値)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
			
			}
			
		}else if(ps_bottom()){	
			flag_stop1 = 0;	
					
			if(flag_sro == 0){
				back0(0,255); //(PWM初期値, カウンター)
			}

			while(1){
				back1(255);

				if(!ps_bottom()){
					back_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

			}
		
		}else {
			flag_stop1 = 1;
			stop();
		}



		if(ps_left()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				left0(0, 255);
			}
			while(1){
				left1(255);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
			}

		}else if(ps_right()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				right0(0, 255);
			}
			while(1){
				right1(255);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

			}

		}else {
			flag_stop2 = 1;
			stop();
		}



/*----移動----*/


		// SELECT+START同時押しで、アナログスティックのX, Yの中心位置を初期化
/*		if(SwitchRecv[0]==0x09){
			usart_sendStr("Initialize center\r\n");
			center_r_x = 118;
			center_r_y = 132;
			center_l_x = 118;
			center_l_y = 132;
		}
		// アナログスティックの中心位置を変更
		if(select){
			usart_sendStr("PUSH SELECT");
			center_r_x = analog_r_x;
			center_r_y = analog_r_y;
			center_l_x = analog_l_x;
			center_l_y = analog_l_y;
		}

		// ここより下がプレステコントローラー制御命令
		if(analog_l_y <= center_l_y - 60)//center_yから80引いているのはｱﾅﾛｸﾞｽﾃｨｯｸを約45°ずつで分けるため
		{
			sig_up  = 1;

//			analog_l_up = 0xff - (analog_l_y * 2);

			top(s);
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			sig_up = 1;

//			analog_l_down = (analog_l_y * 2) - 0xff;

			down(s);
			usart_sendStr("DOWN ");
		}
		else
		{
			sig_up = 0;

			stop_up();
			usart_sendStr("STOP ");
		}
		
		if(analog_l_x <= center_l_x - 60)//center_yから80引いているのはｱﾅﾛｸﾞｽﾃｨｯｸを約45°ずつで分けるため
		{
			sig_side = 1;

//			analog_l_left = 0xff - (analog_l_x * 2);

			left(s);

			usart_sendStr("UP ");
		}
		else if(analog_l_x >= center_l_x + 60)
		{
			sig_side = 1;

//			analog_l_right = (analog_l_x * 2) - 0xff;

			right(s);

			usart_sendStr("DOWN ");
		}
		else
		{
			sig_side = 0;

			stop_side();
			usart_sendStr("STOP ");
		}


*/






	}
}


