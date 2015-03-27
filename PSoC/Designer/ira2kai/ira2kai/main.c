//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules


void main(void)
{
	unsigned char x_result,y_result,z_result;
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	PWM8_1_Start();
	PWM8_2_Start();
	PWM8_3_Start();
	PWM8_4_Start();
	PWM8_5_Start();
	PWM8_6_Start();
	PWM16_1_Start();
	TRIADC_1_Start(3);
	TRIADC_1_GetSamples(0);
	PGA_1_Start(3);
	PGA_2_Start(3);
	PGA_3_Start(3);
	
/*	while (1){
		PWM8_1_WritePulseWidth(255);
		PWM8_2_WritePulseWidth(255);
		PWM8_3_WritePulseWidth(255);
		PWM8_4_WritePulseWidth(255);
		PWM8_5_WritePulseWidth(255);
		PWM8_6_WritePulseWidth(255);
	
	}*/	
	while (1){
		
		while(TRIADC_1_fIsDataAvailable() == 0);	///AD変換待ち
		
		x_result = TRIADC_1_iGetData1();			///x,y,zの値を取得
		y_result = TRIADC_1_iGetData2();			
		z_result = TRIADC_1_iGetData3ClearFlag();	
		
		/////x軸のプログラム//////////////////////////////////
		
		/////x軸の正の方向かつリミットスイッチ１反応なし///////////
		if ((x_result > 150) && (!(PRT1DR & (1 << 1)))){
				
			PWM8_2_WritePulseWidth(x_result);
			PWM8_1_WritePulseWidth(0);

		}
		/////x軸の負の方向かつリミットスイッチ２反応なし////////////
		if ((x_result < 100) && (!(PRT1DR & (1 << 2)))){
				
			PWM8_2_WritePulseWidth(0);
			PWM8_1_WritePulseWidth(255-x_result);
			
		}
		/////x軸の中央またはリミットスイッチ１反応あり///////////////		
		if (((x_result >= 100) && (x_result <= 150)) || (PRT1DR & (1 << 1))){
			
			PWM8_2_WritePulseWidth(0);
			
		}
		/////x軸の中央またはリミットスイッチ２反応あり////////////////
		if (((x_result >= 100) && (x_result <= 150)) || (PRT1DR & (1 << 2))){
			
			PWM8_1_WritePulseWidth(0);
			
		}
		
		/////y軸のプログラム/////////////////////////////////
		
		/////y軸の正の方向かつリミットスイッチ３反応なし///////////
		if ((y_result > 150) && (!(PRT1DR & (1 << 3)))){
				
			PWM8_3_WritePulseWidth(y_result);
			PWM8_4_WritePulseWidth(0);

		}
		
		/////y軸の正の方向かつリミットスイッチ４反応なし///////////
		if ((y_result < 100) && (!(PRT1DR & (1 << 4)))){
				
			PWM8_3_WritePulseWidth(0);
			PWM8_4_WritePulseWidth(255-y_result);
			
		}
		
		/////y軸の中央またはリミットスイッチ３反応あり///////////////
		if (((y_result >= 100) && (y_result <= 150)) || (PRT1DR & (1 << 3))){
			
			PWM8_3_WritePulseWidth(0);
			
		}
		
		/////y軸の中央またはリミットスイッチ4反応あり///////////////
		
		if (((y_result >= 100) && (y_result <= 150)) || (PRT1DR & (1 << 4))){
			
			PWM8_4_WritePulseWidth(0);
			
		}
		
		/////z軸のプログラム////////////////////////////////
		
		/////z軸の正の方向かつリミットスイッチ５反応なし//////////
		if ((z_result > 150) && (!(PRT1DR & (1 << 5)))){
				
			PWM8_5_WritePulseWidth(z_result);
			PWM8_6_WritePulseWidth(0);

		}
		
		/////z軸の負の方向かつリミットスイッチ６反応なし////////
		if ((z_result < 100) && (!(PRT1DR & (1 << 4)))){
				
			PWM8_5_WritePulseWidth(0);
			PWM8_6_WritePulseWidth(255-z_result);
			
		}
		
		/////z軸の中央またはリミットスイッチ５反応あり///////////
		if (((z_result >= 100) && (z_result <= 150)) || (PRT1DR & (1 << 5))){
			
			PWM8_5_WritePulseWidth(0);
			
		}
		
		/////z軸の中央またはリミットスイッチ６反応あり///////////
		if (((z_result >= 100) && (z_result <= 150)) || (PRT1DR & (1 << 6))){
			
			PWM8_6_WritePulseWidth(0);
			
		}
		
		/////servoの角度調節///////////////////////////
		if (PRT1DR & (1 << 7)){
			
			PWM16_1_WritePulseWidth(1200);
			
		}
		
		else  if (!(PRT1DR & (1 << 7))){
			
			PWM16_1_WritePulseWidth(1800);
			
		}
	}
}
