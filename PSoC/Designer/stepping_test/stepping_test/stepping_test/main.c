//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdarg.h>
#include <stdio.h>

void LCD_print(char *str);
void LCD_cprint(const char *str);

BYTE SPI_transceiver(BYTE data);

#pragma interrupt_handler _SPIM_ISR
void _SPIM_ISR(void)
{
	CS_Off();
}

enum L6470_Register
{
	ABS_POS = 1,
	EL_POS,
	MARK,
	SPEED,
	ACC,
	DEC,
	MAX_SPEED,
	MIN_SPEED,
	KVAL_HOLD,
	KVAL_RUN,
	KVAL_ACC,
	KVAL_DEC,
	INT_SPEED,
	ST_SLP,
	FN_SLP_ACC,
	FN_SLP_DEC,
	K_THERM,
	ADC_OUT,
	OCD_TH,
	STALL_TH,
	FS_SPD,
	STEP_MODE,
	ALARM_EN,
	CONFIG,
	STATUS,
};

/*
typedef struct
{
	long ABS_POS : 22;
	int EL_POS : 9;
	long MARK : 22;
	long SPEED : 20;
	WORD ACC : 12;
	WORD DEC : 12;
	WORD MAX_SPEED : 10;
	WORD MIN_SPEED : 13;
	BYTE KVAL_HOLD;
	BYTE KVAL_RUN;
	BYTE KVAL_ACC;
	BYTE KVAL_DEC;
	WORD INT_SPEED : 14;
	BYTE ST_SLP;
	BYTE FN_SLP_ACC;
	BYTE FN_SLP_DEC;
	BYTE K_THERM : 4;
	BYTE ADC_OUT : 5;
	BYTE OCD_TH : 4;
	BYTE STALL_TH : 7;
	WORD FS_SPD : 10;
	BYTE STEP_MODE;
	BYTE ALARM_EN;
} L6470_REG;*/

void L6470_SetParam(BYTE param, ...)
{
	va_list ap;
	va_start(ap, param);
	
	if (param == KVAL_RUN || param == KVAL_ACC || param == KVAL_DEC || param == KVAL_HOLD || param == STEP_MODE)
	{
		BYTE i = va_arg(ap, BYTE);
		SPI_transceiver(param);
		SPI_transceiver(i);
	}
	
	va_end(ap);
}

void L6470_Run(LONG speed)
{
	if (speed < 0)
	{
		SPI_transceiver(0x51);
		speed *= -1;
	}
	else
		SPI_transceiver(0x50);
	
	SPI_transceiver((speed >> 16) & 0x0f);
	SPI_transceiver((speed >> 8) & 0xff);
	SPI_transceiver(speed & 0xff);
}

void main(void)
{
	BYTE i = 0xff;
	LONG j;
	M8C_EnableGInt;
	
	CS_Start();
	CS_Off();
	
	SPIM_1_EnableInt();
	SPIM_1_Start(SPIM_1_SPIM_MODE_0 | SPIM_1_SPIM_MSB_FIRST);
	SPIM_1_SendTxData(0);
	
	SleepTimer_1_EnableInt();
	SleepTimer_1_Start();
	
	LCD_1_Start();
	LCD_cprint("PSoC Start");

	LCD_cprint("Send Command");
	L6470_SetParam(KVAL_RUN, i);
	L6470_SetParam(KVAL_ACC, i);
	L6470_SetParam(KVAL_DEC, i);
	L6470_SetParam(KVAL_HOLD, i);
	SPI_transceiver(0xa8);
	i = 0x07;
	L6470_SetParam(STEP_MODE, i);
	
	i = 128;
	for (j = 0; j <= 30000; j += 5000)
	{
		char str[17] = {0};
		L6470_Run(j);
		csprintf(str, "%ld", j);
		LCD_print(str);
		SleepTimer_1_TickWait(i);
	}
	
	i = 4;
	for (j = 30000; ; j++)
	{
		char str[17] = {0};
		L6470_Run(j);
		csprintf(str, "%ld", j);
		LCD_print(str);
		SleepTimer_1_TickWait(i);
	}
	
	LCD_cprint("Complete");
	while (1);
}


BYTE SPI_transceiver(BYTE data)
{
	while (!(SPIM_1_bReadStatus() & SPIM_1_SPIM_SPI_COMPLETE));
	CS_On();
	SPIM_1_SendTxData(data);
	return SPIM_1_bReadRxData();
}



char lcdStr[17] = {0};

void LCD_print(char *str)
{
	BYTE i;
	LCD_1_Control(LCD_1_DISP_CLEAR_HOME);
	LCD_1_Delay50uTimes(10);
	LCD_1_PrString(str);
	LCD_1_Position(1, 0);
	LCD_1_PrString(lcdStr);
	for (i = 0; i < sizeof(lcdStr); i++)
	{
		lcdStr[i] = str[i];
		if (str[i] == 0)
			break;
	}
}

void LCD_cprint(const char *str)
{
	BYTE i;
	LCD_1_Control(LCD_1_DISP_CLEAR_HOME);
	LCD_1_Delay50uTimes(10);
	LCD_1_PrCString(str);
	LCD_1_Position(1, 0);
	LCD_1_PrString(lcdStr);
	for (i = 0; i < sizeof(lcdStr); i++)
	{
		lcdStr[i] = str[i];
		if (str[i] == 0)
			break;
	}
}
