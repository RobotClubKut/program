//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

void x_motor_control(void);
void y_motor_control(void);
void z_motor_control(void);

unsigned char port1data = 0,port2data = 0;

struct I2C_Motor
{
	BYTE x_1;
	BYTE x_2;
	BYTE y_1;
	BYTE y_2;
	BYTE z_1;
	BYTE z_2;
	
} MyI2C_Motor;

void main(void)
{

	
	/*ピンデータの保存変数*/
	unsigned char port1data = 0,port2data = 0;
	 M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	/*PWM8の1~6をスタート*/
	PWM8_1_Start();
	PWM8_2_Start();
	PWM8_3_Start();
	PWM8_4_Start();
	PWM8_5_Start();
	PWM8_6_Start();
	
	/*EzI2Cs_1の設定*/
	EzI2Cs_1_SetRamBuffer(sizeof(MyI2C_Motor),6, (BYTE *)&MyI2C_Motor);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();

	/*メイン処理(没)*/
	while (1)
	{
		x_motor_control();
		y_motor_control();
		z_motor_control();

	}
}


void x_motor_control(void)
{
//		xが入力されてなかったらブレーキ
	if ( (MyI2C_Motor.x_1 == 0) && (MyI2C_Motor.x_2 == 0) )
	{
	
		PRT2DR = port2data & ~(1 << 1);
		PRT1DR = port1data & ~(1 << 3);
		
		PWM8_1_WritePulseWidth(255);
		PWM8_2_WritePulseWidth(255);

	}
	
//		x軸モータ駆動
	else if(MyI2C_Motor.x_2 == 0)
	{
		
		PRT2DR = port2data | (1 << 1);
//		PRT1DR = port1data | (1 << 3);
		
		PWM8_1_WritePulseWidth(MyI2C_Motor.x_1);
		PWM8_2_WritePulseWidth(MyI2C_Motor.x_2);
	}
	else if(MyI2C_Motor.x_1 == 0)
	{
		
//		PRT2DR = port2data | (1 << 1);
		PRT1DR = port1data | (1 << 3);
		
		PWM8_1_WritePulseWidth(MyI2C_Motor.x_1);
		PWM8_2_WritePulseWidth(MyI2C_Motor.x_2);
	}
}


void y_motor_control(void)
{
//		yが入力されてなかったらブレーキ	
	if ((MyI2C_Motor.y_1 == 0)&&(MyI2C_Motor.y_2 == 0)){
	
		PRT2DR = port2data & ~(1 << 5);
		PRT2DR = port2data & ~(1 << 7);
		
		PWM8_3_WritePulseWidth(255);
		PWM8_4_WritePulseWidth(255);
	}
		
//		y軸モータ駆動
	else if (MyI2C_Motor.y_2 == 0){
		
		PRT2DR = port2data | (1 << 5);
//		PRT2DR = port2data | (1 << 7);
		
		PWM8_3_WritePulseWidth(MyI2C_Motor.y_1);
		PWM8_4_WritePulseWidth(MyI2C_Motor.y_2);

	}
	else if (MyI2C_Motor.y_1 == 0){
		
//		PRT2DR = port2data | (1 << 5);
		PRT2DR = port2data | (1 << 7);
		
		PWM8_3_WritePulseWidth(MyI2C_Motor.y_1);
		PWM8_4_WritePulseWidth(MyI2C_Motor.y_2);

	}
}

void z_motor_control(void)
{
//				zが入力されてなかったらブレーキ
	if ((MyI2C_Motor.z_1 == 0)&&(MyI2C_Motor.z_2 == 0)){
		
		PRT2DR = port2data & ~(1 << 0);
		PRT1DR = port1data & ~(1 << 6);
		
		PWM8_5_WritePulseWidth(255);
		PWM8_6_WritePulseWidth(255);

	}
		
//		z軸モータ駆動
	else if((MyI2C_Motor.z_1 == 0)||(MyI2C_Motor.z_2 == 0)){
		
		PRT2DR = port2data | (1 << 0);
		PRT1DR = port1data | (1 << 6);
			
		PWM8_5_WritePulseWidth(MyI2C_Motor.z_1);
		PWM8_6_WritePulseWidth(MyI2C_Motor.z_2);

	}

}