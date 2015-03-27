//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

struct I2C_Regs
{
	BYTE x;
	BYTE y;
	BYTE z;
	WORD time;
} MyI2C_Regs;
	

void main(void)
{	
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	
	
	LCD_1_Start();
	LCD_1_Position(0, 0);
	LCD_1_PrCString("PSoC_Start");
	
	EzI2Cs_1_SetRamBuffer(sizeof(MyI2C_Regs), 3, (BYTE *)&MyI2C_Regs);
	EzI2Cs_1_Start();
	EzI2Cs_1_EnableInt();
	
	LCD_1_Position(1, 0);
	LCD_1_PrCString("I2C_Start");
	
	Timer16_1_Start();
	Timer16_1_EnableInt();
	while (TRUE)
	{
		
	}
}

#pragma interrupt_handler _Timer16_1_ISR
#pragma nomac
void _Timer16_1_ISR(void)
{
	LCD_1_Control(LCD_1_DISP_CLEAR_HOME);
	LCD_1_Position(0, 0);
	LCD_1_PrCString("x   y   z   time");
	LCD_1_Position(1, 0);
	LCD_1_PrHexByte(MyI2C_Regs.x);
	LCD_1_Position(1, 4);
	LCD_1_PrHexByte(MyI2C_Regs.y);
	LCD_1_Position(1, 8);
	LCD_1_PrHexByte(MyI2C_Regs.z);
	LCD_1_Position(1, 12);
	LCD_1_PrHexInt(MyI2C_Regs.time++);
}
#pragma usemac
