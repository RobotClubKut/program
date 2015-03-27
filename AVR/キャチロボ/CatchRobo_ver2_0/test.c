/* キャチロボ用プログラム
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

/*-------- ポート定義 --------*/
/* 
   上下モータ AHI : OC0B
   上下モータ BHI : OC0A
   上下モータ ALI : PORTB1
   上下モータ BLI : PORTB0

   前後モータ AHI : OC2B
   前後モータ BHI : OC2A
   前後モータ ALI : PORTC1
   前後モータ BLI : PORTC0

   サーボモータ 右 : OC1B 
   サーボモータ 左 : OC1A

   リミットスイッチ前進限界 : PORTA5
   リミットスイッチ後進限界 : PORTA6
   リミットスイッチ上昇限界 : PORTA7
   リミットスイッチ下降限界 : PORTC7

   電磁弁 : PORTC5    
*/

/*-------- コントローラボタン割り当て --------*/
/*
○ : サーボモータ回転（押している間アームが傾く、離すと戻る）
□ : 電磁弁（押している間押し出し、離すと戻る）

アナログスティック右 : 上下モータ（前に倒すと上昇、後ろに倒すと下降）
アナログスティック左 : 前後モータ（前に倒すと前進、後ろに倒すと後進）

R1,R2 : 上下モータ速度変化（どちらかを押している間低速、両方離すと高速）
L1,L2 : 前後モータ速度変化（どちらかを押している間低速、両方離すと高速）

START : プログラムスタートボタン(アナログボタンが押されていないと反応しない)

SELECT : アナログスティック基準変更（その時のアナログスティックの位置が基準となる）

SELECT + START : アナログスティック基準初期化（プログラム規定値が基準となる）

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
#define up         (SwitchRecv[0]&0x10)==0x10
#define down       (SwitchRecv[0]&0x40)==0x40
#define right      (SwitchRecv[0]&0x20)==0x20
#define left       (SwitchRecv[0]&0x80)==0x80

#define triangle   (SwitchRecv[1]&0x10)==0x10
#define cross      (SwitchRecv[1]&0x40)==0x40
#define circle     (SwitchRecv[1]&0x20)==0x20
#define square     (SwitchRecv[1]&0x80)==0x80

#define l1     (SwitchRecv[1]&0x04)==0x04
#define r1	   (SwitchRecv[1]&0x08)==0x08
#define l2	   (SwitchRecv[1]&0x01)==0x01
#define r2	   (SwitchRecv[1]&0x02)==0x02
#define l3	   (SwitchRecv[0]&0x02)==0x02	//L3, R3はアナログスティックの押しこみボタン
#define r3	   (SwitchRecv[0]&0x04)==0x04

#define start	   (SwitchRecv[0]&0x08)==0x08
#define select     (SwitchRecv[0]&0x01)==0x01

#define analog_r_x   SwitchRecv[2]   // 左0 < 中心127 < 右255 
#define analog_r_y   SwitchRecv[3]   // 上0 < 中心127 < 下255

#define analog_l_x   SwitchRecv[4]   // 左0 < 中心127 < 右255 
#define analog_l_y   SwitchRecv[5]   // 上0 < 中心127 < 下255

//センサポート定義
#define PR0 !PINA_0		//一番前
#define PR1 !PINA_1
#define PR2 !PINA_2
#define PR3 !PINA_3
#define PR4 !PINA_4

//リミットスイッチ定義
#define RS_F PINA_5		//リミットスイッチ前進限界
#define RS_B PINA_6		//リミットスイッチ後進限界
#define RS_U PINA_7		//リミットスイッチ上昇限界
#define RS_D PINC_7 	//リミットスイッチ下降限界

//スピード定義
#define LOWSP 100
#define HIGHSP 150

volatile uint16_t SwitchRecv[8]; //SwitchRecv[]をグローバル変数で宣言
volatile int rail0_flag = 0;
volatile int rail1_flag = 0;


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

	void rail0_up(int);
	void rail0_down(int);
	void rail0_stop(void);
	void rail1_front(int);
	void rail1_back(int);
	void rail1_stop(void);
	void servo1a_set(int32_t);	
	void servo1b_set(int32_t);

	DDRA = 0x00;
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0x7f;

	int center_r_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_r_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int center_l_x = 118;   //127 //125 //118 //131 //184    //コントローラーによって差がでるので微調整必要
	int center_l_y = 132;   //127 //127 //122 //132 //138　　//コントローラーによって差がでるので微調整必要
	int analog_l_up, analog_l_down, analog_l_right, analog_l_left;
	int analog_r_up, analog_r_down, analog_r_right, analog_r_left;
	int up_f = 0;
	int down_f = 0;

    usart_init(MYUBRR);   // USART設定
   	//adc_init();           // ADConverter設定

	//int ad,ad2,ad3;
   	char buf[6];

	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;
	TCCR1A = 0b10100010;	//高速PWM(TOP値 = ICR1)
							//比較一致でLow、BOTTOM(TCNT = 0)でHigh
	TCCR1B = 0b00011010;	//8分周
	ICR1 = 20000;			//TCNT = 20000でTCNT = 0
	

    sei();    //割り込み許可(許可しないとPSコントローラーの信号が受けれない)
	servo1b_set(0);
	servo1a_set(160);
	OCR0A = 0;
	OCR0B = 0;
	PORTB_0 = 0;
	PORTB_1 = 0;
	OCR2A = 0;
	OCR2B = 0;
	PORTC_0 = 0;
	PORTC_1 = 0;
	
    //ANALOGが押されてないとノイズが乗るのでANALOGを押しスタートを押すまでは待機
	while(analog_r_x == 0 || analog_r_y == 0)usart_sendStr("PUSH ANALOG\r\n");
 	while(start == 0){
		usart_sendStr("PUSH START\r\n");
		//stop();
	}


    	while(1){
		// SELECT+START同時押しで、アナログスティックのX, Yの中心位置を初期化
		if(SwitchRecv[0]==0x09){
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
			analog_l_up = 0xff - (analog_l_y * 2);
			if(l1||l2)
			{
				rail1_front(analog_l_up/2);
			}
			else
			{
				rail1_front(analog_l_up);
			}
			usart_sendStr("UP ");
		}
		else if(analog_l_y >= center_l_y + 60)
		{
			analog_l_down = (analog_l_y * 2) - 0xff;
			if(l1||l2)
			{
				rail1_back(analog_l_down/2);
			}
			else
			{
				rail1_back(analog_l_down);
			}
			usart_sendStr("DOWN ");
		}
		else
		{
			rail1_stop();
			usart_sendStr("STOP ");
		}
		
		if(analog_r_y <= center_r_y - 60)//center_yから80引いているのはｱﾅﾛｸﾞｽﾃｨｯｸを約45°ずつで分けるため
		{
			analog_r_up = 0xff - (analog_r_y * 2);
			if(r1||r2)
			{
				rail0_up(analog_r_up/3);
			}
			else
			{
				rail0_up(analog_r_up);
			}
			usart_sendStr("UP ");
		}
		else if(analog_r_y >= center_r_y + 60)
		{
			analog_r_down = (analog_r_y * 2) - 0xff;
			if(r1||r2)
			{
				rail0_down(analog_r_down/3);
			}
			else
			{
				rail0_down(analog_r_down);
			}
			usart_sendStr("DOWN ");
		}
		else
		{
			rail0_stop();
			usart_sendStr("STOP ");
		}

		//サーボ制御
		if((SwitchRecv[1]&0x20)==0x20)
		{
			servo1a_set(0);
			servo1b_set(160);
		}
		else
		{
			servo1a_set(160);
			servo1b_set(0);
		}

		// 電磁弁制御
		if(square)
		{
			solenoid_side(1);
		}
		else
		{
			solenoid_side(0);
		}
		

		//自動制御
		if(up)
		{
			if(up_f == 0)
			{
				up_f = 1;
				moter_front_auto();
			}
		}
		else
		{
			up_f = 0;
		}
		if(down)
		{
			if(down_f == 0)
			{
				down_f = 1;
				moter_back_auto();
			}
		}
		else
		{
			down_f = 0;
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
	 	usart_sendStr(intToStr(analog_r_up,buf));
		usart_sendStr("  ");
 		usart_sendStr(intToStr(SwitchRecv[1],buf)); 

		usart_sendStr("\r\n"); // 改行
		
		
  	}
}



/*-----------------------------上下レール制御関数------------------------------*/

