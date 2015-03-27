//#define F_CPU 32000000
#define F_CPU 32000000
#include <avr/io.h>
#include <util/delay.h>
#include "xkvr/clock.h"
#include "xkvr/usart.h"
#include "xkvr/adc.h"
#include "xkvr/interrupt.h"


//前側デジタルIO定義
/*
#define f_left3  PORTA.IN&_BV(7)
#define f_left2  PORTA.IN&_BV(6)
#define f_left1  PORTA.IN&_BV(5)
#define f_center PORTA.IN&_BV(4)
#define f_right1 PORTA.IN&_BV(3)
#define f_right2 PORTA.IN&_BV(2)
#define f_right3 PORTA.IN&_BV(1)
*/

//前AD変換用定義
#define f_left3  adc_convert(7)
#define f_left2  adc_convert(6)
#define f_left1  adc_convert(5)
#define f_center adc_convert(4)
#define f_right1 adc_convert(3)
#define f_right2 adc_convert(2)
#define f_right3 adc_convert(1)


#define s_lift0 adc_convert(1)
#define s_lift1 adc_convert(2)
#define s_lift2 adc_convert(3)

//後ろ側デジタル用IO定義
/*
#define r_left3  PORTB.IN&_BV(1)
#define r_left2  PORTB.IN&_BV(2)
#define r_left1  PORTB.IN&_BV(3)
#define r_center PORTB.IN&_BV(4)
#define r_right1 PORTB.IN&_BV(5)
#define r_right2 PORTB.IN&_BV(6)
#define r_right3 PORTB.IN&_BV(7)
*/

//後ろAD変換定義
#define r_left3  adc_convert(15)
#define r_left2  adc_convert(14)
#define r_left1  adc_convert(13)
#define r_center adc_convert(12)
#define r_right1 adc_convert(11)
#define r_right2 adc_convert(10)
#define r_right3 adc_convert(9)

#define SW1 PORTC.IN&_BV(0)
#define TS1 PORTC.IN&_BV(1)
#define LS0 PORTC.IN&_BV(2)

int line(char l3,char l2,char l1,char c,char r1,char r2,char r3){
	char m=0,p=0,s[7]={ l3, l2, l1, c, r1, r2, r3};
	
	for(int i=0;i < 7;i++){
		if(m<s[i]){
			m = s[i];
			p = i;
		}
	}
	return p-3;
}

int IIR(int n,char p){
	static int z[4][15]={0};//処理の後に代入させる
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[3][15] = {0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1][p] << 8) * a2;
	a1 = (z[0][p] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3][p] << 8) * b2;
	b1 = (z[2][p] << 8) * b1;
	
	z[1][p] = z[0][p];
	z[0][p] = n >> 2;
	z[3][p] = z[2][p];
	z[2][p] = add[0][p];
	
	add[0][p] = add[1][p] + (a0 >> 4);
	add[0][p] = add[0][p] >> 8;
	add[1][p] = (a1 >> 4) + b1 + add[2][p];
	add[2][p] = (a2 >> 4) - b2;
	
	return add[0][p];
}

void port_in(char n,char x){
	int i,cnt = 0;

	for(i = 1;cnt <= x;cnt ++){
		i *= 2;
	}

	i != i;//iの反転
	
	if(n == 'A'){
		PORTA.DIR = PORTA.DIR & i;
	}
	else if(n == 'B'){
		PORTB.DIR = PORTB.DIR & i;
	}
	else if(n == 'C'){
		PORTC.DIR = PORTC.DIR & i;
	}
	else if(n == 'D'){
		PORTD.DIR = PORTD.DIR & i;
	}
	else if(n == 'E'){
		PORTE.DIR = PORTE.DIR & i;
	}
	else if(n == 'F'){
		PORTF.DIR = PORTF.DIR & i;
	}
}

