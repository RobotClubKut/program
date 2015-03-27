/*ライントレースマシン制御プログラム*/
//8MHz

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>


#define sbi(BYTE,BIT) BYTE|=_BV(BIT) // BYTEの指定BITに1をセット
#define cbi(BYTE,BIT) BYTE&=~_BV(BIT) // BYTEの指定BITをクリア


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

/* ライントレース初期宣言 */
/* ライントレースセンター1枚目 */
#define f_left3  PINA&_BV(6)
#define f_left2  PINA&_BV(5)                                                                                                                                                                                                           
#define f_left1  PINA&_BV(4)
#define f_center PINA&_BV(3)
#define f_right1 PINA&_BV(2)
#define f_right2 PINA&_BV(1)
#define f_right3 PINA&_BV(0)

#define r_left3  PINC&_BV(0)
#define r_left2  PINC&_BV(1)
#define r_left1  PINC&_BV(2)
#define r_center  PINC&_BV(3)
#define r_right1  PINC&_BV(4)
#define r_right2  PINC&_BV(5)
#define r_right3  PINC&_BV(6)

/* ライントレースサイド */

/*void lt_straight_Mk2(){
		if(f_center){
			PORTB = 0x00;
			_delay_ms(5);
			if(f_center) straight();
		}


		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right(0xff - 30);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left(0xff - 30);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right(0xff - 20);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left(0xff - 20);
		}
		else if(f_center){
			PORTB = 0x00;
			_delay_ms(3);
		}
		else{
			//motor_R(0xff,0xff);
			//motor_L(0xff,0xff);
		}
}*/

int img_boad1(){//仮想ライントレース基板

	if(f_center){
		_delay_us(1000);
		if(f_center) return 0;
	}
	if(f_right2){
		_delay_us(1000);
		if(f_right2) return 2;
	}
	else if(f_left2){
		_delay_us(1000);
		if(f_left2) return -2;
	}
	else if(f_right1){
		_delay_us(1000);
		if(f_right1) return 1;
	}
	else if(f_left1){
		_delay_us(1000);
		if(f_left1) return -1;
	}
	else if(f_center){
		_delay_us(1000);
		if(f_center) return 0;
	}
	else return 0;
}
int img_boad2(){//仮想ライントレース基板
	if(r_center){
		_delay_us(1000);
		if(r_center) return 0;
	}
	if(r_right2){
		_delay_us(1000);
		if(r_right2) return 2;
	}
	else if(r_left2){
		_delay_us(1000);
		if(r_left2) return -2;
	}
	else if(r_right1){
		_delay_us(1000);
		if(r_right1) return 1;
	}
	else if(r_left1){
		_delay_us(1000);
		if(r_left1) return -1;
	}
	else if(r_center){
		_delay_us(1000);
		if(r_center) return 0;
	}
	else return 0;
}

int place(i,j){
	int p;
	return p = 2*i+j;
}

void lt_straight(){
		if(f_center){
			_delay_ms(5);
			if(f_center) straight(0xff/2);
		}

		if(f_right2){
			_delay_ms(3);
			if(f_right2) turn_right(0xff-20);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left(0xff-20);
		}
		else if(f_right1){
			_delay_ms(1);
			if(f_right1) turn_right(0xef-20);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left(0xef-20);
		}
		else if(f_center){
			_delay_ms(3);
			if(f_center) straight(0xff-20);
		}
		else straight(0xff);
}

void lt_straight2(){
		if(r_center){
			_delay_ms(5);
			if(r_center) straight(0xff/2);
		}

		if(r_right2){
			_delay_ms(3);
			if(r_right2) turn_right(0xff-20);
		}
		else if(r_left2){
			_delay_ms(3);
			if(r_left2) turn_left(0xff-20);
		}
		else if(r_right1){
			_delay_ms(1);
			if(r_right1) turn_right(0xef-20);
		}
		else if(r_left1){
			_delay_ms(1);
			if(r_left1) turn_left(0xef-20);
		}
		else if(r_center){
			_delay_ms(3);
			if(r_center) straight(0xff-20);
		}
		else straight(0xff);
}

void lt_back(int p){
		if(p == 0){
			r_straight(0xff);
		}

		if(p == 2){
			r_turn_right2(0xff-20);
		}
		else if(p == -2){
			r_turn_left2(0xff-20);
		}
		else if(p == 1){
			r_turn_right(0xef-20);
		}
		else if(p == -1){
			r_turn_left(0xef-20);
		}
		else if(p == 0){
			r_straight(0xff-20);
		}
		else r_straight(0xff);
}

