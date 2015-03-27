//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------
//PSoC1の29446用です。
//配線はxのhighが
//        lowが　
//     yのhighが
//		  lowが
//     zのhighが
//		  lowが 
//EZI2Cs_1  slave　address 11
//          I2C clock 400k First



#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

/*
struct I2C_Motor
{
	BYTE x_1;
	BYTE x_2;
	BYTE y_1;
	BYTE y_2;
	BYTE z_1;
	BYTE z_2;
	
} MyI2C_Motor;
*/

int  x_y_z_motor_control(int mode);




void main(void)
{
	
	/*(旧)メールボックスの値*/
	unsigned  char 	X_TRD_b = 0;
	unsigned  char  Y_TRD_b = 0;
	unsigned  char  Z_TRD_b = 0;
	unsigned  char  X_SPEED_b = 0;
	unsigned  char  Y_SPEED_b = 0;
	unsigned  char  Z_SPEED_b = 0;
	unsigned  char  OUTBOX_FLAG_b = 0;
	
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	/*ポートの初期化いらない*/
/*	PRT2DR = 0x00;
	PRT1DR = 0x00;
	PRT0DR = 0x00;*/
	
	/*PWM8の1~6をスタート*/
	PWM8_1_Start();
	PWM8_2_Start();
	PWM8_3_Start();
	
	/*メールボックスの設定*/
	MBM_1_InitializeMailbox();
	
	/*EzI2Cs_1の設定*/
	EzI2Cs_1_SetRamBuffer(sizeof(MBM_1_MyMailbox),10, (BYTE *)&MBM_1_MyMailbox);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();
	
	/*SleepTimerの設定*/
	
	SleepTimer_1_Start();
	SleepTimer_1_EnableInt();
	SleepTimer_1_SetInterval(0x18);
	
		
	/*テストプログラム*/
/*	while (1){
		SleepTimer_1_TickWait(4);
		RDI0RO0 = 0x01;
		PRT2GS = 0x01;
		
		SleepTimer_1_TickWait(4);
		PRT2GS = 0x00;
		
		
		SleepTimer_1_TickWait(4);
		RDI0RO0 = 0x04;
		PRT1GS = 0x01;
		
		
		SleepTimer_1_TickWait(4);
		PRT1GS = 0x00;
	}*/
	
	
	/*メイン処理２*/
	while (1){
		/*(新)メールボックスの値を別の変数に置き換え*/
		BYTE X_TRD_a = MBM_1_MyMailbox.Outbox.x_trd;
		BYTE Y_TRD_a = MBM_1_MyMailbox.Outbox.y_trd;
		BYTE Z_TRD_a = MBM_1_MyMailbox.Outbox.z_trd;
		BYTE X_SPEED_a = MBM_1_MyMailbox.Outbox.x_speed;
		BYTE Y_SPEED_a = MBM_1_MyMailbox.Outbox.y_speed;
		BYTE Z_SPEED_a = MBM_1_MyMailbox.Outbox.z_speed;
		BYTE OUTBOX_FLAG_a = MBM_1_MyMailbox.Outbox.outbox_flag;
		
		/*xの方向か速度が変化した場合*/
		if (!((X_TRD_a == X_TRD_b)||(X_SPEED_a == X_SPEED_b))){
			
			
			
			if (X_TRD_a == 1){
				
				/*ピンの切り替え*/
				PRT1GS &= ~(1 << 0) ;//Port_1_0をOFF
				RDI0RO0 &= ~(1 << 2);//GOO[0]をOFF
				RDI0RO0 |= (1 << 0);//GOE[0]をON
				PRT2GS |= (1 << 0);//Port_2_0をON
				
				x_y_z_motor_control(1);
				
				/*データを保存*/
				X_TRD_b = X_TRD_a;
				X_SPEED_b = X_SPEED_a;
			}
			
			else if (X_TRD_a == 0){
				
				/*ピンの切り替え*/
				PRT2GS &= ~(1 << 0);//Port_2_0をOFF
				RDI0RO0 &= ~(1 << 0);//GOE[0]をOFF
				RDI0RO0 |= (1 << 2);//GOO[0]をON
				PRT1GS |= (1 << 0);//Port_1_0をON
				
				x_y_z_motor_control(2);
				
				/*データを保存*/
				X_TRD_b = X_TRD_a;
				X_SPEED_b = X_SPEED_a;
			}
		}
		/*yの方向か速度が変化した場合*/
		if (!((Y_TRD_a == Y_TRD_b)||(Y_SPEED_a == Y_SPEED_b))){
			
			
			
			if (X_TRD_a == 1){
				
				/*ピンの切り替え*/
				PRT1GS &= ~(1 << 1);//Port_1_1をOFF
				RDI0RO0 &= ~(1 << 6);//GOO[1]をOFF
				RDI0RO0 |= (1 << 4);//GOE[1]をON
				PRT2GS |= (1 << 1);//Port_2_1をON
				
				x_y_z_motor_control(3);
				
				/*データを保存*/
				Y_TRD_b = Y_TRD_a;
				Y_SPEED_b = Y_SPEED_a;
			}
			
			else if (Y_TRD_a == 0){
				
				/*ピンの切り替え*/
				PRT2GS &= ~(1 << 1);//Port_2_1をOFF
				RDI0RO0 &= ~(1 << 4);//GOE[1]をOFF
				RDI0RO0 |= (1 << 6);//GOO[1]をON
				PRT1GS |= (1 << 1);//Port_1_1をON
				
				x_y_z_motor_control(4);
				
				/*データを保存*/
				Y_TRD_b = Y_TRD_a;
				Y_SPEED_b = Y_SPEED_a;
			}
		}
		/*zの方向か速度が変化した場合*/
		if (!((Z_TRD_a == Z_TRD_b)||(Z_SPEED_a == Z_SPEED_b))){
			
			
			
			if (X_TRD_a == 1){
				
				/*ピンの切り替え*/
				PRT1GS &= ~(1 << 2) ;//Port_1_2をOFF
				RDI0RO1 &= ~(1 << 2);//GOO[2]をOFF
				RDI0RO1 |= (1 << 0);//GOE[2]をON 
				PRT2GS |= (1 << 1);//Port_2_1をON
				
				x_y_z_motor_control(5);
				
				/*データを保存*/
				Z_TRD_b = Z_TRD_a;
				Z_SPEED_b = Z_SPEED_a;
			}
			
			else if (Z_TRD_a == 0){
				
				/*ピンの切り替え*/
				PRT2GS &= ~(1 << 1);//Port_2_1をOFF
				RDI0RO1 &= ~(1 << 0);//GOE[2]をOFF
				RDI0RO1 |= (1 << 2);//GOO[2]をON
				PRT1GS |= (1 << 1);//Port_1_1をON
				
				x_y_z_motor_control(6);
				
				/*データを保存*/
				Z_TRD_b = Z_TRD_a;
				Z_SPEED_b = Z_SPEED_a;
			}
		}
	}
}