void test_port(char p,char n,int t){
	//push
	char heaven[6] = {PORTA.DIR,
					  PORTB.DIR,
					  PORTC.DIR,
					  PORTD.DIR,
					  PORTE.DIR,
					  PORTF.DIR};

	PORTA.DIR = 0xff;
	PORTB.DIR = 0xff;
	PORTC.DIR = 0xff;
	PORTD.DIR = 0xff;
	PORTE.DIR = 0xff;
	PORTF.DIR = 0xff;

	if(p == 'A'){
		PORTA.OUT = _BV(n);
	}
	else if(p == 'B'){
		PORTB.OUT = _BV(n);
	}
	else if(p == 'C'){
		PORTC.OUT = _BV(n);
	}
	else if(p == 'D'){
		PORTD.OUT = _BV(n);
	}
	else if(p == 'E'){
		PORTE.OUT = _BV(n);
	}
	else if(p == 'F'){
		PORTF.OUT = _BV(n);
	}

	_delay_ms(t);
	
	//pop
	PORTA.DIR = heaven[0];
	PORTB.DIR = heaven[1];
	PORTC.DIR = heaven[2];
	PORTD.DIR = heaven[3];
	PORTE.DIR = heaven[4];
	PORTF.DIR = heaven[5];
	
}

int img_boad1(){//仮想ライントレース基板
	if(f_center > 300){
		return 0;
	}
	if(f_right3 > 300){
		return 3;
	}
	else if(f_left3 > 300){
		return -3;
	}
	else if(f_right2 > 300){
		return 2;
	}
	else if(f_left2 > 300){
		return -2;
	}
	else if(f_right1 > 300){
		return 1;
	}
	else if(f_left1 > 300){
		return -1;
	}
	else if(f_center > 300){
		return 0;
	}
	else return 0;
}
int img_boad2(){//仮想ライントレース基板
	if(r_center > 300){
		return 0;
	}
	if(r_left3 > 300){
		return 3;
	}
	else if(r_right3 > 300){
		return -3;
	}
	else if(r_left2 > 300){
		return 2;
	}
	else if(r_right2 > 300){
		return -2;
	}
	else if(r_left1 > 300){
		return 1;
	}
	else if(r_right1 > 300){
		return -1;
	}
	else if(r_center > 300){
		return 0;
	}
	else return 0;
}

int place(i,j){
	int p;
	p = i;
	p += i;
	p += j;
	return p;
}

void lt_straight(char n){

		if(f_right2 > 300){
			if(n == 1)usart_printf(&USARTE0,"turn_right2\n");
			_delay_ms(5);
			turn_right2(0xdf);
		}
		else if(f_left2 > 300){
			if(n == 1)usart_printf(&USARTE0,"turn_left2\n");
			_delay_ms(3);
			turn_left2(0xdf);
		}
		else if(f_right1 > 300){
			if(n == 1)usart_printf(&USARTE0,"turn_right1\n");
			_delay_ms(3);
			turn_right1(0xdf);
		}
		else if(f_left1 > 300){
			if(n == 1)usart_printf(&USARTE0,"turn_left1\n");
			_delay_ms(1);
			turn_left1(0xdf);
		}
		else if(f_center > 300){
			if(n == 1)usart_printf(&USARTE0,"f_center\n");
			_delay_ms(3);
			straight(0xdf);
		}
		/*
		else{
			if(n == 1)usart_printf(&USARTE0,"other\n");
			straight(0xff);
		}*/
}

void lt_sl_straight(char n,int s){

		if(IIR(f_right2,12) >= 3 && IIR(f_right2,12) <= 4){
			if(n == 1)usart_printf(&USARTE0,"turn_right2\n");
			_delay_ms(5);
			turn_right2(s);
		}
		else if(IIR(f_left2,8) >= 3 && IIR(f_left2,8) <= 4){
			if(n == 1)usart_printf(&USARTE0,"turn_left2\n");
			_delay_ms(3);
			turn_left2(s);
		}
		else if(IIR(f_right1,11) >= 3 && IIR(f_right1,11) <= 4){
			if(n == 1)usart_printf(&USARTE0,"turn_right1\n");
			_delay_ms(3);
			turn_right1(s);
		}
		else if(IIR(f_left1,9) >= 3 && IIR(f_left1,9) <= 4){
			if(n == 1)usart_printf(&USARTE0,"turn_left1\n");
			_delay_ms(1);
			turn_left1(s);
		}
		else if(IIR(f_center,10) >= 3 && IIR(f_center,10) <= 4){
			if(n == 1)usart_printf(&USARTE0,"f_center\n");
			_delay_ms(3);
			straight(s);
		}
		/*
		else{
			if(n == 1)usart_printf(&USARTE0,"other\n");
			straight(0xff);
		}*/
}

