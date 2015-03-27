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
#include <math.h>

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


#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTEの指定BITに1をセット
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTEの指定BITをクリア

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

/* ADコンバータ設定 */
void adc_init(void){
  ADMUX = (0<<REFS0); // 外部基準電圧
  ADCSRA =(1<<ADEN)|(1<<ADSC)|(0<<ADPS0);
  // A/D変換許可、1回目変換開始(調整)、分周率2
}

/* ピンを指定してAD変換 return 0-1023 */
int adc_convert(char pin){
  int ad;
  ADMUX = pin; // AD変換入力ピン
  cbi(ADCSRA,ADIF);
  sbi(ADCSRA,ADSC); // 変換開始
  loop_until_bit_is_set(ADCSRA,ADIF); // 変換完了まで待つ
  ad = ADCL; // 下位8bit取得
  return ad += (ADCH<<8); // 上位2bit取得
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

/******グローバル変数******/

int A0_number, B0_number;
int A1_number, B1_number;
int A2_number, B2_number;
int A3_number, B3_number;

int token1 = 0, token2 = 0, token3 = 0;

char buf[6], ps;

double angle_one, angle_twe, angle_apex, angle_apex_plan;



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
//			debug_move(); //足回りデバッグ


//		A0_number = A0_number + 1;
		A2_number = A2_number + 1;


		a++;	

		if(a > 1){
			if(a == 1){
				A0_number = 0;
			}

			A0_number = A0_number + 1;

		}else {
			if(s <= 100){
				A0_number = A0_number + 1;
			}else {
				A0_number = 0;
			}
		}

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

//			debug_move(); //足回りデバッグ

		if(s == 100){
			A0_number = s - 4;
			B0_number = 0;
			A2_number = s;
			B2_number = 0;
		}else {
			A0_number = s - 13;
			B0_number = 0;
			A2_number = s;
			B2_number = 0;
		}


		OCR0A = s;
		OCR0B = 0;
		PORTB |=  _BV(1);
		PORTB |=  _BV(2);

		OCR2A = s;
		OCR2B = 0;
		PORTD |=  _BV(2);
		PORTD |=  _BV(3);


}

void strat_stop(){
	int i;

	A0_number = 255;
	B0_number = 0;
	A2_number = 255;
	B2_number = 0;

	for(i = 0; i < 126; i++){

//			debug_move(); //足回りデバッグ

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
		_delay_ms(2);

	}
}




void back0(int s, int bt){
	int i, a = 0;

	A0_number = 0;
	B0_number = s;
	A2_number = 0;
	B2_number = s;

	for(i = 0; i < bt; i++){

//		B0_number = B0_number + 1;
		B2_number = B2_number + 1;

		a++;	
/*
		if(a > 10){
			if(a == 10){
				B0_number = 9;
			}

			B0_number = B0_number + 1;

		}else {
			if(s <= 100){
*/				B0_number = B0_number + 1;
//			}else {
//				B0_number = 0;
//			}
//		}


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

//	debug_move(); //デバッグ

	}
}

void back1(int s){

	if(s == 100){
		A0_number = 0;
		B0_number = s - 9;
		A2_number = 0;
		B2_number = s;
	}else {
		A0_number = 0;
		B0_number = s - 3;
		A2_number = 0;
		B2_number = s;
	}



	OCR0A = A0_number;
	OCR0B = B0_number;
	PORTB |=  _BV(1);
	PORTB |=  _BV(2);

	OCR2A = A2_number;
	OCR2B = B2_number - 7;
	PORTD |=  _BV(2);
	PORTD |=  _BV(3);

//		debug_move(); //デバッグ

}