//上下レール上昇用
void rail0_up(int n)
{
	if(RS_U == 1)
	{
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 1;
		PORTB_1 = 1;
		return;
	}
	if(rail0_flag != 1)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR0A = 0;
			OCR0B = n;
			PORTB_0 = 1;
			PORTB_1 = 0;
			_delay_ms(1);
		}
		rail0_flag = 1;
	}
	OCR0A = 0;
	OCR0B = n;
	PORTB_0 = 1;
	PORTB_1 = 0;
}
//上下レール下降用
void rail0_down(int n)
{	
	if(RS_D == 1)
	{
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 1;
		PORTB_1 = 1;
		return;
	}
	if(rail0_flag != 2)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR0A = n;
			OCR0B = 0;
			PORTB_0 = 0;
			PORTB_1 = 1;
			_delay_ms(1);
		}
		rail0_flag = 2;
	}
	OCR0A = n;
	OCR0B = 0;
	PORTB_0 = 0;
	PORTB_1 = 1;
}
//上下レール停止用
void rail0_stop()
{
	if(rail0_flag != 3)
	{
		_delay_ms(50);
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 0;
		PORTB_1 = 0;
		rail0_flag = 3;
	}
	OCR0A = 0;
	OCR0B = 0;
	PORTB_0 = 1;
	PORTB_1 = 1;
}