void lt_back(int p,unsigned char s){
	switch(p){
	case -9:
		r_turn_left9(s);
		break;
	case -8:
		r_turn_left8(s);
		break;
	case -7:
		r_turn_left7(s);
		break;
	case -6:
		r_turn_left6(s);
		break;
	case -5:
		r_turn_left5(s);
		break;
	case -4:
		r_turn_left4(s);
		break;
	case -3:
		r_turn_left3(s);
		break;
	case -2:
		r_turn_left2(s);
		break;
	case -1:
		r_turn_left(s);
		break;
	case 0:
		r_straight(s);
		break;
	case 1:
		r_turn_right(s);
		break;
	case 2:
		r_turn_right2(s);
		break;
	case 3:
		r_turn_right3(s);
		break;
	case 4:
		r_turn_right4(s);
		break;
	case 5:
		r_turn_right5(s);
		break;
	case 6:
		r_turn_right6(s);
		break;
	case 7:
		r_turn_right7(s);
		break;
	case 8:
		r_turn_right8(s);
		break;
	case 9:
		r_turn_right9(s);
		break;
	}
}

void go(int n,int t,int s){	
	int p=s;
	int cnt = 0;
	while(cnt < n){
		if(IIR(f_right2,12) >= 3){
			if(IIR(f_left2,8) >= 3){
				if(IIR(f_right1,11) >= 3){
					if(IIR(f_left1,9) >= 3){
						if(IIR(f_center,10) >= 3){
							cnt++;					//フォトトランジスタ5つ反応でcntを+1
							straight(s);
							while(
							((IIR(f_center,10) >= 3) && 
							//(IIR(f_right2,12) >= 3) && 
							(IIR(f_right1,11) >= 3) && 
							(IIR(f_left2,8) >= 3)  
							//(IIR(f_left1,9) >= 3)
							)
							||
							((IIR(f_center,10) >= 3) && 
							(IIR(f_right2,12) >= 3) && 
							//(IIR(f_right1,11) >= 3) && 
							//(IIR(f_left2,8) >= 3) && 
							(IIR(f_left1,9) >= 3)
							)
							){}
							_delay_ms(t);
							while(cnt>=n) break;   //cntの数値がn(入力した値)
						}           //より大きくなったらbreakする
					}
				}
			}	
		}
		//usert送らない
		if(cnt == 0){
			s = 0x9f;
			lt_sl_straight(0,0x9f);
		}
		else if(cnt == 1){
			s = 0xbf;
			lt_sl_straight(0,0xbf);
		}
		else{
			s = p;
			lt_sl_straight(0,s);
		}
		if(cnt == n - 1){
			s = 0x6f;
			lt_sl_straight(0,0x6f);
		}
		else if(cnt == n - 2){
			s = 0x8f;
			lt_sl_straight(0,0x8f);
		}
		else{
			lt_sl_straight(0,s);
		}
	}
}

/*モータードライバ制御命令(標準動作)*/

//高速ライントレース用
/*通常方式*/
void straight(int s){
	motor_R(s-18,0);
	motor_L(s,0);
}

void sl_straight(int s){
	if(s < 0x7f){
		motor_R(s-6,0);
		motor_L(s,0);
	}
	else if(s < 0x8f){
		motor_R(s-9,0);
		motor_L(s,0);
	}
	else if(s < 0x9f){
		motor_R(s-10,0);
		motor_L(s,0);
	}
	else if(s < 0xaf){
		motor_R(s-12,0);
		motor_L(s,0);
	}
	else if(s < 0xbf){
		motor_R(s-13,0);
		motor_L(s,0);
	}
	else if(s < 0xcf){
		motor_R(s-15,0);
		motor_L(s,0);
	}
	else if(s < 0xdf){
		motor_R(s-15,0);
		motor_L(s,0);
	}
	else if(s < 0xef){
		motor_R(s-16,0);
		motor_L(s,0);
	}
	else if(s < 0xff){
		motor_R(s-17,0);
		motor_L(s,0);
	}
	else{
		straight(s);
	}
}

void back(int s){
	motor_R(0,s);
	motor_L(0,s);
}

void turn_right(int s){
	motor_R(s-50,0);
	motor_L(s,0);
}

void turn_right1(int s){
	motor_R(s-20,0);
	motor_L(s,0);
}
void turn_right2(int s){
	motor_R(s-40,0);
	motor_L(s,0);
}

void turn_left(int s){
	motor_R(s,0);
	motor_L(s-50,0);
}

