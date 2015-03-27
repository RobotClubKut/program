//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

#include <stdio.h>

#define I2CIO_WRITE		0x80
#define I2CIO_READ		0x40
#define I2CIO_UPDATE	0x20

#define STOP_X	0x01
#define STOP_Y	0x02
#define STOP_Z	0x04

#define POLY_1	0xE0000200
#define POLY_2	0xE0000200
#define POLY_3	0xE0000200

#define STOPTIME 100
#define BYTETODWRD 16843009

#define bitSet(a, b)	((a) |= (b))
#define bitClear(a, b)	((a) &= ~(b))
#define bitCheck(a, b)	(((a) & (b)) ? TRUE : FALSE)

#define I2CIO_SetWriteFlag()	bitSet(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_WRITE)
#define I2CIO_ClearWriteFlag()	bitClear(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_WRITE)
#define I2CIO_CheckWriteFlag()	bitCheck(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_WRITE)

#define I2CIO_SetReadFlag()		bitSet(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_READ)
#define I2CIO_ClearReadFlag()	bitClear(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_READ)	
#define I2CIO_CheckReadFlag() 	bitCheck(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_READ)

#define I2CIO_SetUpdateFlag()	bitSet(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_UPDATE)
#define I2CIO_ClearUpdateFlag()	bitClear(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_UPDATE)
#define I2CIO_CheckUpdateFlag()	bitCheck(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_UPDATE)

MBM_1_Outbox OutboxBuff = {0};
MBM_1_Inbox InboxBuff = {0};

WORD ct = 0;

void main(void)
{
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	LCD_1_Start();
	LCD_1_Position(0, 0);
	cprintf("PSoC Start");
	
	MBM_1_InitializeMailbox();
	MBM_1_pMyMailbox = &MBM_1_MyMailbox;
	
	EzI2Cs_1_SetRamBuffer(sizeof (MBM_1_MyMailbox), INBOXFLAG + 1, (BYTE *)MBM_1_pMyMailbox);
	EzI2Cs_1_Start();
	EzI2Cs_1_ResumeInt();
	
	LCD_1_Position(1, 0);
	cprintf("I2C Start");
	
	PRS32_1_WritePolynomial(POLY_1);
	PRS32_1_WriteSeed(0);
	PRS32_1_Start();
	
	PRS32_2_WritePolynomial(POLY_2);
	PRS32_2_WriteSeed(0);
	PRS32_2_Start();
	
	PRS32_3_WritePolynomial(POLY_3);
	PRS32_3_WriteSeed(0);
	PRS32_3_Start();
	
	Timer8_1_Start();
	Timer8_1_EnableInt();
	
	LCD_1_Position(0, 0);
	cprintf("Motor Start");
	
	LCD_1_Position(0, 0);
	cprintf("BF Xs Ys Zs time");
	
	while (TRUE)
	{
		//I2C Read 
		if (I2CIO_CheckUpdateFlag())
		{
			Timer8_1_DisableInt();
			I2CIO_SetReadFlag();
			while (I2CIO_CheckWriteFlag());
			OutboxBuff = MBM_1_MyMailbox.Outbox;
			I2CIO_ClearUpdateFlag();
			I2CIO_ClearReadFlag();
			Timer8_1_EnableInt();
		}
		
		//I2C Write
		if (bitCheck(InboxBuff.InboxFlag, I2CIO_UPDATE))
		{
			Timer8_1_DisableInt();
			I2CIO_SetWriteFlag();
			while (I2CIO_CheckReadFlag());
			InboxBuff.InboxFlag = MBM_1_MyMailbox.Inbox.InboxFlag;
			MBM_1_MyMailbox.Inbox = InboxBuff;
			I2CIO_SetUpdateFlag();
			I2CIO_ClearWriteFlag();
			InboxBuff.InboxFlag = 0;
			Timer8_1_EnableInt();
		}
		
		LCD_1_Position(0, 0);
		cprintf(
			"B%02X X%02X Y%02X Z%02X time",
			OutboxBuff.TBrakeFlag,
			OutboxBuff.X_trs,
			OutboxBuff.Y_trs,
			OutboxBuff.Z_trs);
		
		LCD_1_Position(1, 0);
		cprintf(
			"B%02X X%02X Y%02X Z%02X %04X",
			InboxBuff.CBrakeFlag,
			InboxBuff.X_crs,
			InboxBuff.Y_crs,
			InboxBuff.Z_crs,
			ct);
	}
}