void back_stop(){
	int i;

	A0_number = 0;
	B0_number = 255;
	A2_number = 0;
	B2_number = 255;

	for(i = 0; i < 126; i++){

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
		_delay_ms(2);

//	debug_move(); //デバッグ


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

	for(i = 0; i < 126; i++){

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

	for(i = 0; i < 126; i++){

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
	PORTD &=  ~_BV(2);
	PORTD &=  ~_BV(3);
}






/*--------------アームモータ関数---------------*/

// 中心モータ伸びる
void arm_one_strat0(int s, int t){
	int i;

	A1_number = 0;
	B1_number = s;

	for(i = 0; i < t; i++){

		B1_number = B1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC |= _BV(0);
		PORTC |= _BV(1);

		_delay_ms(1);

		if(!ps_triangle()){
			break;
		}
	}
}

void arm_one_strat1(int s){

	A1_number = 0;
	B1_number = s;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC |= _BV(0);
	PORTC |= _BV(1);
}

void arm_one_strat_stop(){
	int i;

	A1_number = 0;
	B1_number = 255;

	for(i = 0; i < 126; i++){

		A1_number = A1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC &=  ~_BV(0);
		PORTC &=  ~_BV(1);

		_delay_ms(1);

	}
}




// 中心モータ縮む
void arm_one_back0(int s, int t){
	int i;

	A1_number = s;
	B1_number = 0;

	for(i = 0; i < t; i++){

		A1_number = A1_number + 1;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC |= _BV(0);
		PORTC |= _BV(1);

		_delay_ms(1);

		if(!ps_cross()){
			break;
		}
	}
}

void arm_one_back1(int s){

	A1_number = s;
	B1_number = 0;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC |= _BV(0);
	PORTC |= _BV(1);

}

void arm_one_back_stop(){
	int i;

	A1_number = 255;
	B1_number = 0;

	for(i = 0; i < 126; i++){

		B1_number = B1_number + 2;

		OCR1A = A1_number;
		OCR1B = B1_number;
		PORTC &=  ~_BV(0);
		PORTC &=  ~_BV(1);

		_delay_ms(1);

	}
}

void arm_one_stop(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC &=  ~_BV(0);
	PORTC &=  ~_BV(1);

}


// ワイヤーモータ伸びる
void arm_twe_strat0(int s, int t){
	int i;

	A3_number = 0;
	B3_number = s;

	for(i = 0; i < t; i++){

		B3_number = B3_number + 1;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC |= _BV(2);
		PORTC |= _BV(3);

		_delay_ms(1);

		if(!ps_triangle()){
			break;
		}
	}
}

void arm_twe_strat1(int s){

	A3_number = 0;
	B3_number = s;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC |= _BV(2);
	PORTC |= _BV(3);
}

void arm_twe_strat_stop(){
	int i;

	A3_number = 0;
	B3_number = 255;

	for(i = 0; i < 126; i++){

		A3_number = A3_number + 2;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC &=  ~_BV(2);
		PORTC &=  ~_BV(3);

		_delay_ms(1);

	}
}

// ワイヤーモータ縮む
void arm_twe_back0(int s, int t){
	int i;

	A3_number = s;
	B3_number = 0;

	for(i = 0; i < t; i++){

		A3_number = A3_number + 1;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC |= _BV(2);
		PORTC |= _BV(3);

		_delay_ms(2);

		if(!ps_cross()){
			break;
		}
	}
}

void arm_twe_back1(int s){

	A3_number = s;
	B3_number = 0;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC |= _BV(2);
	PORTC |= _BV(3);

}

void arm_twe_back_stop(){
	int i;

	A3_number = 255;
	B3_number = 0;

	for(i = 0; i < 126; i++){

		B3_number = B3_number + 2;

		OCR3A = A3_number;
		OCR3B = B3_number;
		PORTC &=  ~_BV(2);
		PORTC &=  ~_BV(3);

		_delay_ms(1);

	}
}

void arm_twe_stop(){

	A3_number = 255;
	B3_number = 255;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


void stop2(){

	A1_number = 255;
	B1_number = 255;

	OCR1A = A1_number;
	OCR1B = B1_number;
	PORTC &=  ~_BV(0);
	PORTC &=  ~_BV(1);


	A3_number = 255;
	B3_number = 255;

	OCR3A = A3_number;
	OCR3B = B3_number;
	PORTC &=  ~_BV(2);
	PORTC &=  ~_BV(3);

}


void strat0_srow(int t){

	int i;
//	A0_number = s;
	B0_number = 0;
//	A2_number = s;
	B2_number = 0;

	for(i = 0; i < t; i++){

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
		_delay_ms(2);

		if(!ps_top()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_bottom()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_left()){
			break;
		}
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
		_delay_ms(2);

		if(!ps_right()){
			break;
		}
	}
}


int flag_stop1 = 0;
int flag_stop2 = 0;

/*---------------------スロー足回り-----------------*/
void slow_move(){
			
	while(ps_l1()){

		leaf();

		if(ps_top()){
			flag_stop1 = 0;
			if(A0_number == 255 && B0_number == 255){
				strat0(50, 50);
			}else if(A0_number >= 100 && B0_number < 3){

				strat0_srow(A0_number - 100);
			}else{

				strat0(A0_number, 100 - A0_number); //(PWM初期値, カウンター)
			}

			while(1){

				strat1(100); //(PWM)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(!ps_l1()){
					strat0(100,154);
					break;
				}
			}
		}else if(ps_bottom()){
			flag_stop1 = 0;

			if(A0_number == 255 && B0_number == 255){
				back0(50, 50);
			}else if(A0_number < 3 && B0_number >= 100){
				back0_srow(B0_number - 100);
			}else{
				back0(B0_number, 100 - B0_number); //(PWM初期値, カウンター)
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
//			stop();
		}



		if(ps_left()){
			flag_stop2 = 0;

			if(A0_number == 255 && B0_number == 255){
				left0(30, 70);
			}else if(A0_number >= 100 && B0_number < 3){
				left0_srow(A0_number - 100);
			}else{
				left0(A0_number, 100 - A0_number); //(PWM初期値, カウンター)
			}

			while(1){
				left1(100);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(!ps_l1()){
					break;
				}
			}
		}else if(ps_right()){
			flag_stop2 = 0;

			if(A0_number == 255 && B0_number == 255){
				right0(30, 70);
			}else if(A0_number < 3 && B0_number >= 100){
				right0_srow(B0_number - 100);
			}else{
				right0(B0_number, 100 - B0_number); //(PWM初期値, カウンター)
			}

			while(1){
				right1(100);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(!ps_l1()){
					break;
				}
			}
		}else {
			flag_stop2 = 1;
			stop();
		}
	}
}

/*----------圧縮空気関連----------*/
void leaf_one_on(){
	PORTC |= _BV(7);

	_delay_ms(100);

	PORTC &=~_BV(7);
}

void leaf_one_off(){
	PORTC |= _BV(6);

	_delay_ms(100);

	PORTC &=~_BV(6);
}

void leaf_twe_on(){
	PORTA |= _BV(3);

	_delay_ms(100);

	PORTA &=~_BV(3);
}

void leaf_twe_off(){
	PORTA |= _BV(4);

	_delay_ms(100);

	PORTA &=~_BV(4);
}

void leaf_up(){
	PORTC |= _BV(5);

	_delay_ms(100);

	PORTC &=~_BV(5);
}

void leaf_down(){
	PORTC |= _BV(4);

	_delay_ms(100);

	PORTC &=~_BV(4);
}

void stone_on(){
	PORTA |= _BV(5);

	_delay_ms(100);

	PORTA &=~_BV(5);
}

void stone_off(){
	PORTA |= _BV(6);

	_delay_ms(100);

	PORTA &=~_BV(6);
}

//	bool token1 = false; // トークン1をとっているか
	int stone = 1;
	

void leaf(){

	while(ps_r1() && ps_r2()){

		//下アームだけ動かす
		if(ps_circle()){
			if(token3 == 0){
				leaf_one_on(); //1閉じる
				token3 = 1;
			}else if(token3 == 1){
				leaf_one_off(); //1開ける
				token3 = 0;
			}
			while(ps_circle());
		}
	}
	//全アーム開いて閉じる
	if(r3){ 	
		if(token1 == 1 && token2 == 1 && token3 == 1){
			leaf_one_off(); //1開ける
			leaf_twe_off(); //2開ける

			token1 = 0;
			token2 = 0;
			token3 = 0;
		}else if(token1 == 0 && token2 == 0 && token3 == 0){
			leaf_one_on(); //1閉じる
			leaf_twe_on(); //2閉じる

			token1 = 1;
			token2 = 1;
			token3 = 1;	
		}
		while(r3);
	}

	//投石器
	if(l3){
		if(stone == 0){
			stone_off();
			stone = 1;
		}else if(stone ==1){
			stone_on();
			stone = 0;
		}
		while(l3);
	}


//葉っぱ落とすとき
	if(ps_square()){
		//三個持っている時
		if(token1 == 1 && token2 == 1 && token3 == 1){
			leaf_one_off(); //1開ける

			token3 = 0;
		}		
		//二個持っている時
		else if(token1 == 1 && token2 == 1 && token3 == 0){
			leaf_down();	//下げる
			_delay_ms(300);
			leaf_twe_off(); //2開ける
			leaf_up();	//上げる
			_delay_ms(20);
			leaf_twe_on(); //2閉じる

			token2 = 0;

		}
		//一個持っている時
		else if(token1 == 1 && token2 == 0 && token3 == 0){
			leaf_down();	//下げる
			_delay_ms(300);
			leaf_twe_off(); //2開ける
			leaf_up();	//上げる

			token1 = 0;
		}else {
			token3 = 0; //?
		}

	while(ps_square());

	}




//葉っぱとるとき
	if(ps_circle()){
		//持っていないとき
		if(token1 == 0 && token2 == 0 && token3 == 0){
			leaf_one_off(); //1開ける
			leaf_twe_off(); //2開ける
			leaf_down(); //下げる
			_delay_ms(400);
			leaf_twe_on(); //2閉じる
			leaf_up(); //持ち上げる
			arm_one_back1(100);
			_delay_ms(450);
			arm_one_stop();
			token1 = 1;
		}
		//一個持っている時
		else if(token1 == 1 && token2 == 0 && token3 == 0){
			leaf_twe_off(); //2開ける
			leaf_down(); //下げる
			_delay_ms(400);
			leaf_twe_on(); //2閉じる
			leaf_up(); //持ち上げる
			arm_one_back1(100);
			_delay_ms(500);
			token2 = 1;
			arm_one_stop();
		}
		//二個持っている時
		else if(token1 == 1 && token2 == 1 && token3 == 0){
			leaf_one_on(); //1閉じる
			token3 = 1;

		}else {
			token3 = 0; //?
		}
		while(ps_circle());
	}
}
/*----------角度計算関数----------*/
void count_angle(){
//			0度				90度
	double one_max = 650, one_min = 287;
	double twe_max = 419, twe_min = 711;
//			90度			0度

	angle_one = (one_max - adc_convert(0)) * (90/(one_max - one_min)); //アーム①の床からの角度
	angle_twe = (twe_min - adc_convert(1)) * (90/(twe_min - twe_max)); //アーム②の垂直からの角度
	angle_apex = 90 - angle_one + angle_twe; //現在頂点角度
	angle_apex_plan = 180 - angle_one * 1.8; //理想頂点角度
									//	↑の値を2.0から大きくすればアーム低く, 小さくすれば高くなる
}

void debug_angle(){

	usart_sendStr("1AD= ");
	usart_sendStr(intToStr(adc_convert(0),buf));
	usart_sendStr(", 2AD= ");
	usart_sendStr(intToStr(adc_convert(1),buf));
	usart_sendStr(", angle_one= ");
	usart_sendStr(intToStr(angle_one,buf));
	usart_sendStr(", angle_twe= ");
	usart_sendStr(intToStr(angle_twe,buf));

	usart_sendStr(", angle_apex= ");
	usart_sendStr(intToStr(angle_apex,buf));

	usart_sendStr(", kakudo= ");
	usart_sendStr(intToStr(angle_apex_plan,buf));
/*
	usart_sendStr(", seki= ");
	usart_sendStr(intToStr(adc_convert(2),buf));

	usart_sendStr(", IIR= ");
	usart_sendStr(intToStr(IIR_y(adc_convert(2)),buf));
*/	usart_sendStr("\r\n"); // 改行

}

void debug_move(){
	usart_sendStr("  ");
	usart_sendStr("0A:"); 
 	usart_sendStr(intToStr(OCR0A,buf)); 
	usart_sendStr("  ");
	usart_sendStr("0B:"); 
 	usart_sendStr(intToStr(OCR0B,buf));
	usart_sendStr("  ");
	usart_sendStr("2A:");
  	usart_sendStr(intToStr(OCR2A,buf));
	usart_sendStr("  "); 
	usart_sendStr("2B:"); 
	usart_sendStr(intToStr(OCR2B,buf));; 

	usart_sendStr("\r\n"); // 改行
}

void debug_pwm_angle(){
	usart_sendStr("  ");
	usart_sendStr("1A:"); 
 	usart_sendStr(intToStr(OCR1A,buf)); 
	usart_sendStr("  ");
	usart_sendStr("1B:"); 
 	usart_sendStr(intToStr(OCR1B,buf));
	usart_sendStr("  ");
	usart_sendStr("3A:");
  	usart_sendStr(intToStr(OCR3A,buf));
	usart_sendStr("  "); 
	usart_sendStr("3B:"); 
	usart_sendStr(intToStr(OCR3B,buf));; 

	usart_sendStr("\r\n"); // 改行
}


/*------------アナログフィルター-------------*/

int IIR_y(int n){
	static int z[4]={0};//処理の後に代入させる
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[] = {0,0,0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1] << 8) * a2;
	a1 = (z[0] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3] << 8) * b2;
	b1 = (z[2] << 8) * b1;
	
	z[1] = z[0];
	z[0] = n >> 2;
	z[3] = z[2];
	z[2] = add[0];
	
	add[0] = add[1] + (a0 >> 4);
	add[0] = add[0] >> 8;
	add[1] = (a1 >> 4) + b1 + add[2];
	add[2] = (a2 >> 4) - b2;
	
	return add[0];
}



void arm_strat(){
					count_angle(); //角度計算

					arm_one_strat1(255); //(PWM)
/*
					if(!ps_triangle()){ //離された時止める
						arm_one_strat_stop();
						arm_twe_stop();
						break;
					}
*/
					if(angle_one < 4){ //アーム1が伸びきっているのでこの角度でストップ
						arm_one_stop();
						if(angle_twe < 75){ //アーム2が伸びきっていないのでこの角度まで伸ばす
							arm_twe_strat0(70,70);

						}else if(angle_twe > 85){
							arm_twe_back0(70,70);
						}else {
							arm_twe_stop();
//							break;
						}
					}else {
						//最初引っかからないようにアーム2を少し伸ばす
						if(angle_one > 70){
							if(angle_apex < 25){
								arm_one_stop();
								arm_twe_strat1(200);
								while(angle_apex < 25){
									count_angle(); //角度計算
								}
								arm_twe_strat_stop();
							}
						}


						if(angle_apex_plan - angle_apex > 15){ //アーム2の角度がとても浅い時
							if(angle_twe > 65){ //この角度以上の時はアーム2ストップ
								arm_twe_stop();

							}else {

								arm_twe_strat1(200);
								arm_one_strat_stop();
							}
						}else {
							if((angle_apex < angle_apex_plan) && (angle_twe < 85)){
								arm_twe_strat0(100, 150); //角度小さいから伸ばす
						//		arm_twe_strat_stop();
							}
							else if(angle_twe > angle_apex_plan){
								arm_twe_back0(80, 70); //角度大きいから縮む
						//		arm_twe_back_stop();
							}else {
								arm_twe_stop();
							}
						}
					}
}

void arm_back(){

					count_angle(); //角度計算

					arm_one_back1(255); //(PWM)
/*
					if(!ps_cross()){ //離された時止める
						arm_one_back_stop();
						arm_twe_stop();
						break;
					}
*/
					if(angle_one > 91){ //葉っぱを運ぶ位置へアームを移動
						arm_one_stop();
						if(angle_apex < 25){
							arm_twe_strat1(200);

							while(angle_apex < 25){
								count_angle(); //角度計算
							}
						}
						arm_twe_stop();
					}else {
						if(angle_apex < 55){ //葉っぱを運ぶ位置へアームを移動
					//		arm_one_back1(150);
							arm_twe_strat1(200);

						}else {
							if(angle_apex < angle_apex_plan){
								arm_twe_strat0(50, 80); //角度小さいから伸ばす

							}
							else if(angle_apex > angle_apex_plan){
								arm_twe_back0(80, 130); //角度大きいから縮む

							}else {
								arm_twe_stop();
							}
						}
					}

}

void r1_strat(){
						count_angle(); //角度計算

						if(adc_convert(0) <= 580){
							_delay_ms(5);
							if(adc_convert(0) <= 580){
								arm_one_strat1(255); //(PWM)
							}
						}else {
							arm_one_strat_stop();
//							break;
						}


}

void r1_back(){

						count_angle(); //角度計算

						if(adc_convert(0) > 192){
//							_delay_ms(5);
//							if(adc_convert(0) > 290){
								arm_one_back1(250);
//							}
						}else {
							arm_one_stop();
//							break;
						}


}

void modoru(){
	if(angle_one < 35){
		arm_one_back1(250);
	}else {
		arm_one_stop();
	}

	if(angle_twe > 30){
		arm_twe_back1(170);
	}else {
		arm_twe_stop();
	}
}


/**********PORT配置**********/
// 1284Pのとき

// PA0 アーム1のポテンショメータ
// PA1 アーム2のポテンショメータ
// PA2 
// PA3 圧縮空気(上2)
// PA4 圧縮空気(上2)
// PA5 圧縮空気(投石器)
// PA6 圧縮空気(投石器)

// PB0: 
// PB1: BHS (右モーター)
// PB2: AHS (右モーター)
// PB3: BLS (右モーター)
// PB4: ALS (右モーター)
// PB5:
// PB6: ALS (ワイヤーモーター)
// PB7: BLS (ワイヤーモーター)

// PC0: AHS (中心モーター)
// PC1: BHS (中心モーター)
// PC2: AHS (ワイヤーモーター)
// PC3: BHS (ワイヤーモーター)
// PC4:	圧縮空気(上下)
// PC5:	圧縮空気(上下)
// PC6: 圧縮空気(下1)
// PC7: 圧縮空気(下1)

// PD0: コントローラー受信
// PD1:
// PD2: AHS (左モーター)
// PD3: BHS (左モーター)
// PD4: BLS (中心モーター)
// PD5: ALS (中心モーター)
// PD6: ALS (左モーター)
// PD7: BLS (左モーター)


/**********メイン関数**********/
int main(){

	DDRA = 0b01111000;
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	DDRC = 0b11111111;

    usart_init(MYUBRR);   // USART設定
   	adc_init();           // ADConverter設定

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
	TCCR3A = 0b10100001;  // OCR3A OCR3B の設定
	TCCR3B = 0b00000011;

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


	int flag_sro = 0, angle_twe_sample = 0;

//	token1 = false; // トークンをとっているか
	leaf_one_off(); //1開ける
	leaf_twe_off(); //2開ける
	stone_off();


	while(1){

		if(start){
			
			leaf_one_off(); //1開ける
			leaf_up();		//上げる
			leaf_twe_off(); //2開ける

			stone_off();
			stone = 1;

			token1 = 0;
			token2 = 0;
			token3 = 0;

		}
		


		leaf(); //アーム開閉

		count_angle(); //角度計算

		debug_angle(); //デバッグ

/*-------------------アーム制御-------------------*/
/*

		if(ps_triangle()){
			
			arm_one_strat1(255); //(PWM)
			arm_twe_strat1(255); //(PWM)


		}else if(ps_cross()){

			arm_one_back1(255); //(PWM)
			arm_twe_back1(255); //(PWM)

		}else {
			arm_one_stop();
			arm_twe_stop();

		}

*/


	//R1を押しながら△Ｘを押すとアーム1だけ操作
		if(ps_r1()){
			if(ps_triangle()){

				if(angle_one > 2){ //アーム1伸びる

					arm_one_strat0(0, 255); //(PWM初期値, カウンター)

					while(1){
						count_angle(); //角度計算

						if(angle_one > 3){
							_delay_ms(5);
							if(angle_one > 3){
								arm_one_strat1(255); //(PWM)
							}
						}else {
							arm_one_strat_stop();
							break;
						}

						if(!ps_triangle() || !ps_r1()){ //離された時止める
							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}
					}
				}else {
					arm_one_stop();//アーム1止まる
					arm_twe_stop();
				}

			}else if(ps_cross()){
				if(angle_one < 90){//アーム1縮む

					arm_one_back0(0, 254);

					while(1){
						count_angle(); //角度計算

						if(angle_one < 90){
							arm_one_back1(255);
						}else {
							arm_one_stop();
							break;
						}

						if(!ps_cross() || !ps_r1){ //離された時止める
							arm_one_back_stop();
							arm_twe_stop();
							break;
						}
					}
				}else {
					arm_one_stop(); //アーム1止まる
					arm_twe_stop();
				}
			}else {
				arm_one_stop();
				arm_twe_stop();
			}
		}

	//R2を押しながら△Ｘを押すとアーム2だけ操作
		else if(ps_r2()){

			if(ps_triangle()){
				if(angle_twe < 90){
					//アーム2伸びる
					arm_twe_strat0(0, 255); //(PWM初期値, カウンター)

					while(1){
						count_angle(); //角度計算

						if(angle_twe < 90){
							arm_twe_strat1(255); //(PWM)
						}else {
							arm_twe_strat_stop();
							break;
						}

						if(!ps_triangle() || !ps_r2()){ //離された時止める
							arm_twe_strat_stop();
							break;
						}
					}

				}else {
					arm_one_stop();
					arm_twe_stop();
				}

			}else if(ps_cross()){
				if(angle_twe > 6){
					//アーム2縮む
					arm_twe_back0(0, 255);

					while(1){
						count_angle(); //角度計算

						if(angle_twe > 7){
							arm_twe_back1(255);
						}else {
							arm_twe_back_stop();
							break;
						}

						if(!ps_cross() || !ps_r2()){ //離された時止める
					//		arm_twe_back_stop();
							arm_twe_stop();
							break;
						}
					}

				}else {
					//アーム2止まる
					arm_twe_stop();
					arm_one_stop();
				}

			}else {
				arm_twe_stop();
				arm_one_stop();	
			}

	//△Ｘだけを押すと両方のアームを同時に動かす
		}else if(!ps_r1() && !ps_r2()){
			if(ps_triangle()){ //アーム伸ばす

				if(angle_one > 3){

					arm_one_strat0(0, 200); //(PWM初期値, カウンター)

					while(ps_triangle()){

						count_angle(); //角度計算

						arm_one_strat1(255); //(PWM)

						if(ps_r1()){ //アーム1だけ動かそうとした時
//							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}else if(ps_r2()){ //アーム2だけ動かそうとした時
							arm_one_strat_stop();
//							arm_twe_stop();
							break;
						}
	
						if(angle_one < 2){ //アーム1が伸びきっているのでこの角度でストップ
							arm_one_stop();
							if(angle_twe < 72){ //アーム2が伸びきっていないのでこの角度まで上げる
								arm_twe_strat0(70,100);

							}else if(angle_twe > 75){ //アーム2が伸びすぎているのでこの角度まで下げる
								arm_twe_back0(70,100);
							}else {
								arm_twe_stop();
								break;
							}
						}else {
							//最初引っかからないようにアーム2を少し伸ばす
							if(angle_one > 80){
								if(angle_apex < 13){
									arm_one_stop();
									arm_twe_strat1(200);
									while(angle_apex < 13){
										count_angle(); //角度計算
									}
									arm_twe_strat_stop();
								}
							}



							if(angle_apex_plan - angle_apex > 20){ //アーム2の角度がとても浅い時
								if(angle_twe > 80){ //この角度以上の時はアーム2ストップ
									arm_twe_stop();

								}else { //アーム1低速、アーム2高速
									arm_twe_strat1(200);
									arm_one_strat1(150);
								}
							}else {
								if((angle_apex < angle_apex_plan) && (angle_twe < 85)){
									arm_twe_strat0(70, 140); //角度小さいから伸ばす
							//		arm_twe_strat_stop();
								}
								else if(angle_twe > angle_apex_plan){
									arm_twe_back0(80, 70); //角度大きいから縮む
							//		arm_twe_back_stop();
								}else {
									arm_twe_stop();
								}
							}
						}
					}
					arm_one_strat_stop();
					arm_twe_stop();

				}else {
					arm_one_stop();
					arm_twe_stop();
			
				}
			}else if(ps_cross()){ //アーム縮める
				if(angle_one < 85){

					arm_one_back0(0, 200); //(PWM初期値, カウンター)

					while(1){

						count_angle(); //角度計算

						arm_one_back1(255); //(PWM)

						if(ps_r1()){ //アーム1だけ動かそうとした時
//							arm_one_strat_stop();
							arm_twe_stop();
							break;
						}else if(ps_r2()){ //アーム2だけ動かそうとした時
							arm_one_strat_stop();
//							arm_twe_stop();
							break;
						}


						if(!ps_cross()){ //離された時止める
							arm_one_back_stop();
							arm_twe_stop();
							break;
						}

						if(angle_one > 91){ //葉っぱを運ぶ時の位置へアームを移動
							arm_one_stop();
							if(angle_apex < 25){
								arm_twe_strat1(200);

								while(angle_apex < 25){
									count_angle(); //角度計算
								}
							}
							arm_twe_stop();
						}else {
							if(angle_apex < 55){ //葉っぱを運ぶ位置へアームを移動
						//		arm_one_back1(150);
								arm_twe_strat1(200);

							}else {
								if(angle_apex < angle_apex_plan){
									arm_twe_strat0(50, 80); //角度小さいから伸ばす

								}
								else if(angle_apex > angle_apex_plan){
									arm_twe_back0(60, 150); //角度大きいから縮む

								}else {
									arm_twe_stop();
								}
							}
						}
					}
				}else {
					arm_one_stop();
					arm_twe_stop();

				}
			}else {
				arm_one_stop();
				arm_twe_stop();
				stop();

			}
		}

		//伸びた状態から葉っぱを取る位置までアームを縮める
		if(ps_l2()){
			modoru();
		}



/*-------------------MAX足回り------------------*/
		flag_sro = 0;

		if(ps_l1()){
			flag_sro = 1;

			slow_move();// スロー
		}

		if(ps_top()){
			flag_stop1 = 0;		

			if(flag_sro == 0){
				strat0(30,225); //(PWM初期値, カウンター)

			}

			while(1){
				count_angle(); //角度計算

				strat1(255); //(PWM数値)

				if(!ps_top()){
					strat_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}
				//アーム制御(アーム1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//アーム制御(前後)
				}else if(ps_l2()){
					modoru();
				}else{
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}
			}

		}else if(ps_bottom()){
			flag_stop1 = 0;

			if(flag_sro == 0){
				back0(30,225); //(PWM初期値, カウンター)
			}

			while(1){
				count_angle(); //角度計算

				back1(255);

				if(!ps_bottom()){
					back_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

				//アーム制御(アーム1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//アーム制御(前後)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}
			}

		}else {
			flag_stop1 = 1;
		}



		if(ps_left()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				left0(30, 90);
			}
			while(1){
				count_angle(); //角度計算

				left1(120);

				if(!ps_left()){
					left_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}


				//アーム制御(アーム1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//アーム制御(前後)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}


			}

		}else if(ps_right()){

			flag_stop2 = 0;

			if(flag_sro == 0){
				right0(30, 90);
			}
			while(1){
				count_angle(); //角度計算

				right1(120);

				if(!ps_right()){
					right_stop();
					break;
				}

				if(ps_l1()){
					slow_move();
				}

				//アーム制御(アーム1)
				if(ps_r1()){
					if(ps_triangle()){
						if(adc_convert(0) <= 580){
							r1_strat();
						}else {
							arm_one_stop();
						}
					}else if(ps_cross()){
						if(adc_convert(0) > 192){
							r1_back();
						}else {
							arm_one_stop();	
						}
					}else {
						arm_one_stop();
					}
				//アーム制御(前後)
				}else if(ps_l2()){
					modoru();
				}else {
					if(ps_triangle()){
						if(angle_one > 3){
							arm_strat();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else if(ps_cross()){
						if(angle_one < 85){
							arm_back();
						}else {
							arm_one_stop();
					//		arm_twe_stop();
						}
					}else {
						arm_one_stop();
						arm_twe_stop();

					}
				}

			}

		}else {
			flag_stop2 = 1;
			stop();
		}

	}
}