void turn_left1(int s){
	motor_R(s,0);
	motor_L(s-20,0);
}
void turn_left2(int s){
	motor_R(s,0);
	motor_L(s-40,0);
}

void roll_left(int s){
	motor_R(s,0);
	motor_L(0,s);
}

void roll_right(int s){
	motor_R(0,s);
	motor_L(s,0);
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
	motor_L(0,s-10);
}

void r_turn_right2(int s){
	motor_R(0,s);
	motor_L(0,s-15);
}

void r_turn_right3(int s){
	motor_R(0,s);
	motor_L(0,s-20);
}

void r_turn_right4(int s){
	motor_R(0,s);
	motor_L(0,s-25);
}

void r_turn_right5(int s){
	motor_R(0,s);
	motor_L(0,s-30);
}

void r_turn_right6(int s){
	motor_R(0,s);
	motor_L(0,s-35);
}

void r_turn_right7(int s){
	motor_R(0,s);
	motor_L(0,s-40);
}

void r_turn_right8(int s){
	motor_R(0,s);
	motor_L(0,s-45);
}

void r_turn_right9(int s){
	motor_R(0,s);
	motor_L(0,s-50);
}

void r_turn_left(int s){
	motor_R(0,s-10);
	motor_L(0,s);
}

void r_turn_left2(int s){
	motor_R(0,s-15);
	motor_L(0,s);
}

void r_turn_left3(int s){
	motor_R(0,s-20);
	motor_L(0,s);
}
void r_turn_left4(int s){
	motor_R(0,s-25);
	motor_L(0,s);
}

void r_turn_left5(int s){
	motor_R(0,s-30);
	motor_L(0,s);
}

void r_turn_left6(int s){
	motor_R(0,s-35);
	motor_L(0,s);
}
void r_turn_left7(int s){
	motor_R(0,s-40);
	motor_L(0,s);
}

void r_turn_left8(int s){
	motor_R(0,s-45);
	motor_L(0,s);
}

void r_turn_left9(int s){
	motor_R(0,s-50);
	motor_L(0,s);
}

void motor_R(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTF.OUT |= 0x10;//dis
	}
	else{
		PORTD.OUT = 0x00;
		TCC0.CCD = f;
		TCC1.CCA = b;
	}
}

void motor_L(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTF.OUT |= 0x20;//dis
	}
	else{
		PORTD.OUT = 0x00;
		TCC1.CCB = f;
		TCD0.CCA = b;
	}
}

void fw_straight(unsigned char s){
		int f,b;
		f = img_boad2();
		b = img_boad1();
		lt_back(place(f,b), s);
}

void fw_straight2(unsigned char s){
	int f,b;
	f = -1 * line(
	IIR(r_left3,0),
	IIR(r_left2,1),
	IIR(r_left1,2),
	IIR(r_center,3),
	IIR(r_right1,4),
	IIR(r_right2,5),
	IIR(r_right3,6)
	);

	b = line(
	IIR(f_left3,7),
	IIR(f_left2,8),
	IIR(f_left1,9),
	IIR(f_center,10),
	IIR(f_right1,11),
	IIR(f_right2,12),
	IIR(f_right3,13)
	);
	lt_back(place(f,b), s);
}

void brake(){
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
}

void leg_stop(){
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
}

/*ライン読み取り回転処理*/
void lt_left(int c,char s){
	adc_init(10);
	roll_left(0x2a);
	for(int cnt = 0;cnt <= c;c++){
		/*while(1){
			if(f_right3 > 280){
				break;
			}
		}*/
		while(1){
			if((f_right3 >= 220+s) || (f_left3 >= 200+s) || (f_right2 >= 280+s) || (f_left2 >= 260+s))break;
		}
	}
	brake();
	_delay_ms(1000);
	roll_right(0x2c);
	_delay_ms(150);
	if((f_left3 > 220+s)){}
	while(1){
		adc_init(10);
		if((f_left3 >= 220+s) && (f_left2 >= 275+s))break;
	}
}

void lt_right(int c,char s){
	adc_init(10);
	roll_right(0x2c);
	for(int cnt = 0;cnt <= c;c++){
		/*while(1){
			if(f_right3 > 280){
				break;
			}
		}*/
		while(1){
			if((f_right3 >= 220+s) || (f_left3 >= 200+s) || (f_right2 >= 280+s) || (f_left2 >= 260+s))break;
		}
	}
	brake();
	_delay_ms(1000);
	roll_left(0x2c);
	_delay_ms(150);
	if((f_left3 > 220+s)){}
	while(1){
		adc_init(10);
		if((f_left3 >= 220+s) && (f_left2 >= 275+s))break;
	}
}

