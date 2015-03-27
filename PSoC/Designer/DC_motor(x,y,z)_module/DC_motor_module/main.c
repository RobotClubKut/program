//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------
//PSoC1の29446用です。
//配線はxのhighがP1[2],P1[3]
//        lowが　P0[0],P1[1]
//     yのhighがP2[5],P2[7]
//		  lowが　P0[2],P0[3] 
//     zのhighがP1[6],P2[0]
//		  lowが P0[4],P0[5]
//EZI2Cs_1  slave　address 11
//          I2C clock 400k First



#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules


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
	
	// M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	/*ポートの初期化いらない*/
//	PRT2DR = 0x00;
//	PRT1DR = 0x00;
//	PRT0DR = 0x00;
	
	/*PWM8の1~6をスタート*/
	PWM8_1_Start();
	PWM8_2_Start();
	PWM8_3_Start();
	PWM8_4_Start();
	PWM8_5_Start();
	PWM8_6_Start();
	/*EzI2Cs_1の設定*/
	EzI2Cs_1_SetRamBuffer(sizeof(MyI2C_Motor), 6, (BYTE *)&MyI2C_Motor);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();
	/*メイン処理*/
	while (1){
		/*xが入力されてなかったらブレーキ*/
		if ((MyI2C_Motor.x_1 == 0)&&(MyI2C_Motor.x_2 == 0)){
			
			PRT1DR = PRT1DR & ~(1 << 2);
			PRT1DR = PRT1DR & ~(1 << 3);
			
			PWM8_1_WritePulseWidth(255);
			PWM8_2_WritePulseWidth(255);
		}
		
		/*x軸モータ駆動*/
		else{
			
			PRT1DR = PRT1DR | (1 << 2);
			PRT1DR = PRT1DR | (1 << 3);
			
			PWM8_1_WritePulseWidth(MyI2C_Motor.x_1);
			PWM8_2_WritePulseWidth(MyI2C_Motor.x_2);
		}
		/*yが入力されてなかったらブレーキ*/	
		if ((MyI2C_Motor.y_1 == 0)&&(MyI2C_Motor.y_2 == 0)){
			
			PRT2DR = PRT2DR & ~(1 << 5);
			PRT2DR = PRT2DR & ~(1 << 7);
			
			PWM8_3_WritePulseWidth(255);
			PWM8_4_WritePulseWidth(255);		
		}
		
		/*y軸モータ駆動*/
		else{
			
			PRT2DR = PRT2DR | (1 << 5);
			PRT2DR = PRT2DR | (1 << 7);
			
			PWM8_3_WritePulseWidth(MyI2C_Motor.y_1);
			PWM8_4_WritePulseWidth(MyI2C_Motor.y_2);
		}
		/*zが入力されてなかったらブレーキ*/
		if ((MyI2C_Motor.z_1 == 0)&&(MyI2C_Motor.z_2 == 0)){
			
			PRT2DR = PRT2DR & ~(1 << 0);
			PRT1DR = PRT1DR & ~(1 << 6);
			
			PWM8_5_WritePulseWidth(255);
			PWM8_6_WritePulseWidth(255);
		}
		
		/*z軸モータ駆動*/
		else{
			
			PRT2DR = PRT2DR | (1 << 0);
			PRT1DR = PRT1DR | (1 << 6);
			
			PWM8_5_WritePulseWidth(MyI2C_Motor.z_1);
			PWM8_6_WritePulseWidth(MyI2C_Motor.z_2);
		}
	}
}
