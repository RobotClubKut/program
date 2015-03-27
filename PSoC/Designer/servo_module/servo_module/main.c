//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------
//PSoC1の29466用です
//EzI2Cs_1
//        I2C clock 400k First
//        slave address 12
#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"// PSoC API definitions for all User Modules
#include <string.h>
#include <stdio.h>
#include "PSoCGPIOINT.h"



int putchar(char  c) 
{
	char  str[]=" ";
	strncpy( str , &c , 1 );
	LCD_1_PrString( str );
	return c;
}

/*EzI2Csのデータ設定*/
struct I2C_Servos
{
	BYTE deg[5];
	BYTE air_1;
	BYTE motor_1;
	
} MyI2C_Servos;

void main(void)
{
	int Port_2_Data_SHADE = 0x00;
	int servo_a_[8],servo_b_[8] = {1200},i;
	servo_a_[1] = 2250;
	M8C_EnableGInt ;// Uncomment this line to enable Global Interrupts
					// Insert your main routine code here.
	
	/*MBMの設定*/
//	MBM_1_InitializeMailbox();
//	MBM_1_pMyMailbox = &MBM_1_MyMailbox;
	
	/*PWM１６の１~８をスタート*/
	
	PWM16_1_Start();
	PWM16_2_Start();
	PWM16_3_Start();
	PWM16_4_Start();
	PWM16_5_Start();
	PWM16_6_Start();
	PWM16_7_Start();
	PWM16_8_Start();
	
	/*EzI2Csの１の設定*/
	
	EzI2Cs_1_SetRamBuffer(sizeof(MyI2C_Servos),7, (BYTE *)&MyI2C_Servos);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();
	
	/*LCDの設定*/

	LCD_1_Start();
	
	while (1){
		
		for (i=0;i<=7;i++){
			
			servo_a_[i] = 1200 + MyI2C_Servos.deg[i]*10;
			
		}
		/*マスターから来た角度を計算して出力*/
	
		
	
	/*	servo_a_[0] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_1*10;
		servo_a_[1] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_2*10;
		servo_a_[2] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_3*10;
		servo_a_[3] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_4*10;
		servo_a_[4] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_5*10;
		servo_a_[5] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_6*10;
		servo_a_[6] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_7*10;
		servo_a_[7] = 1200 + MBM_1_MyMailbox.Outbox.servo_deg_8*10; */
		
		
		while (!(servo_a_[0] == servo_b_[0])){
			PWM16_1_WritePulseWidth(servo_a_[0]);
			servo_b_[0] = servo_a_[0];
		}
		while (!(servo_a_[1] == servo_b_[1])){
			PWM16_2_WritePulseWidth(servo_a_[1]);
			servo_b_[1] = servo_a_[1];
		}			
		while (!(servo_a_[2] == servo_b_[2])){
			PWM16_3_WritePulseWidth(servo_a_[2]);
			servo_b_[2] = servo_a_[2];
		}			
		while (!(servo_a_[3] == servo_b_[3])){
			PWM16_4_WritePulseWidth(servo_a_[3]);
			servo_b_[3] = servo_a_[3];
		}			
		while (!(servo_a_[4] == servo_b_[4])){
			PWM16_5_WritePulseWidth(servo_a_[4]);
			servo_b_[4] = servo_a_[4];
		}			
/*		while (!(servo_a_[5] == servo_b_[5])){
			PWM16_6_WritePulseWidth(servo_a_[5]);
			servo_b_[5] = servo_a_[5];
		}			
		while (!(servo_a_[6] == servo_b_[6])){
			PWM16_7_WritePulseWidth(servo_a_[6]);
			servo_b_[6] = servo_a_[6];
		}			
		while (!(servo_a_[7] == servo_b_[7])){
			PWM16_8_WritePulseWidth(servo_a_[7]);
			servo_b_[7] = servo_a_[7];
		}*/
		
		/*サーボ*/
		
		
		
		
		
		/*空気の開閉*/
		
		if (MyI2C_Servos.air_1 == 1){
			
			Port_2_Data_SHADE |= 0x08;
			PRT2DR = Port_2_Data_SHADE;
						
		}
		
		else {
			
			Port_2_Data_SHADE &= ~0x08;
			PRT2DR =Port_2_Data_SHADE;
			
		}
		
		/*モータ取り込み*/
		
		if (MyI2C_Servos.motor_1 == 1){
			
			PWM16_6_WritePulseWidth(12000);
			
		}
		
		else{
			
			PWM16_6_WritePulseWidth(0);
			
		}
		
		/*LCDの表示*/
		
		LCD_1_Position(0,0);
		cprintf("%d %d %d %d",MyI2C_Servos.deg[0],MyI2C_Servos.deg[1],MyI2C_Servos.deg[2],MyI2C_Servos.deg[3]);
		LCD_1_Position(1,0);
		cprintf("%d %d %d %d",MyI2C_Servos.deg[4],MyI2C_Servos.deg[5],MyI2C_Servos.deg[6],MyI2C_Servos.deg[7]);
	}
}
