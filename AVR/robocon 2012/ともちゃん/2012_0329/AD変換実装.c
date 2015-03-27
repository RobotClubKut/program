//#define F_CPU 32000000
#define F_CPU 32000000
#include <avr/io.h>
#include <util/delay.h>
#include "xkvr/clock.h"
#include "xkvr/usart.h"
#include "xkvr/adc.h"

/*
#define f_left3  PORTA.IN&_BV(7)
#define f_left2  PORTA.IN&_BV(6)
#define f_left1  PORTA.IN&_BV(5)
#define f_center PORTA.IN&_BV(4)
#define f_right1 PORTA.IN&_BV(3)
#define f_right2 PORTA.IN&_BV(2)
#define f_right3 PORTA.IN&_BV(1)
*/

#define f_left3  adc_convert(6)
#define f_left2  adc_convert(5)
#define f_left1  adc_convert(4)
#define f_center adc_convert(3)
#define f_right1 adc_convert(2)
#define f_right2 adc_convert(1)
#define f_right3 adc_convert(7)

/*
#define r_left3  PORTB.IN&_BV(1)
#define r_left2  PORTB.IN&_BV(2)
#define r_left1  PORTB.IN&_BV(3)
#define r_center PORTB.IN&_BV(4)
#define r_right1 PORTB.IN&_BV(5)
#define r_right2 PORTB.IN&_BV(6)
#define r_right3 PORTB.IN&_BV(7)
*/

#define r_right3  adc_convert(15)
#define r_left3  adc_convert(14)
#define r_left2  adc_convert(13)
#define r_left1 adc_convert(12)
#define r_center adc_convert(11)
#define r_right1 adc_convert(10)
#define r_right2 adc_convert(9)

#define SW1 PORTC.IN&_BV(0)
#define TS1 PORTC.IN&_BV(1)
#define LS0 PORTC.IN&_BV(2)

