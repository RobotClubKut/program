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



/*-----------ブザー関連-----------*/
void buzzer_on(void){
	PORTB |= _BV(0);
}

void buzzer_off(void){
	PORTB &= ~_BV(0);
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



/*-----------圧縮空気-----------*/

void token_on(){
	PORTB |= _BV(3);

	_delay_ms(300);

	PORTB &=~_BV(3);
}

void token_off(){
	PORTB |= _BV(4);

	_delay_ms(300);

	PORTB &=~_BV(4);	
}


void basket_on(){
	PORTB |= _BV(5);

	_delay_ms(600);

	PORTB &=~_BV(5);
}

void basket_off(){
	PORTD |= _BV(7);

	_delay_ms(600);

	PORTD &=~_BV(7);
}




/*------------モータ--------------*/
/*
	motaA:左モーター
	motaB:右モーター
*/

void motaA_front(){

	OCR0A = 255;  //PB3-AHI
	OCR0B = 0;    //PB4-BHI
}

void motaA_back(){	
	OCR0A = 0;  
	OCR0B = 255; 
}

void motaA_stop(){
	OCR0A = 0xff;  
	OCR0B = 0xff; 

}

void motaB_front(){
	OCR2A = 255;  //PD6-AHI
	OCR2B = 0;    //PD7-BHI
}

void motaB_back(){
	OCR2A = 0;
	OCR2B = 255; 
}

void motaB_stop(){
	OCR2A = 0xff;  
	OCR2B = 0xff; 
}

	//上下機構モーター
int motaj_up(int s){
	OCR1A = s;  //PD5-
	OCR1B = 0;  //PD4
}

int motaj_down(int s){
	OCR1A = 0;  
	OCR1B = s; 
}

int motaj_stop(){
	OCR1A = 255;  
	OCR1B = 255; 
}

/*-------------アナログ速度変化------------*/
int analog_up_down(){
	if(IIR_y(analog_y * 2) == 2){

		motaj_up(150);
	}
	else if(IIR_y(analog_y * 2) == 1){
		motaj_up(200);
	}
	else if(IIR_y(analog_y * 2) == 0){
		motaj_up(250);
	}
	else if(IIR_y(analog_y * 2) == 5){
		motaj_down(150);
	}
	else if(IIR_y(analog_y * 2) == 6){
		motaj_down(200);
	}
	else if(IIR_y(analog_y * 2) == 7){
		motaj_down(250);
	}
	else {
		motaj_stop();
	}
}
/*
int analog_lr(){
	if(IIR_x(analog_x * 2) == 2){

		motaA_front(150);
	}
	else if(IIR_x(analog_x * 2) == 1){
		motaA_front(200);
	}
	else if(IIR_x(analog_x * 2) == 0){
		motaA_front(250);
	}
	else if(IIR_x(analog_x * 2) == 5){
		motaA_back(150);
	}
	else if(IIR_x(analog_x * 2) == 6){
		motaA_back(200);
	}
	else if(IIR_x(analog_x * 2) == 7){
		motaA_back(250);
	}
	else {
		motaA_stop();
	}

}
*/

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

int IIR_x(int n){
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


/*-----------メイン-------------*/

int main(void){

	char buf[6];
	int motaA_front_flag = 0, motaA_back_flag = 0;
	int i, j;

	DDRA = 0b00000000;
	DDRB = 0b11111111;
	DDRC = 0b00000000;
	DDRD = 0b11111111;

	// OCR0A OCR0B の設定
	TCCR0A = 0b10100011;  
	TCCR0B = 0b00000001;
	// OCR1A OCR1B の設定
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	// OCR2A OCR2B の設定
	TCCR2A = 0b10100011;
	TCCR2B = 0b00000001;

	buzzer_on();
	_delay_ms(500);

	usart_init(MYUBRR);   // USART設定

    sei();    //割り込み許可(許可しないとPSコントローラーの信号が受けれない)
	
	buzzer_off();

	while(1){
/*---------強制停止---------*/
		if(ps_r1()){
			while(1){
				buzzer_times(2);
				motaA_stop();
				motaB_stop();
				motaj_stop();
			}
		}


/*---------------足回り------------------*/
		if(ps_top()){
			if(motaA_front_flag == 0){
				for(i = 0; i < 50; i++){
					motaA_front(205 + i);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");

					motaA_front_flag = 1;
				}
			}
	
			else {
				motaA_front(255);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));					
					usart_sendStr(" \r\n");
			}
		}

		else if(ps_bottom()){
			if(motaA_back_flag == 0){
				for(i = 0; i < 100; i++){
					motaA_back(155 + i);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");
				}
				motaA_back_flag = 1;
			}
			else {
				motaA_back(255);

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}
		}
		
		else {
			if(motaA_front_flag == 1){
				for(j = 0; j < 100; j++){
					motaA_front(255 - j);
					_delay_ms(10);

					usart_sendStr("OCR0A= ");
					usart_sendStr(intToStr(OCR0A,buf));
					usart_sendStr(" OCR0B= ");
					usart_sendStr(intToStr(OCR0B,buf));
					usart_sendStr(" \r\n");
				}
				motaA_front_flag = 0;
			}

			else {
				motaA_stop();
				
				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}


			if(motaA_back_flag == 1){
				for(j = 0; j < 100; j++){
					motaA_back(255 - j);
					_delay_ms(10);

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
				}
				motaA_back_flag = 0;
			}
			else {
				motaA_stop();

				usart_sendStr("OCR0A= ");
				usart_sendStr(intToStr(OCR0A,buf));
				usart_sendStr(" OCR0B= ");
				usart_sendStr(intToStr(OCR0B,buf));
				usart_sendStr(" \r\n");
			}

		}

		if(ps_triangle()){
			motaB_front(255);
		}

		else if(ps_cross()){
			motaB_back(255);
		}

		else {
			motaB_stop();
		}

/*---------------上下機構----------------*/
		//上昇
		if(ps_l1()){

			analog_up_down();

			usart_sendStr("OCR1A= ");
			usart_sendStr(intToStr(OCR1A,buf));
			usart_sendStr(" OCR1B= ");
			usart_sendStr(intToStr(OCR1B,buf));
			usart_sendStr(" OCR0A= ");
			usart_sendStr(intToStr(OCR0A,buf));
			usart_sendStr(" OCR0B= ");
			usart_sendStr(intToStr(OCR0B,buf));
			
		}
		else {

			motaj_stop();

		}





		usart_sendStr(" analog_y = ");
		usart_sendStr(intToStr(IIR_y(analog_y * 2),buf));
		usart_sendStr("  ");
		usart_sendStr("analog_x = ");
		usart_sendStr(intToStr(IIR_y(analog_x * 2),buf));
		usart_sendStr("\r\n");
		
	}
//	return 0;
}