void fw_go(int n,int t,unsigned char s){	
	unsigned char p = s;
	int cnt = 0;



	while(cnt < n){
		if(IIR(r_right3,6) >= 3 && IIR(r_right3,6) <= 4){
			if(IIR(r_right2,5) >= 3 && IIR(r_right2,5) <= 4){
				if(IIR(r_left3,0) >= 3 && IIR(r_left3,0) <= 4){
					if(IIR(r_left2,1) >= 3 && IIR(r_left2,1) <= 4){
						
						cnt++;					//フォトトランジスタ5つ反応でcntを+1

						fw_straight2(s);
						while(
						(IIR(r_center,3) >= 3) && 
						(IIR(r_right3,6) >= 3) && 
						(IIR(r_right1,4) >= 3) && 
						(IIR( r_left3,0) >= 3) && 
						(IIR( r_left1,2) >= 3)){}
						if(cnt == 1){
							//t+20?
							_delay_ms(t + 10);
						}
						else{
							_delay_ms(t);
						}
						while(cnt>=n) break;   //cntの数値がn(入力した値)
	        			 //より大きくなったらbreakする
					}
				}
			}
		}
		if(cnt == 0){
			s = 0x5f;
		}
		else if(cnt == 1){
			s = 0x8f;
		}
		else if(cnt == 2){
			s = 0xcf;
		}
		else{
			s=p;
		}

		if(cnt == n - 2){
			s = 0x7f;
		}
		else if(cnt == n - 1){
			s = 0x5f;
		}
		fw_straight2(s);
	}
}

void lift0(int u,int d){//f前 b後ろ
	PORTD.OUT = 0x00;
	TCD0.CCB = u;
	TCD0.CCC = d;
}

void lift1(int f,int b){//f前 b後ろ
	PORTD.OUT = 0x00;
	TCD0.CCD = f;
	TCE0.CCA = b;
}

void valve(char n,char i){//n電磁弁の番号 状態0で縮む1伸びる
	/*if(n == 0){//0
		if(i == 0){
			PORTE.OUT = 0x02;
		}
		else{
			PORTE.OUT = 0x04;
		}
	}
	else if(n == 1){//1
		if(i == 0){
			PORTE.OUT = 0x08;
		}
		else{
			PORTE.OUT = 0x10;
		}
	}
	else if(n == 2){//2
		if(i == 0){
			PORTE.OUT = 0x20;
		}
		else{
			PORTE.OUT = 0x40;
		}
	}*/
}
void pwm_reset(){
	// TCC0 (ポートC; OC0A, OC0B, OC0C, OC0D) の設定
	TCC0.PER = 0x00ff;
	TCC0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCC0.CTRLB = TC_WGMODE_SS_gc | (0b0000 << 4);//OC0D
	// TCC1 (ポートC; OC1A, OC1B) の設定
	TCC1.PER   = 0x00ff; // おまじない
	TCC1.CTRLA = TC_CLKSEL_DIV64_gc; // 64 分周
	TCC1.CTRLB = TC_WGMODE_SS_gc | (0b0000 << 4); // 波形 & 有効ポートの設定OC1B
	// TCD0 (ポートD; OC0A, OC0B, OC0C, OC0D) の設定
	TCD0.PER = 0x00ff;
	TCD0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCD0.CTRLB = TC_WGMODE_SS_gc | (0b0000 << 4);
	
	// TCE0 (ポートE; OC0A, OC0B, OC0C, OC0D) の設定
	TCE0.PER = 0x00ff;
	TCE0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCE0.CTRLB = TC_WGMODE_SS_gc | (0b0000 << 4);
}