int f_IIR1(int n){
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

int f_IIR2(int n){
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

int f_IIR3(int n){
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

int f_IIR4(int n){
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

int f_IIR5(int n){
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

int f_IIR6(int n){
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

int f_IIR7(int n){
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

void port_in(char n,char x){
	int i,cnt = 0;

	for(i = 1;cnt <= x;cnt ++){
		i *= 2;
	}

	i != i;
	
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
					  PORTF.DIR
	};

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
	if(f_center > 250){
		return 0;
	}
	if(f_right3 > 250){
		return 3;
	}
	else if(f_left3 > 250){
		return -3;
	}
	else if(f_right2 > 250){
		return 2;
	}
	else if(f_left2 > 250){
		return -2;
	}
	else if(f_right1 > 250){
		return 1;
	}
	else if(f_left1 > 250){
		return -1;
	}
	else if(f_center > 250){
		return 0;
	}
	else return 0;
}
int img_boad2(){//仮想ライントレース基板
	if(r_center > 250){
		return 0;
	}
	if(r_left3 > 250){
		return 3;
	}
	else if(r_right3 > 250){
		return -3;
	}
	else if(r_left2 > 250){
		return 2;
	}
	else if(r_right2 > 250){
		return -2;
	}
	else if(r_left1 > 250){
		return 1;
	}
	else if(r_right1 > 250){
		return -1;
	}
	else if(r_center > 250){
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

		if(f_right2 > 250){
			if(n == 1)usart_printf(&USARTE0,"turn_right2\n");
			_delay_ms(5);
			turn_right2(0xff);
		}
		else if(f_left2 > 250){
			if(n == 1)usart_printf(&USARTE0,"turn_left2\n");
			_delay_ms(3);
			turn_left2(0xff);
		}
		else if(f_right1 > 250){
			if(n == 1)usart_printf(&USARTE0,"turn_right1\n");
			_delay_ms(3);
			turn_right1(0xff);
		}
		else if(f_left1 > 250){
			if(n == 1)usart_printf(&USARTE0,"turn_left1\n");
			_delay_ms(1);
			turn_left1(0xff);
		}
		else if(f_center > 250){
			if(n == 1)usart_printf(&USARTE0,"f_center\n");
			_delay_ms(3);
			straight(0xff);
		}
		else{
			if(n == 1)usart_printf(&USARTE0,"other\n");
			straight(0xff);
		}
}

void lt_back(int p){
	switch(p){
	case -9:
		r_turn_left9(0xff);
		_delay_ms(8);
		break;
	case -8:
		r_turn_left8(0xff);
		_delay_ms(6);
		break;
	case -7:
		r_turn_left7(0xff);
		_delay_ms(6);
		break;
	case -6:
		r_turn_left6(0xff);
		_delay_ms(6);
		break;
	case -5:
		r_turn_left5(0xff);
		_delay_ms(6);
		break;
	case -4:
		r_turn_left4(0xff);
		_delay_ms(6);
		break;
	case -3:
		r_turn_left3(0xff);
		_delay_ms(5);
		break;
	case -2:
		r_turn_left2(0xff);
		_delay_ms(4);
		break;
	case -1:
		r_turn_left(0xff);
		_delay_ms(2);
		break;
	case 0:
		r_straight(0xff);
		break;
	case 1:
		r_turn_right(0xff);
		break;
	case 2:
		r_turn_right2(0xff);
		break;
	case 3:
		r_turn_right3(0xff);
		break;
	case 4:
		r_turn_right4(0xff);
		break;
	case 5:
		r_turn_right5(0xff);
		break;
	case 6:
		r_turn_right6(0xff);
		break;
	case 7:
		r_turn_right7(0xff);
		break;
	case 8:
		r_turn_right8(0xff);
		break;
	case 9:
		r_turn_right9(0xff);
		break;
	}
}

void go(int n,int t){	

	int cnt = 0;
	while(cnt < n){
		if(f_right2){
			if(f_left2){
				if(f_right1){
					if(f_left1){
						if(f_center){
							cnt++;					//フォトトランジスタ5つ反応でcntを+1
							straight();
							while((f_center) && (f_right2) && (f_right1) && (f_left2) && (f_left1)){}
							_delay_ms(t);
							while(cnt>=n) break;   //cntの数値がn(入力した値)
						}           //より大きくなったらbreakする
					}
				}
			}	
		}
		lt_straight(0);
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
	motor_R(0,s-30);
	motor_L(0,s);
}

void r_back(int s){
	motor_R(s,0);
	motor_L(s,0);
}

void r_turn_right(int s){
	motor_R(0,s);
	motor_L(0,s-30);
}

void r_turn_right2(int s){
	motor_R(0,s);
	motor_L(0,s-50);
}

void r_turn_right3(int s){
	motor_R(0,s);
	motor_L(0,s-70);
}

void r_turn_right4(int s){
	motor_R(0,s);
	motor_L(0,s-90);
}

void r_turn_right5(int s){
	motor_R(0,s);
	motor_L(0,s-110);
}

void r_turn_right6(int s){
	motor_R(0,s);
	motor_L(0,s-130);
}

void r_turn_right7(int s){
	motor_R(0,s);
	motor_L(0,s-150);
}

void r_turn_right8(int s){
	motor_R(0,s);
	motor_L(0,s-170);
}

void r_turn_right9(int s){
	motor_R(0,s);
	motor_L(0,s-190);
}

void r_turn_left(int s){
	motor_R(0,s-30);
	motor_L(0,s);
}

void r_turn_left2(int s){
	motor_R(0,s-50);
	motor_L(0,s);
}

void r_turn_left3(int s){
	motor_R(0,s-60);
	motor_L(0,s);
}
void r_turn_left4(int s){
	motor_R(0,s-62);
	motor_L(0,s);
}

void r_turn_left5(int s){
	motor_R(0,s-65);
	motor_L(0,s);
}

void r_turn_left6(int s){
	motor_R(0,s-73);
	motor_L(0,s);
}
void r_turn_left7(int s){
	motor_R(0,s-75);
	motor_L(0,s);
}

void r_turn_left8(int s){
	motor_R(0,s-78);
	motor_L(0,s);
}

void r_turn_left9(int s){
	motor_R(0,s-76);
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

void fw_straight(){
		int f,b;
		f = img_boad2();
		b = img_boad1();
		lt_back(place(f,b));
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
void lt_left(int c,int t){
	int cnt = 0;

	roll_left(0x90);
	while(1){
		if(c == cnt)break;
		while(1){
			if(f_right3){
				if(f_right3){
					break;
				}
			}
		}
		while(1){
			if(r_right3 || r_left3 || r_right2 || r_left2 || f_left3)break;
		}
		c++;
	}
	leg_stop();
	_delay_ms(200);
	roll_right(0x90);
	_delay_ms(t);
	leg_stop();
	_delay_ms(100);
}

void lt_right(int c){
	int cnt=1;

	int s = 0xa0;

	while(cnt <= c){
		roll_right(s);
		_delay_ms(600);
		while((r_right2)==0) roll_right(s);
		leg_stop();
		_delay_ms(70);
		if(cnt == c){
			while((r_right1) || (r_right2)) roll_right(0xa0);
			while((r_left1) || (r_left2)) roll_left(0xa0);
		}
		cnt++;
	}
	leg_stop();
	_delay_ms(100);
}

void fw_go(int n,int t){	

	int cnt = 0;
	while(cnt < n){
		if(r_right2){
			if(r_left2){
				if(r_right1){
					if(r_left1){
						if(r_center){
							cnt++;					//フォトトランジスタ5つ反応でcntを+1
							fw_straight();
							while((r_center) && (r_right3) && (r_right1) && (r_left3) && (r_left1)){}
							for(int i = 0;i < t;i++){
								_delay_ms(1);
							}
							while(cnt>=n) break;   //cntの数値がn(入力した値)
						}           //より大きくなったらbreakする
					}
				}
			}	
		}
		fw_straight();
	}
}

void lift0(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTF.OUT |= 0x40;//dis
	}
	else{
		PORTD.OUT = 0x00;
		TCD0.CCB = f;
		TCD0.CCC = b;
	}
}

void lift1(int f,int b){//f前 b後ろ
	if(f == 0 && b == 0){
		PORTF.OUT |= 0x80;//dis
	}
	else{
		PORTD.OUT = 0x00;
		TCD0.CCD = f;
		TCE0.CCA = b;
	}
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

void dis(){
	PORTF.DIR |= 0b11111111;
	PORTF.OUT = 0b11111111;
}

int main(){;
	clock_internal_init(); // 内部 32 MHz で動作
	PORTA.DIR = 0x00;
	PORTB.DIR = 0x00;
	PORTC.DIR |= 0x38;
	PORTD.DIR |= 0x0f;
	PORTE.DIR |= 0xff;	

	pwm_set();
	//pwm_reset();

    usart_init(&USARTE0, 38400); // USART の初期設定 (ポートE; ボーレート 9600)
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
	while(1){
		lt_straight(0);
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
		_delay_ms(100);

	}
	/*while(1){
		sl_straight(0xcf);
	}*/
}
