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

/**********モーター関数**********/
void top(int s){
	OCR0A = s;
	OCR0B = 0x00;
}

void down(int s){
	OCR0A = 0x00;
	OCR0B = s;
}

void right(int s){
	OCR2A = s;
	OCR2B = 0x00;
}

void left(int s){
	OCR2A = 0x00;
	OCR2B = s;
}

void stop_up(){
	OCR0A = 0xff;
	OCR0B = 0xff;
}

void stop_side(){
	OCR2A = 0xff;
	OCR2B = 0xff;
}

/**********初期位置へ**********/
int var1, var2;

void wwww(int s){

	var1 = 0;
	var2 = 0;

	while(1){
		if(!var1 && right_touch()){
			var1 = 1;
			stop_side();
		}
		else{
			if(var1 == 1){
				stop_side();
			}
			else {
				left(s);
				var1 = 0;
			}
		}

		if(!var2 && down_touch()){
			var2 = 1;
			stop_up();
		}
		else{
			if(var2 == 1){
				stop_up();
			}
			else {
				down(s);
				var2 = 0;
			}
		}

		if(var1 == 1 && var2 == 1){
			break;
		}
	}
}

/**********PORT配置**********/
// 644Pのとき

// PB0: タッチセンサー(上)
// PB1: タッチセンサー(下)
// PB2: タッチセンサー(右)
// PB3: モーター(上)
// PB4: モーター(下)
// PB5: タッチセンサー(左)

// PC1: 
// PC2: 
// PC3:
// PC4:
// PC5:

// PD2: ブザー
// PD3: モーター(左)
// PD4: パトランプ
// PD5: レーザー
// PD6: モーター(左)
// PD7: モーター(右)



/**********メイン関数**********/
int main(){

	DDRA = 0b00000000;
	DDRB = 0b00011000;
	DDRD = 0b11111111;
	DDRC = 0b00000000;

    usart_init(MYUBRR);   // USART設定
   	//adc_init();           // ADConverter設定

	//int ad,ad2,ad3;
//    char buf[6];
	
	int s = 255;// モーター数値
	int sig_up = 0, sig_side = 0; 
	int center_r_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_r_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int center_l_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_l_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;

	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
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


	while(1){

/*----初期位置へ----*/
		if(select){
			wwww(s);
		}

/*----レーザー----*/
		if(ps_circle() && sig_up == 0 && sig_side == 0){
			PORTD |= _BV(5);


	/*----当たり判定----*/
			if(PINC &_BV(1)){

				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);

			}
			else if(PINC &_BV(2)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(3)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(4)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);


			}
			else if(PINC &_BV(5)){
				PORTD |= _BV(2)|_BV(4);
				_delay_ms(500);
				PORTD &= ~_BV(2) & ~_BV(4);

			}
			else if(!(PINC & 0xd3)){

				_delay_ms(500);

			}
		}
		else {
			PORTD &= ~_BV(5);
			_delay_ms(50);			
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
*/
		// ここより下がプレステコントローラー制御命令
		if(analog_l_y <= center_l_y - 60)//center_yから80引いているのはｱﾅﾛｸﾞｽﾃｨｯｸを約45°ずつで分けるため
		{
			sig_up  = 1;

			analog_l_up = 0xff - (analog_l_y * 2);

			top(analog_l_up);
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			sig_up = 1;

			analog_l_down = (analog_l_y * 2) - 0xff;

			down(analog_l_down);
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

			analog_l_left = 0xff - (analog_l_x * 2);

			left(analog_l_left);

			usart_sendStr("UP ");
		}
		else if(analog_l_x >= center_l_x + 60)
		{
			sig_side = 1;

			analog_l_right = (analog_l_x * 2) - 0xff;

			right(analog_l_right);

			usart_sendStr("DOWN ");
		}
		else
		{
			sig_side = 0;

			stop_side();
			usart_sendStr("STOP ");
		}





/*		if(ps_top()){
			top(s);
		}
		else if(ps_bottom()){
			down(s);
		}
		else {
			stop_up();
		}

		if(ps_right()){
			right(s);
		} 
		else if(ps_left()){
			left(s);
		}
		else {
			stop_side();
		}
*/

/*----タッチセンサーでとまる----*/
		if(up_touch()){
			stop_up();
			_delay_ms(200);
			down(s);
			while(up_touch());
			_delay_ms(100);
		}

		if(down_touch()){
			stop_up();
			_delay_ms(200);
			top(200);
			while(down_touch());
			_delay_ms(100);
		}

		if(left_touch()){
			stop_side();
			_delay_ms(200);
			left(s);
			while(left_touch());
			_delay_ms(100);
		}

		if(right_touch()){
			stop_side();
			_delay_ms(200);
			right(s);
			while(right_touch());
			_delay_ms(100);
		}



	}
}
