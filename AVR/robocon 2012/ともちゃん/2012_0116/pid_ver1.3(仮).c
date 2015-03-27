/*
* ライン読み飛ばし処理追加*/

/*ライントレースマシン制御プログラム*/
//8MHz

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#ifndef PID_H_
#define PID_H_

/* ライントレース初期宣言 */
/*センサーの定義*/
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

#define SW1 PINB&_BV(5)
#define TS1 PINA&_BV(7)

/*後輪駆動系*/

//Define parameter
#define epsilon 0.01
#define dt 0.01             //10ms loop time
#define MAX 0xff                   //For Current Saturation
#define MIN -1*0xff 
#define Kp  0.1
#define Kd  0.01
#define Ki  0.005

float PIDcal(float setpoint,float actual_position){
	static float pre_error = 0;
	static float integral = 0;
	float error;
	float derivative;
	float output;

	//Caculate P,I,D
	error = setpoint - actual_position;

	//In case of error too small then stop intergration
	if(abs(error) > epsilon)
	{
		integral = integral + error*dt;
	}
	derivative = (error - pre_error)/dt;
	output = Kp*error + Ki*integral + Kd*derivative;

	//Saturation Filter
	if(output > MAX)
	{
		output = MAX;
	}
	else if(output < MIN)
	{
		output = MIN;
	}
        //Update error
        pre_error = error;

 return output;
}
#endif /*PID_H_*/

int point(){
	if(f_center){
		_delay_ms(10);
		if(f_center){
			return 3;
		}
	}

	if(f_right2){
		_delay_ms(10);
		if(f_right2){
			return 1;
		}
	}
	else if(f_left2){
		_delay_ms(10);
		if(f_left2){
			return 5;
		}
	}
	else if(f_right1){
		_delay_ms(10);
		if(f_right1){
			return 2;
		}
	}
	else if(f_left1){
		_delay_ms(10);
		if(f_left1){
			return 4;
		}
	}
	else if(f_center){
		_delay_ms(10);
		if(f_center){
			return 3;
		}
	}
	//else return 3;
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

void pid_straight(){
	double p=0;
	p = PIDcal(point()*100,300);
	if(p > 0){
		motor_L(0xff-p,0);
		motor_R(0xff,0);
	}
	else if(p == 0){
		motor_R(0xff,0);
		motor_L(0xff,0);
	}
	else{
		motor_L(0xff,0);
		motor_R(0xff+p,0);
	}
}

void pid_go(int n){
	int cnt = 0;
	while(1){
		if(cnt == n)break;
		pid_straight();
		if(f_left3 && f_right3){
			if(f_center){
				cnt++;
				while(f_left3 && f_right3){
					pid_straight();
				}
			}
		}
	}
}


/*ここより上後輪駆動*/

/*前輪駆動系*/
int img_boad1(){//仮想ライントレース基板制御関連
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
int img_boad2(){//仮想ライントレース基板制御関連
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

void fw_straight(){
	int f,b;
	double p=0;
	f = img_boad2();
	b = img_boad1();
	p=PIDcal(place(f,b)*100,300);
	
	if(p > 0){
		motor_L(0,0xff-p);
		motor_R(0,0xff);
	}
	else if(p == 0){
		motor_R(0,0xff);
		motor_L(0,0xff);
	}
	else{
		motor_L(0,0xff);
		motor_R(0,0xff+p);
	}
}

void fw_go(int n){
	int cnt = 0;
	while(1){
		if(cnt == n)break;
		fw_straight();
		if(f_left3 && f_right3){
			if(f_center){
				cnt++;
				while(f_left3 && f_right3){
					fw_straight();
				}
			}
		}
	}
}
/*これより上前輪駆動系*/


int main(){
	DDRA = 0x00;
	DDRC = 0x00;
	DDRB = 0b11011111;
	DDRD = 0xff;
	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
	TCCR1A = 0;  	  // OCR1A OCR1B の設定
	TCCR1B = 3;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;


	while(1){
		if(SW1){
			_delay_ms(20);
			if(SW1){
				while(SW1);
				break;
			}
		}
	}

	while(1){
		fw_straight();
		fw_go(6);
		break;
	}
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
	return 0;
}
