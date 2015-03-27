//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdio.h>
#include <string.h>

int putchar (char c)
{
	char str[] = " ";
	strncpy( str , &c , 1 );
	LCD_1_PrString( str );
	return c;
}
	
void main(void)
{
	int date;
	int target = 20;
	int det_target = 0;
	double kp,ki;
	int det_operation = 0;
	int det_date1 = 0,det_date2 = 0;
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	LCD_1_Start();
	ADCINC_1_Start(3);
	ADCINC_1_GetSamples(0);
	PWM8_1_Start();
	PWM8_2_Start();
	SleepTimer_1_Start();
	SleepTimer_1_SetInterval(SleepTimer_1_1_HZ);
	SleepTimer_1_EnableInt();
	
	//////////////////サーボテストプログラム//////////////////
	while (1){

		////////////////AD変換//////////////////////
		while (ADCINC_1_fIsDataAvailable() == 0);
		LCD_1_Position(0,0);
		date = ADCINC_1_iClearFlagGetData();
		LCD_1_PrCString("AD:");
		LCD_1_PrHexByte(date);
		
		det_date1 = target  - date;
		
		///////////////////////操作量/////////////////
		det_operation = (det_date1 - det_date2) * 2 / 3 + det_date1 * 1 / 3 ;
		
		det_date2 = det_date1;
		
		LCD_1_Position(0,6);
		LCD_1_PrCString("d_op");
		LCD_1_PrHexByte(det_operation);
		////////目標値に達成///////////////
		if (det_operation == 0){
			
			LCD_1_Position(0,12);
			LCD_1_PrCString("stop");
			PWM8_1_WritePulseWidth(255);
			PWM8_2_WritePulseWidth(255);
			
			
			
			if (PRT2DR & (1 << 2)){
				
				target = 0xf0;
				
			}
			
			else if (PRT2DR & (1 << 4)){
				
				target = 0x14;
				
			}
			
			else {
				
				target = 0x80;
			}
		
		}
		/////////目標値とずれていた場合/////////////
		else{
			
			LCD_1_Position(0,12);
			LCD_1_PrCString("    ");
			LCD_1_PrHexByte(det_date1);
			///////目標値より負///////////////
			if (det_operation < 0){
				LCD_1_Position(1,0);
			//	LCD_1_PrCString("se:");
				LCD_1_PrHexInt((BYTE)det_operation);
				PWM8_1_WritePulseWidth(256 + (BYTE)det_operation);
				PWM8_2_WritePulseWidth(0);
			}
			////////目標値より正/////////////
			else{
				LCD_1_Position(1,6);
			//	LCD_1_PrCString("fu:");
				LCD_1_PrHexInt((BYTE)det_operation);
				PWM8_2_WritePulseWidth(215 + (BYTE)det_operation);
				PWM8_1_WritePulseWidth(0);
				
			}
		}
		
	}

	/*
	while(1){
		while (ADCINC_1_fIsDataAvailable() == 0);
		LCD_1_Position(0,0);
		date = ADCINC_1_iClearFlagGetData();
		LCD_1_PrHexByte(date);
	}*/
}
