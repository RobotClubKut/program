//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#define sv1on 17
#define sv1off 31
#define sv2on 0
#define sv2off 0
#define mmspeed 255
struct I2C_Regs
{
	BYTE sv1;
	BYTE sv2;
	BYTE sv3;
    BYTE sv4;
	BYTE mzupdown;
	BYTE mzv;
	BYTE mmupdown;
	BYTE mmv;
} MyI2C_Regs;

void main(void)
{
	/*
	LCD_1_Start();
	LCD_1_Position(0, 0);
	LCD_1_PrCString("PSoC_Start");
	PRT0DR=0b0000100;
	*/
	EzI2Cs_1_SetRamBuffer(sizeof(MyI2C_Regs), 8, (BYTE *)&MyI2C_Regs);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();
	/*
	LCD_1_Position(1, 0);
	LCD_1_PrCString("I2C_Start");
	*/
	PWM8_1_Start();
	PWM8_2_Start();
	PWM8_3_Start();
	PWM8_4_Start();
	PWM8_5_Start();
	PWM8_6_Start();
	while (1)
	{
		//サーボ始め
		if(MyI2C_Regs.sv1==1)
		{
			PWM8_1_WritePulseWidth(sv1on);
			PWM8_2_WritePulseWidth(sv2on);
		}
		else 
		{
			PWM8_1_WritePulseWidth(sv1off);
		    PWM8_2_WritePulseWidth(sv2off);	
		}
		/*
		if (sv3==1)
		{
			
			PWM8_3_WritePulseWidth(sv3off);
		    PWM8_4_WritePulseWidth(sv4off);	
		}
		else
		{
		    PWM8_3_WritePulseWidth(sv3off);
		    PWM8_4_WritePulseWidth(sv4off);	
		}
		//サーボ終わり
		*/
		if (MyI2C_Regs.mzv>0)
	   	{
			if (/*MyI2C_Regs.mzupdown==0*/1)
				{// down BLS=P24
					PWM8_6_WritePulseWidth(0);
					PRT1DR=0b00000101;
			        PWM8_5_WritePulseWidth(MyI2C_Regs.mzv);
				}
		    else 
				{// up ALS=P25
					PWM8_5_WritePulseWidth(0);
					PRT1DR=0b00000101;
			        PWM8_6_WritePulseWidth(MyI2C_Regs.mzv);
				}			
		}
		else 
		{
			PRT1DR=0x00;
			PWM8_5_WritePulseWidth(0);			
			PWM8_6_WritePulseWidth(0);			
		}
		if (MyI2C_Regs.mmv==1)
			{
			if (MyI2C_Regs.mmupdown==0)
			{//down ALI=P02down
				PWM8_4_WritePulseWidth(0);
				PRT2DR=0b00000101; 
				PWM8_3_WritePulseWidth(mmspeed);
			}
			else 
			{//up BLI=P03up
				PWM8_3_WritePulseWidth(0);
				PRT2DR=0b00000101; 
			    PWM8_4_WritePulseWidth(mmspeed);
			}
			}
		else 
			{
				PRT2DR=0x00;
				PWM8_3_WritePulseWidth(0);
				PWM8_4_WritePulseWidth(0);				
			}
	}
	
	
	// M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
}
