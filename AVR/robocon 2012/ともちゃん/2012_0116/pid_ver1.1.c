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
/* ライントレースセンター1枚目 */
#define f_left3  PINA&_BV(6)
#define f_left2  PINA&_BV(5)
#define f_left1  PINA&_BV(4)
#define f_center PINA&_BV(3)
#define f_right1 PINA&_BV(2)
#define f_right2 PINA&_BV(1)
#define f_right3 PINA&_BV(0)

//Define parameter
#define epsilon 0.01
#define dt 0.005             //5000ms loop time
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
		_delay_ms(5);
		if(f_center){
			return 3;
		}
	}

	if(f_right2){
		_delay_ms(5);
		if(f_right2){
			return 1;
		}
	}
	else if(f_left2){
		_delay_ms(5);
		if(f_left2){
			return 5;
		}
	}
	else if(f_right1){
		_delay_ms(5);
		if(f_right1){
			return 2;
		}
	}
	else if(f_left1){
		_delay_ms(5);
		if(f_left1){
			return 4;
		}
	}
	else if(f_center){
		_delay_ms(5);
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

void go(int n,int t){	
	int cnt = 0;
	while(cnt < n){
		if(f_right2){
			if(f_left2){
				if(f_right1){
					if(f_left1){
						if(f_center){
							cnt++;					//フォトトランジスタ5つ反応でcntを+1
							pid_straight();
							while((f_center) && (f_right2) && (f_right1) && (f_left2) && (f_left1)){}
							_delay_ms(t);
							while(cnt>=n) break;   //cntの数値がn(入力した値)
						}           //より大きくなったらbreakする
					}
				}
			}	
		}
		pid_straight();
	}
}

void straight(int s){
	motor_R(s,0);
	motor_L(s,0);
}

int main(){
	DDRA = 0x00;
	DDRC = 0x00;
	DDRB = 0xff;
	DDRD = 0xff;
	TCCR0A = 0b10100011;  // OCR0A OCR0B の設定
	TCCR0B = 0b00000001;
	TCCR1A = 0;  	  // OCR1A OCR1B の設定
	TCCR1B = 3;
	TCCR2A = 0b10100011;  // OCR2A OCR2B の設定
	TCCR2B = 0b00000001;

	while(1){	
		go(6,5);
		break;
	}
	motor_R(0xff,0xff);
	motor_L(0xff,0xff);
	return 0;
}