/*-----------------------------前後レール制御関数------------------------------*/

//前後レール前進用
void rail1_front(int n)
{
	if(RS_F == 1)
	{
		OCR2A = 0;
		OCR2B = 0;
		PORTC_0 = 1;
		PORTC_1 = 1;
		return;
	}
/*	if(rail1_flag != 1)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR2A = n;
			OCR2B = 0;
			PORTC_0 = 0;
			PORTC_1 = 1;
			_delay_ms(1);
		}
		rail1_flag = 1;
	}
	*/
	OCR2A = n;
	OCR2B = 0;
	PORTC_0 = 0;
	PORTC_1 = 1;
}
//前後レール後進用
void rail1_back(int n)
{
	if(RS_B == 1)
	{
		OCR2A = 0;
		OCR2B = 0;
		PORTC_0 = 1;
		PORTC_1 = 1;
		return;
	}
	/*
	if(rail1_flag != 2)
	{
		int i;
		for(i = 0;i < n;i++)
		{
			OCR2A = 0;
			OCR2B = n;
			PORTC_0 = 1;
			PORTC_1 = 0;
			_delay_ms(1);
		}
		rail1_flag = 2;
	}
	*/
	OCR2A = 0;
	OCR2B = n;
	PORTC_0 = 1;
	PORTC_1 = 0;
}
//前後レール停止用
void rail1_stop()
{
	/*
	if(rail1_flag != 3)
	{
		_delay_ms(50);
		OCR0A = 0;
		OCR0B = 0;
		PORTB_0 = 0;
		PORTB_1 = 0;
		rail1_flag = 3;
	}
	*/
	OCR2A = 0;
	OCR2B = 0;
	PORTC_0 = 1;
	PORTC_1 = 1;
}


void servo1b_set(int32_t angle_deg)
{
	OCR1B = 25*angle_deg/3+1000;
}
void servo1a_set(int32_t angle_deg)
{
	OCR1A = 25*angle_deg/3+1000;
}



/*-----------------------------前後モータ自動制御関数------------------------------*/