#define STOP	0x00
#define CW		0x01
#define CCW		0x03

#pragma interrupt_handler _Timer8_1_ISR
void _Timer8_1_ISR(void)
{
	static BYTE rdx = STOP;
	static BYTE rdy = STOP;
	static BYTE rdz = STOP;
	
	static INT pwm_x = 0;
	static INT pwm_y = 0;
	static INT pwm_z = 0;
	
	static INT ix = 0;
	static INT iy = 0;
	static INT iz = 0;
	
	static BYTE countx = 0;
	static BYTE county = 0;
	static BYTE countz = 0;
	
	static BYTE sw = 0;
	
	if (sw == 0)
	{
		//X motor
		if (bitCheck(OutboxBuff.TBrakeFlag, STOP_X))
		{
			if (countx < STOPTIME)
			{
				if (!bitCheck(InboxBuff.CBrakeFlag, STOP_X))
				{
					//xah off
					bitClear(XAH_DataShadow, XAH_MASK);
					XAH_Data_ADDR = XAH_DataShadow;
					//xbh off
					bitClear(XBH_DataShadow, XBH_MASK);
					XBH_Data_ADDR = XBH_DataShadow;
					//xal off
					bitClear(XAL_DataShadow, XAL_MASK);
					XAL_Data_ADDR = XAL_DataShadow;
					bitClear(XAL_GlobalSelect_ADDR, XAL_MASK);
					//xbl off
					bitClear(XBL_DataShadow, XBL_MASK);
					XBL_Data_ADDR = XBL_DataShadow;
					bitClear(XBL_GlobalSelect_ADDR, XBL_MASK);
					
					bitSet(InboxBuff.CBrakeFlag, STOP_X);
					pwm_x = 0;
					ix = 0;
					InboxBuff.X_crs = 0;
					rdx = STOP;
					bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
				}
				countx++;
			}
			else if (countx == STOPTIME)
			{
				//xal on
				bitSet(XAL_DataShadow, XAL_MASK);
				XAL_Data_ADDR = XAL_DataShadow;
				//xbl on
				bitSet(XBL_DataShadow, XBL_MASK);
				XBL_Data_ADDR = XBL_DataShadow;
				
				countx++;
			}
			
		}
		else
		{
			INT px = ((CHAR)OutboxBuff.X_trs - pwm_x);
			INT tmpx = 0;
			ix += px;
			pwm_x += ((px * OutboxBuff.Kp_X + ix * OutboxBuff.Ki_X) / (1 << OutboxBuff.bshift_X));
			
			if (bitCheck(InboxBuff.CBrakeFlag, STOP_X))
			{
				countx = 0;
				bitClear(InboxBuff.CBrakeFlag, STOP_X);
			}
			
			if (pwm_x > 127)
				tmpx = 127;
			else if (pwm_x < -128)
				tmpx = -128;
			else
				tmpx = pwm_x;
			
			//rotation cw
			if (tmpx >= 0)
			{
				if (rdx != CW)
				{
					//xah off
					bitClear(XAH_DataShadow, XAH_MASK);
					XAH_Data_ADDR = XAH_DataShadow;
					//xbh on
					bitSet(XBH_DataShadow, XBH_MASK);
					XBH_Data_ADDR = XBH_DataShadow;
					//xbl off
					bitClear(XBL_DataShadow, XBL_MASK);
					XBL_Data_ADDR = XBL_DataShadow;
					bitClear(XBL_GlobalSelect_ADDR, XBL_MASK);
					//xal pwm on
					bitSet(XAL_GlobalSelect_ADDR, XAL_MASK);
					
					rdx = CW;
				}
				
				InboxBuff.X_crs = (BYTE)(tmpx * 2 + 1);
				PRS32_1_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.X_crs);
			}
			//rotation ccw
			else
			{
				if (rdx != CCW)
				{
					//xbh off
					bitClear(XBH_DataShadow, XBH_MASK);
					XBH_Data_ADDR = XBH_DataShadow;
					//xah on
					bitSet(XAH_DataShadow, XAH_MASK);
					XAH_Data_ADDR = XAH_DataShadow;
					//xal off
					bitClear(XAL_DataShadow, XAL_MASK);
					XAL_Data_ADDR = XAL_DataShadow;
					bitClear(XAL_GlobalSelect_ADDR, XAL_MASK);
					//xbl pwm on
					bitSet(XBL_GlobalSelect_ADDR, XBL_MASK);
					
					rdx = CCW;
				}
				
				InboxBuff.X_crs = (BYTE)(tmpx * (-2) - 1);
				PRS32_1_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.X_crs);
			}
			
			bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
		}
		//end X
		sw++;
	}
	
	else if (sw == 1)
	{
		//Y motor
		if (bitCheck(OutboxBuff.TBrakeFlag, STOP_Y))
		{
			if (county < STOPTIME)
			{
				if (!bitCheck(InboxBuff.CBrakeFlag, STOP_Y))
				{
					//yah off
					bitClear(YAH_DataShadow, YAH_MASK);
					YAH_Data_ADDR = YAH_DataShadow;
					//ybh off
					bitClear(YBH_DataShadow, YBH_MASK);
					YBH_Data_ADDR = YBH_DataShadow;
					//yal off
					bitClear(YAL_DataShadow, YAL_MASK);
					YAL_Data_ADDR = YAL_DataShadow;
					bitClear(YAL_GlobalSelect_ADDR, YAL_MASK);
					//ybl off
					bitClear(YBL_DataShadow, YBL_MASK);
					YBL_Data_ADDR = YBL_DataShadow;
					bitClear(YBL_GlobalSelect_ADDR, YBL_MASK);
					
					bitSet(InboxBuff.CBrakeFlag, STOP_Y);
					pwm_y = 0;
					iy = 0;
					InboxBuff.Y_crs = 0;
					rdy = STOP;
					bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
				}
				county++;
			}
			else if (county == STOPTIME)
			{
				//yal on
				bitSet(YAL_DataShadow, YAL_MASK);
				YAL_Data_ADDR = YAL_DataShadow;
				//ybl on
				bitSet(YBL_DataShadow, YBL_MASK);
				YBL_Data_ADDR = YBL_DataShadow;
				
				county++;
			}
			
		}
		else
		{
			INT py = ((CHAR)OutboxBuff.Y_trs - pwm_y);
			INT tmpy = 0;
			iy += py;
			pwm_y += ((py * OutboxBuff.Kp_Y + iy * OutboxBuff.Ki_Y) / (1 << OutboxBuff.bshift_Y));
			
			if (bitCheck(InboxBuff.CBrakeFlag, STOP_Y))
			{
				county = 0;
				bitClear(InboxBuff.CBrakeFlag, STOP_Y);
			}
			
			if (pwm_y > 127)
				tmpy = 127;
			else if (pwm_y < -128)
				tmpy = -128;
			else
				tmpy = pwm_y;
			
			//rotation cw
			if (tmpy >= 0)
			{
				if (rdy != CW)
				{
					//yah off
					bitClear(YAH_DataShadow, YAH_MASK);
					YAH_Data_ADDR = YAH_DataShadow;
					//ybh on
					bitSet(YBH_DataShadow, YBH_MASK);
					YBH_Data_ADDR = YBH_DataShadow;
					//ybl off
					bitClear(YBL_DataShadow, YBL_MASK);
					YBL_Data_ADDR = YBL_DataShadow;
					bitClear(YBL_GlobalSelect_ADDR, YBL_MASK);
					//yal pwm on
					bitSet(YAL_GlobalSelect_ADDR, YAL_MASK);
					
					rdy = CW;
				}
				
				InboxBuff.Y_crs = (BYTE)(tmpy * 2 + 1);
				PRS32_2_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.Y_crs);
			}
			//rotation ccw
			else
			{
				if (rdy != CCW)
				{
					//ybh off
					bitClear(YBH_DataShadow, YBH_MASK);
					YBH_Data_ADDR = YBH_DataShadow;
					//yah on
					bitSet(YAH_DataShadow, YAH_MASK);
					YAH_Data_ADDR = YAH_DataShadow;
					//yal off
					bitClear(YAL_DataShadow, YAL_MASK);
					YAL_Data_ADDR = YAL_DataShadow;
					bitClear(YAL_GlobalSelect_ADDR, YAL_MASK);
					//ybl pwm on
					bitSet(YBL_GlobalSelect_ADDR, YBL_MASK);
					
					rdy = CCW;
				}
				
				InboxBuff.Y_crs = (BYTE)(tmpy * (-2) - 1);
				PRS32_2_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.Y_crs);
			}
			
			bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
		}
		//end Y
		sw++;
	}
	
	else
	{
		//Z motor
		if (bitCheck(OutboxBuff.TBrakeFlag, STOP_Z))
		{
			if (countz < STOPTIME)
			{
				if (!bitCheck(InboxBuff.CBrakeFlag, STOP_Z))
				{
					//zah off
					bitClear(ZAH_DataShadow, ZAH_MASK);
					ZAH_Data_ADDR = ZAH_DataShadow;
					//zbh off
					bitClear(ZBH_DataShadow, ZBH_MASK);
					ZBH_Data_ADDR = ZBH_DataShadow;
					//zal off
					bitClear(ZAL_DataShadow, ZAL_MASK);
					ZAL_Data_ADDR = ZAL_DataShadow;
					bitClear(ZAL_GlobalSelect_ADDR, ZAL_MASK);
					//zbl off
					bitClear(ZBL_DataShadow, ZBL_MASK);
					ZBL_Data_ADDR = ZBL_DataShadow;
					bitClear(ZBL_GlobalSelect_ADDR, ZBL_MASK);
					
					bitSet(InboxBuff.CBrakeFlag, STOP_Z);
					pwm_z = 0;
					iz = 0;
					InboxBuff.Z_crs = 0;
					rdz = STOP;
					bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
				}
				countz++;
			}
			else if (countz == STOPTIME)
			{
				//zal on
				bitSet(ZAL_DataShadow, ZAL_MASK);
				ZAL_Data_ADDR = ZAL_DataShadow;
				//zbl on
				bitSet(ZBL_DataShadow, ZBL_MASK);
				ZBL_Data_ADDR = ZBL_DataShadow;
				
				countz++;
			}
			
		}
		else
		{
			INT pz = ((CHAR)OutboxBuff.Z_trs - pwm_z);
			INT tmpz = 0;
			iz += pz;
			pwm_z += ((pz * OutboxBuff.Kp_Z + iz * OutboxBuff.Ki_Z) / (1 << OutboxBuff.bshift_Z));
			
			if (bitCheck(InboxBuff.CBrakeFlag, STOP_Z))
			{
				countz = 0;
				bitClear(InboxBuff.CBrakeFlag, STOP_Z);
			}
			
			if (pwm_z > 127)
				tmpz = 127;
			else if (pwm_z < -128)
				tmpz = -128;
			else
				tmpz = pwm_z;
			
			//rotation cw
			if (tmpz >= 0)
			{
				if (rdz != CW)
				{
					//zah off
					bitClear(ZAH_DataShadow, ZAH_MASK);
					ZAH_Data_ADDR = ZAH_DataShadow;
					//zbh on
					bitSet(ZBH_DataShadow, ZBH_MASK);
					ZBH_Data_ADDR = ZBH_DataShadow;
					//zbl off
					bitClear(ZBL_DataShadow, ZBL_MASK);
					ZBL_Data_ADDR = ZBL_DataShadow;
					bitClear(ZBL_GlobalSelect_ADDR, ZBL_MASK);
					//zal pwm on
					bitSet(ZAL_GlobalSelect_ADDR, ZAL_MASK);
					
					rdz = CW;
				}
				
				InboxBuff.Z_crs = (BYTE)(tmpz * 2 + 1);
				PRS32_3_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.Z_crs);
			}
			//rotation ccw
			else
			{
				if (rdz != CCW)
				{
					//zbh off
					bitClear(ZBH_DataShadow, ZBH_MASK);
					ZBH_Data_ADDR = ZBH_DataShadow;
					//zah on
					bitSet(ZAH_DataShadow, ZAH_MASK);
					ZAH_Data_ADDR = ZAH_DataShadow;
					//zal off
					bitClear(ZAL_DataShadow, ZAL_MASK);
					ZAL_Data_ADDR = ZAL_DataShadow;
					bitClear(ZAL_GlobalSelect_ADDR, ZAL_MASK);
					//zbl pwm on
					bitSet(ZBL_GlobalSelect_ADDR, ZBL_MASK);
					
					rdz = CCW;
				}
				
				InboxBuff.Z_crs = (BYTE)(tmpz * (-2) - 1);
				PRS32_3_WriteSeed(BYTETODWRD * (DWORD)InboxBuff.Z_crs);
			}
			
			bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
		}
		//end Z
		sw = 0;
	}
	
	ct++;
}

int putchar(char c)
{
	char str[2] = {0};
	str[0] = c;
	LCD_1_PrString(str);
	return c;
}
