/*  ATmega644P専用プログラム  */
/*  AVR PlayStationController */
/*  Dualshock2対応            */

/*
   SwitchRecv[]のカッコには0から5まで入る。
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
		アナログスティックRのx軸0～255（中心127）

	SwitchRecv[3]
		アナログスティックRのy軸0～255（中心127）

	SwitchRecv[4]
		アナログスティックLのx軸0～255（中心127）

	SwitchRecv[5]
		アナログスティックLのy軸0～255（中心127）
*/


#define  F_CPU 8000000       //クロックを8MHzに設定　これを設定してないと_delay_ms()が使えない

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "yama_io.h"

#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTEの指定BITに1をセット
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTEの指定BITをクリア


/* PSコントローラーボタン定義 */
#define up         SwitchRecv[0]==0x10
#define down       SwitchRecv[0]==0x40
#define right      SwitchRecv[0]==0x20
#define left       SwitchRecv[0]==0x80

#define triangle   SwitchRecv[1]==0x10
#define cross      SwitchRecv[1]==0x40
#define circle     SwitchRecv[1]==0x20
#define square     SwitchRecv[1]==0x80

#define l1         SwitchRecv[1]==0x04
#define r1	   SwitchRecv[1]==0x08
#define l2	   SwitchRecv[1]==0x01
#define r2	   SwitchRecv[1]==0x02
#define l3	   SwitchRecv[0]==0x02	//L3, R3はアナログスティックの押しこみボタン
#define r3	   SwitchRecv[0]==0x04

#define start	   SwitchRecv[0]==0x08
#define select     SwitchRecv[0]==0x01

#define analog_x   SwitchRecv[2]   // 左0 < 中心127 < 右255 
#define analog_y   SwitchRecv[3]   // 上0 < 中心127 < 下255

#define analog_l_x   SwitchRecv[4]   // 左0 < 中心127 < 右255 
#define analog_l_y   SwitchRecv[5]   // 上0 < 中心127 < 下255


volatile uint16_t SwitchRecv[8]; //SwitchRecv[]をグローバル変数で宣言


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

/* メインプログラム */
int main(void){
	DDRA = 0xff;
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0x00;

	int center_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int analog_up, analog_down, analog_right, analog_left;

    	usart_init(MYUBRR);   // USART設定
   	//adc_init();           // ADConverter設定

	//int ad,ad2,ad3;
    	char buf[6];

	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;

    	sei();    //割り込み許可(許可しないとPSコントローラーの信号が受けれない)

    	//ANALOGが押されてないとノイズが乗るのでANALOGを押しスタートを押すまでは待機
	while(analog_x == 0 || analog_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");
		//stop();
	}

	//動作確認のためブザー使ったら(・∀・)ｲｲﾈ!!？
	PORTA = 0x00;   
	_delay_ms(1000);
	PORTA = 0x00;


    	while(1){
		// SELECT+START同時押しで、アナログスティックのX, Yの中心位置を初期化
		if(SwitchRecv[0]==0x09){
			usart_sendStr("Initialize center\r\n");
			center_x = 118;
			center_y = 132;
		}
		// アナログスティックの中心位置を変更
		if(select){
			usart_sendStr("PUSH SELECT");
			center_x = analog_x;
			center_y = analog_y;
		}

		// ここより下がプレステコントローラー制御命令
		if(analog_y <= center_y - 80){    //center_yから80引いているのはｱﾅﾛｸﾞｽﾃｨｯｸを約45°ずつで分けるため
			analog_up = 0xff - (analog_y * 2);
//			straight(analog_up);
			usart_sendStr("UP ");
		}
		else if(analog_y >= center_y + 80){
			analog_down = (analog_y * 2) - 0xff;
//			back(analog_down);
			usart_sendStr("DOWN ");
		}

		else if((analog_x <= center_x - 60) && analog_y){
			analog_left = 0xff - (analog_x * 2);
//			roll_left(analog_left);
			usart_sendStr("LEFT ");
		}
		else if((analog_x >= center_x + 60) && analog_y){
			analog_right = (analog_x * 2) - 0xff;
//			roll_right(analog_right);
			usart_sendStr("RIGHT ");
		}

		else{
//			stop();
			usart_sendStr("STOP ");
		}

		
		//デバッグ用
		//0が帰ってきた場合スペースが表示される
		/*
		usart_sendStr(intToStr(analog_x,buf));
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_y,buf));
		usart_sendStr(" "); 
   		usart_sendStr(intToStr(analog_up,buf));     
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_down,buf));  
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_left,buf));
		usart_sendStr(" ");   
		usart_sendStr(intToStr(analog_right,buf));
		usart_sendStr(" ");   
		usart_sendStr("cx");
		usart_sendStr(intToStr(center_x,buf));
		usart_sendStr(" cy");   
		usart_sendStr(intToStr(center_y,buf)); 
		*/
	
		//ボタン確認　デバッグ用

		
		usart_sendStr("  ");
		usart_sendStr("L_X:"); 
 		usart_sendStr(intToStr(SwitchRecv[4],buf)); 
		usart_sendStr("  ");
		usart_sendStr("L_Y:"); 
 		usart_sendStr(intToStr(SwitchRecv[5],buf));
		usart_sendStr("  ");
		usart_sendStr("R_X:");
  	    usart_sendStr(intToStr(SwitchRecv[2],buf));
		usart_sendStr("  "); 
		usart_sendStr("R_Y:"); 
	 	usart_sendStr(intToStr(SwitchRecv[3],buf));

		usart_sendStr("  "); 
	 	usart_sendStr(intToStr(SwitchRecv[0],buf));
		usart_sendStr("  ");
 		usart_sendStr(intToStr(SwitchRecv[1],buf)); 

		usart_sendStr("\r\n"); // 改行
		
		
  	}
}

void rail2_up(int n)
{

}

void rail2_down(int n)
{

}

void rail1_front(int n)
{

}

void rail1_back(int n)
{

}