//モータ1ステップ前進
void moter_front_auto()
{
	if(RS_F == 1)							//レールが伸びきっていたら実行しない
		return;
	while((PR4 == 1)&&(RS_F == 0))			//レールがセンサ範囲より後ろでも次のセンサまで移動
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:10000\r\n"); 
	}
	while((PR3 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:01000\r\n"); 
	}
	while((PR2 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00100\r\n"); 
	}
	while((PR1 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00010\r\n"); 
	}
	while((PR0 == 1)&&(RS_F == 0))
	{
		rail1_front(LOWSP);
		usart_sendStr("zensin:00001\r\n"); 
	}

	//チャタリング防止
	_delay_ms(10);

	// センサが反応しない場合は黒線間を移動中だから最高速で移動
	while((PR0 == 0)&&(PR1 == 0)&&(PR2 == 0)&&(PR3 == 0)&&(PR4 == 0)&&(RS_F == 0))
	{
		rail1_front(HIGHSP);
		usart_sendStr("zensin:00000\r\n"); 
	}
	rail1_stop();
	_delay_ms(10);
	// しっかり停止するためにスピードを落とす
	while((PR4 == 1)&&(PR3 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(RS_F == 0))
		rail1_front(LOWSP);
	while(RS_F == 0)
	{
		rail1_stop();
		_delay_ms(100);
		if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_stop();
			usart_sendStr("zensin:01110\r\n");
			return;
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:10000\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:01100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11000\r\n");
		}

		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00111\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00110\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00001\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00011\r\n");
		}
		else
		{
			rail1_stop();
			usart_sendStr("zensin:else\r\n");
			return;
		}
	}
}
//モータ1ステップ後進
void moter_back_auto()
{
	if(RS_B == 1)							//レールが縮みきっていたら実行しない
		return;
	while((PR0 == 1)&&(RS_B == 0))			//レールがセンサ範囲より前でも次のセンサまで移動
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:10000\r\n");
	}
	while((PR1 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:01000\r\n");
	}
	while((PR2 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00100\r\n");
	}
	while((PR3 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00010\r\n");
	}
	while((PR4 == 1)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
		usart_sendStr("kousin:00001\r\n");
	}

	//チャタリング防止
	_delay_ms(10);
	// センサが反応しない場合は黒線間を移動中だから最高速で移動
	while((PR0 == 0)&&(PR1 == 0)&&(PR2 == 0)&&(PR3 == 0)&&(PR4 == 0)&&(RS_B == 0))
	{
		rail1_back(HIGHSP);
		usart_sendStr("kousin:00000\r\n");
	}
	rail1_stop();
	_delay_ms(10);
	// しっかり停止するためにスピードを落とす
	while((PR0 == 1)&&(PR1 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 1)&&(PR1 == 1)&&(PR2 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 1)&&(PR1 == 1)&&(PR2 == 1)&&(PR3 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while((PR0 == 0)&&(PR1 == 1)&&(PR2 == 1)&&(PR3 == 0)&&(RS_B == 0))
	{
		rail1_back(LOWSP);
	}
	while(RS_B == 0)
	{
		rail1_stop();
		_delay_ms(100);
		if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_stop();
			usart_sendStr("zensin:01110\r\n");
			return;
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:10000\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 1)&&(PR2 == 1)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:01100\r\n");
		}
		else if((PR4 == 1)&&(PR3 == 1)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 0))
		{
			rail1_front(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:11000\r\n");
		}

		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00111\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 1)&&(PR1 == 1)&&(PR0 == 0))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00110\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 0)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00001\r\n");
		}
		else if((PR4 == 0)&&(PR3 == 0)&&(PR2 == 0)&&(PR1 == 1)&&(PR0 == 1))
		{
			rail1_back(LOWSP);
			_delay_ms(100);
			usart_sendStr("zensin:00011\r\n");
		}
		else
		{
			rail1_stop();
			usart_sendStr("zensin:else\r\n");
			return;
		}
	}
}

/*-----------------------------電磁弁制御------------------------------*/
// サイド2つの電磁弁
void solenoid_side(int sl)
{
	PORTC_5 = sl;
}

// バックの電磁弁
void solenoid_back()
{

}