void pwm_set(){
	// TCC0 (ポートC; OC0A, OC0B, OC0C, OC0D) の設定
	TCC0.PER = 0x00ff;
	TCC0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCC0.CTRLB = TC_WGMODE_SS_gc | (0b1000 << 4);//OC0D
	// TCC1 (ポートC; OC1A, OC1B) の設定
	TCC1.PER   = 0x00ff; // おまじない
	TCC1.CTRLA = TC_CLKSEL_DIV64_gc; // 64 分周
	TCC1.CTRLB = TC_WGMODE_SS_gc | (0b0011 << 4); // 波形 & 有効ポートの設定OC1B
	// TCD0 (ポートD; OC0A, OC0B, OC0C, OC0D) の設定
	TCD0.PER = 0x00ff;
	TCD0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCD0.CTRLB = TC_WGMODE_SS_gc | (0b1111 << 4);
	
	// TCE0 (ポートE; OC0A, OC0B, OC0C, OC0D) の設定
	TCE0.PER = 0x00ff;
	TCE0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCE0.CTRLB = TC_WGMODE_SS_gc | (0b0001 << 4);
}

char f_tsen(){
	PORTF.DIR = 0b00000000;

	if(PORTF.IN == 0){//反応なし
		return 0;
	}
	else if(PORTF.IN & _BV(0)){//右タッチセンサー
		return 1;
	}
	else if(PORTF.IN & _BV(1)){//左タッチセンサー
		return 2;
	}
	else if((PORTF.IN & _BV(0)) && (PORTF.IN & _BV(1))){//左右タッチセンサー
		return 3;
	}
	else if(PORTF.IN & _BV(2)){//真ん中
		return 4;
	}
	else if((PORTF.IN & _BV(0)) && (PORTF.IN & _BV(2))){//真ん中＋右
		return 5;
	}
	else if((PORTF.IN & _BV(1)) && (PORTF.IN & _BV(2))){//真ん中＋左
		return 6;
	}
	else if((PORTF.IN & _BV(0)) && (PORTF.IN & _BV(1)) && (PORTF.IN & _BV(2))){//前部
		return 7;
	}
}

void ex_stop(){
	for(int n = 0;n < 5;n++){
		for(int i = 0;i <= 3;i++){
			brake();
			lift0(0xff,0xff);
			lift1(0xff,0xff);
			test_port('F',6,30);
			_delay_ms(10);
			test_port('F',6,10);
			_delay_ms(10);
			test_port('F',6,40);
			_delay_ms(10);
			test_port('F',6,20);
			_delay_ms(10);
		}
		_delay_ms(500);
	}
	_delay_ms(200);
	while(1);
}

void AD_sw(char n){
	PORTF.DIR |= 0x03;
	if(n == 1){
		PORTF.OUT|=0x03;
	}
	else {
		PORTF.OUT &= 0xfc;
	}
	_delay_ms(10);/*ADコンバータ切り替え時間*/
}

void AD_see(char c){
	if(c == 'f'){
		usart_printf(&USARTE0,"f_left3=%d\n",f_left3);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_left2=%d\n",f_left2);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_left1=%d\n",f_left1);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_center=%d\n",f_center);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right1=%d\n",f_right1);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right2=%d\n",f_right2);
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right3=%d\n\n",f_right3);
		_delay_ms(1000);
	}
	else if(c == 'r'){
		usart_printf(&USARTE0,"r_left3=%d\n",r_left3);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_left2=%d\n",r_left2);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_left1=%d\n",r_left1);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_center=%d\n",r_center);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right1=%d\n",r_right1);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right2=%d\n",r_right2);
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right3=%d\n\n",r_right3);
		_delay_ms(1000);
	}
}

void lift(int x,int y){
	PORTE.DIR &= 0x00111111;
	if(x == 0){
		lift1(0xff,0xff);
	}
	else if(x < 0){//後ろ
		if(s_lift1 > 500){
			lift1(0xff,0xff);
		}
		else{
			lift1(0x00,-1 * x);
		}
	}
	else if(x > 0){//前
		if(s_lift2 < 500){
			lift1(0xff,0xff);
		}
		else{
			lift1(x,0x00);
		}
	}
	if(y == 0){
		lift0(0xff,0xff);
	}
	else if(y < 0){//下
		//制御命令
		/*タッチセンサー*/
		if(PORTE.IN & _BV(6)){
			lift0(0xff,0xff);
		}
		else{
			lift0(0,-1*y);
		}
	}
	else if(y > 0){//上
		if(PORTE.IN & _BV(8)){
			lift0(0xff,0xff);
		}
		else{
			lift0(y,0);
		}
	}
}