/*モータードライバ制御命令(標準動作)*/

//高速ライントレース用
/*通常方式*/
void straight(int s){
	motor_R(s,0);
	motor_L(s,0);
}

void back(int s){
	motor_R(0,s);
	motor_L(0,s);
}

void turn_right(int s){
	motor_R(s-50,0);
	motor_L(s,0);
}

void turn_left(int s){
	motor_R(s,0);
	motor_L(s-50,0);
}

void roll_left(int s){
	motor_R(s,0);
	motor_L(0,s);
}

void roll_right(int s){
	motor_R(0,s);
	motor_L(s,0);
}

void stop(){
	motor_R(0,0);
	motor_L(0,0);
}

/*逆側回転時*/
void r_straight(int s){
	motor_R(0,s);
	motor_L(0,s);
}

void r_back(int s){
	motor_R(s,0);
	motor_L(s,0);
}

void r_turn_right(int s){
	motor_R(0,s);
	motor_L(0,s-50);
}

void r_turn_right2(int s){
	motor_R(0,s);
	motor_L(0,s-80);
}

void r_turn_right3(int s){
	motor_R(0,s);
	motor_L(0,s-100);
}

void r_turn_left(int s){
	motor_R(0,s-50);
	motor_L(0,s);
}

void r_turn_left2(int s){
	motor_R(0,s-80);
	motor_L(0,s);
}

void r_turn_left3(int s){
	motor_R(0,s-100);
	motor_L(0,s);
}

void r_roll_right(int s){
	motor_R(s,0);
	motor_L(0,s);
}

void r_roll_left(int s){
	motor_R(0,s);
	motor_L(s,0);
}


// 超音波センサー
// 1cm単位で数値が帰ってくる
int sonic_sensor(){
	int cnt = 0;
	int n = 0.0;
	int buf[6];

	DDRA = 0x40;    // PA1を出力ポート指定（このプログラムの場合はPA6,7も出力指定）
	sbi(PORTA,PA6); //超音波センサーの接続ポートがPA1
	_delay_us(5);
	cbi(PORTA,PA6);
	cnt = 0;

	DDRA = 0x00;	// PA1を入力ポート指定(このプログラムはPA6,7は出力指定)
	while(!(PINA & _BV(6))) TCNT1 = 0;
	while(PINA & _BV(6));

	n = TCNT1;
		
	cnt = n / 7.6598;	

	
//	usart_sendStr("TCNT1:"); // AD値を文字列にして送信
//  usart_sendStr(intToStr(cnt,buf)); // AD値を文字列にして送信
//  usart_sendStr("\r\n"); // 改行
	_delay_ms(10);
	//nop(2);

	return cnt;
}

void motor_R(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTB |= 0x01;
	}
	else{
		PORTB = 0x00;
		OCR0A = f;
		OCR0B = b;
	}
}

void motor_L(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTB |= 0x02;
	}
	else{
		PORTB = 0x00;
		OCR2A = f;
		OCR2B = b;
	}
}

/*90度回転*/
void rad90_r(){
	roll_right(0xaf);
	if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)
		while(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)_delay_ms(700);
	
	while(1){
		if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
			if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
				motor_R(0xff,0xff);
				motor_L(0xff,0xff);
				_delay_ms(200);
				return;
			}
			else{
				roll_left(0xaf);
				_delay_ms(100);
			}
		}
	}
}

void rad90_l(){
	roll_left(0xaf);
	if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)
		while(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1)_delay_ms(700);
	
	while(1){
		if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
			if(f_left3 || f_left2 || f_left1 || f_center || f_right3 || f_right2 || f_right1){
				motor_R(0xff,0xff);
				motor_L(0xff,0xff);
				_delay_ms(200);
				return;
			}
			else{
				roll_left(0xaf);
				_delay_ms(100);
			}
		}
	}
}

int main(){

	DDRA = 0x00;
	DDRC = 0x00;
	DDRB = 0xff;
	DDRD = 0xff;
	//int cnt=0;
	int c = 0;
	//int lf=0,rf=0;
	int s = 0xff;

	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
	TCCR1A = 0;  	  // OCR1A OCR1B の設定
	TCCR1B = 3;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;
	

	PORTB = 0x03;
	_delay_ms(1500);
	PORTB = 0x00;
	
	TCNT1 = 0;
	while(1){
		lt_back(place(img_boad2(),img_boad1()));
	}
	
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
	_delay_ms(5000);

	return 0;
}
