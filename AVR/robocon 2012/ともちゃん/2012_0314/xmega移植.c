#define F_CPU 3200000
#include <avr/io.h>
#include <util/delay.h>
#include "xkvr/clock.h"

#define f_left3  PORTA.IN&_BV(7)
#define f_left2  PORTA.IN&_BV(6)
#define f_left1  PORTA.IN&_BV(5)
#define f_center PORTA.IN&_BV(4)
#define f_right1 PORTA.IN&_BV(3)
#define f_right2 PORTA.IN&_BV(2)
#define f_right3 PORTA.IN&_BV(1)

#define r_left3  PORTB.IN&_BV(1)
#define r_left2  PORTB.IN&_BV(2)
#define r_left1  PORTB.IN&_BV(3)
#define r_center PORTB.IN&_BV(4)
#define r_right1 PORTB.IN&_BV(5)
#define r_right2 PORTB.IN&_BV(6)
#define r_right3 PORTB.IN&_BV(7)

#define SW1 PORTC.IN&_BV(0)
#define TS1 PORTC.IN&_BV(1)
#define LS0 PORTC.IN&_BV(2)

int img_boad1(){//仮想ライントレース基板
	if(f_center){
		if(f_center) return 0;
	}
	if(f_right3){
		if(f_right3) return 3;
	}
	else if(f_left3){
		if(f_left3) return -3;
	}
	else if(f_right2){
		if(f_right2) return 2;
	}
	else if(f_left2){
		if(f_left2) return -2;
	}
	else if(f_right1){
		if(f_right1) return 1;
	}
	else if(f_left1){
		if(f_left1) return -1;
	}
	else if(f_center){
		if(f_center) return 0;
	}
	else return 0;
}
int img_boad2(){//仮想ライントレース基板
	if(r_center){
		if(r_center) return 0;
	}
	if(r_left3){
		if(r_left3) return 3;
	}
	else if(r_right3){
		if(r_right3) return -3;
	}
	else if(r_left2){
		if(r_left2) return 2;
	}
	else if(r_right2){
		if(r_right2) return -2;
	}
	else if(r_left1){
		if(r_left1) return 1;
	}
	else if(r_right1){
		if(r_right1) return -1;
	}
	else if(r_center){
		if(r_center) return 0;
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

void lt_straight(){
		if(f_center){
			_delay_ms(5);
			if(f_center) straight(0xff);
		}

		if(f_right2){
			_delay_ms(5);
			if(f_right2) turn_right2(0xff);
		}
		else if(f_left2){
			_delay_ms(3);
			if(f_left2) turn_left2(0xff);
		}
		else if(f_right1){
			_delay_ms(3);
			if(f_right1) turn_right1(0xff);
		}
		else if(f_left1){
			_delay_ms(1);
			if(f_left1) turn_left1(0xff);
		}
		else if(f_center){
			_delay_ms(3);
			if(f_center) straight(0xff);
		}
		else straight(0xff);
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
		lt_straight();
	}
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

void stop(){
	motor_R(0,0);
	motor_L(0,0);
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
	// TCC0 (ポートC; OC0A, OC0B, OC0C, OC0D) の設定
	TCC0.PER = 0x00ff;
	TCC0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCC0.CTRLB = TC_WGMODE_SS_gc | (0b1000 << 4);
	// TCC1 (ポートC; OC1A, OC1B) の設定
	TCC1.PER   = 0x00ff; // おまじない
	TCC1.CTRLA = TC_CLKSEL_DIV64_gc; // 64 分周
	TCC1.CTRLB = TC_WGMODE_SS_gc | (0b0001 << 4); // 波形 & 有効ポートの設定
	
	
	if(f == 0 && b == 0){
		PORTD.OUT |= 0x02;//dis
	}
	else{
		PORTD.OUT = 0x00;
		TCC0.CCD = f;
		TCC1.CCA = b;
	}
}

void motor_L(int f,int b){//f前 b後ろ
	// TCC1 (ポートC; OC1A, OC1B) の設定
	TCC1.PER   = 0x00ff; // おまじない
	TCC1.CTRLA = TC_CLKSEL_DIV64_gc; // 64 分周
	TCC1.CTRLB = TC_WGMODE_SS_gc | (0b0010 << 4); // 波形 & 有効ポートの設定
	// TCC0 (ポートC; OC0A, OC0B, OC0C, OC0D) の設定
	TCD0.PER = 0x00ff;
	TCD0.CTRLA = TC_CLKSEL_DIV64_gc;
	TCD0.CTRLB = TC_WGMODE_SS_gc | (0b0001 << 4);
	if(f == 0 && b == 0){
		PORTD.OUT |= 0x04;//dis
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


int main(){
	clock_internal_init(); // 内部 32 MHz で動作

	while(1){
	}
}