int  x_y_z_motor_control(int mode)
{
	
}			
		
	/*メイン処理(没)*/
/*	while (1){
		xが入力されてなかったらブレーキ
		if ((MyI2C_Motor.x_1 == 0)&&(MyI2C_Motor.x_2 == 0)){
		
			PRT1DR = PRT1DR & ~(1 << 2);
			PRT1DR = PRT1DR & ~(1 << 3);
			
			PWM8_1_WritePulseWidth(255);
			PWM8_2_WritePulseWidth(255);
		}
		
		x軸モータ駆動
		else if((MyI2C_Motor.x_1 == 0)||(MyI2C_Motor.x_2 == 0)){
			
			PRT1DR = PRT1DR | (1 << 2);
			PRT1DR = PRT1DR | (1 << 3);
			
			PWM8_1_WritePulseWidth(MyI2C_Motor.x_1);
			PWM8_2_WritePulseWidth(MyI2C_Motor.x_2);
		}
		yが入力されてなかったらブレーキ	
		if ((MyI2C_Motor.y_1 == 0)&&(MyI2C_Motor.y_2 == 0)){
			
			PRT2DR = PRT2DR & ~(1 << 5);
			PRT2DR = PRT2DR & ~(1 << 7);
			
			PWM8_3_WritePulseWidth(255);
			PWM8_4_WritePulseWidth(255);		
		}
		
		y軸モータ駆動
		else if ((MyI2C_Motor.y_1 == 0)||(MyI2C_Motor.y_2 == 0)){
			
			PRT2DR = PRT2DR | (1 << 5);
			PRT2DR = PRT2DR | (1 << 7);
			
			PWM8_3_WritePulseWidth(MyI2C_Motor.y_1);
			PWM8_4_WritePulseWidth(MyI2C_Motor.y_2);
		}
		zが入力されてなかったらブレーキ
		if ((MyI2C_Motor.z_1 == 0)&&(MyI2C_Motor.z_2 == 0)){
			
			PRT2DR = PRT2DR & ~(1 << 0);
			PRT1DR = PRT1DR & ~(1 << 6);
			
			PWM8_5_WritePulseWidth(255);
			PWM8_6_WritePulseWidth(255);
		}
		
		z軸モータ駆動
		else if((MyI2C_Motor.z_1 == 0)||(MyI2C_Motor.z_2 == 0)){
			
			PRT2DR = PRT2DR | (1 << 0);
			PRT1DR = PRT1DR | (1 << 6);
			
			PWM8_5_WritePulseWidth(MyI2C_Motor.z_1);
			PWM8_6_WritePulseWidth(MyI2C_Motor.z_2);
		}
	}
}*/