void obl_run(){
	go(2,50,0xff);
	brake();
	_delay_ms(300);
	for(int t= 0;t < 300;t++){
	lt_sl_straight(0,0x6f);
		_delay_ms(1);
	}
	brake();
	_delay_ms(300);
	for(int i = 0;i <= 1000;i++){
		motor_R(0xa0,0x00);
		motor_L(0x40,0x00);
		_delay_ms(1);
	}
	brake();
	_delay_ms(300);
	
	for(int i = 0;i <= 500;i++){
		motor_R(0xff,0xff);
		motor_L(0xa0,0x00);
		_delay_ms(1);
	}
	brake();
	_delay_ms(100);
	for(int i = 0;i <= 150;i++){
		lt_sl_straight(0,0x7f);
		_delay_ms(1);
	}
	go(2,50,0xff);
	brake();
}

void sloap(){
	obl_run();
	brake();
	_delay_ms(250);
	for(int i = 0;i <= 500;i++){
		fw_straight2(0x3f);
		_delay_ms(1);
	}
	brake();
	_delay_ms(400);
	/*for(int i = 0;i < 1400;i++){
		roll_right(60);
		_delay_ms(1);
	}*/
	lt_right(1,0);
	brake();
	_delay_ms(450);
	fw_go(16,50,0xaf);
	brake();
}

void basket(){
	obl_run();
	brake();
	_delay_ms(1000);
	fw_go(5,50,0xaf);
	brake();
	_delay_ms(1000);
	lt_left(1,0);
	brake();
	_delay_ms(800);
	for(int i=0;i < 250;i++){
		fw_straight2(0x7f);
		_delay_ms(1);
	}
	fw_go(1,50,0xcf);
	brake();
	_delay_ms(500);
	lt_right(1,0);
	brake();
	_delay_ms(500);
	for(int i=0;i < 200;i++){
		fw_straight2(0x4f);
		_delay_ms(1);
	}
	fw_go(2,50,0x6f);
	brake();
	_delay_ms(100);
	for(int i=0;i < 100;i++){
		roll_left(0x4f);
		_delay_ms(1);
	}
	brake();
}

int main(){
	interrupt_init();
	clock_internal_init(); // 内部 32 MHz で動作
	PORTA.DIR = 0x00;
	PORTB.DIR = 0x00;
	PORTC.DIR |= 0x38;
	PORTD.DIR |= 0x0f;
	PORTE.DIR |= 0xff;	

	interrupt_start(&PORTF, 7, ex_stop);

	pwm_set();
	//pwm_reset();

    usart_init(&USARTE0, 9600); // USART の初期設定 (ポートE; ボーレート 9600)
	adc_init(10);

	/*
	#define r_left3  PORTB.IN&_BV(1)
	#define r_left2  PORTB.IN&_BV(2)
	#define r_left1  PORTB.IN&_BV(3)
	#define r_center PORTB.IN&_BV(4)
	#define r_right1 PORTB.IN&_BV(5)
	#define r_right2 PORTB.IN&_BV(6)
	#define r_right3 PORTB.IN&_BV(7)*/
	//int t = 0;
	int n = 0;
	
	test_port('F',6,100);
	_delay_ms(50);
	test_port('F',6,100);
	_delay_ms(50);
	//test_port('F',4,1000);
	//test_port('F',5,1000);
	//lt_right(1,0);
	
	//while(1){
		/*usart_printf(&USARTE0,"f_left3=%d\n",IIR(f_left3,0));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_left2=%d\n",IIR(f_left2,1));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_left1=%d\n",IIR(f_left1,2));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_center=%d\n",IIR(f_center,3));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right1=%d\n",IIR(f_right1,4));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right2=%d\n",IIR(f_right2,5));
		_delay_us(1000);
		usart_printf(&USARTE0,"f_right3=%d\n\n",IIR(f_right3,6));
		_delay_ms(1000);*/
		
		/*usart_printf(&USARTE0,"r_left3=%d\n",IIR(r_left3,7));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_left2=%d\n",IIR(r_left2,8));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_left1=%d\n",IIR(r_left1,9));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_center=%d\n",IIR(r_center,10));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right1=%d\n",IIR(r_right1,11));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right2=%d\n",IIR(r_right2,12));
		_delay_us(1000);
		usart_printf(&USARTE0,"r_right3=%d\n\n",IIR(r_right3,13));
		_delay_ms(1000);*/
	//}
	


	while(1){
		
		sloap();
		brake();
		break;
	}
}
