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
#define MIN -0xff
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
	if(abs(error) > epsilon){
		integral = integral + error*dt;
	}
	derivative = (error - pre_error)/dt;
	output = Kp*error + Ki*integral + Kd*derivative;

	//Saturation Filter
	if(output > MAX){
		output = MAX;
	}
	else if(output < MIN){
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

	double p=0;

	while(1){	


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
	return 0;
}
