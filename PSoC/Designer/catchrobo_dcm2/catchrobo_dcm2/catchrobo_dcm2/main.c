//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdio.h>

//MBM & I2C Flag
#define I2CIO_WRITE		0x80
#define I2CIO_READ		0x40
#define I2CIO_UPDATE	0x20

//BrakeFlag
#define STOP_X	0x01
#define STOP_Y	0x02
#define STOP_Z	0x04

//set prs
#define prsSet(dw, b)	(*(BYTE *)&(dw) = (*((BYTE *)&(dw) + 1) = (*((BYTE *)&(dw) + 2) = (*(((BYTE *)&(dw)) + 3) = (b)))))

//prs poly balue
#define POLY	0xE0000200

//brake delay time
#define STOPCOUNT_X	0xff
#define STOPINC_X	0x01
#define STOPCOUNT_Y	0xff
#define STOPINC_Y	0x01
#define STOPCOUNT_Z	0xff
#define STOPINC_Z	0x04

//rotation direction flag
#define STOP	0x00
#define CW		0x01
#define CCW		0x02

//bit macro
#define bitSet(a, b)	((a) |= (b))
#define bitClear(a, b)	((a) &= ~(b))
#define bitCheck(a, b)	((a) & (b))

//I2C buff
MBM_1_Outbox	OutboxBuff;
MBM_1_Inbox		InboxBuff;

//prs seed
DWORD	prs_X;
DWORD	prs_Y;
DWORD	prs_Z;

//prs seed update flag
BOOL	sw_X = TRUE;
BOOL	sw_Y = TRUE;
BOOL	sw_Z = TRUE;

BYTE ct;
BYTE ec;

BOOL i2cchekc = FALSE;

void main(void)
{
	M8C_EnableGInt ; // Uncomment this line to enable Global Interrupts
	// Insert your main routine code here.
	
	//init LCD
	LCD_1_Start();
	LCD_1_Control(LCD_1_DISP_CLEAR_HOME);
	
	//init MBM
	MBM_1_InitializeMailbox();
	MBM_1_pMyMailbox = &MBM_1_MyMailbox;
	
	//init EzI2C
	EzI2Cs_1_SetRamBuffer(sizeof (MBM_1_MyMailbox), (INBOXFLAG + 1), (BYTE *)&MBM_1_MyMailbox);
	EzI2Cs_1_Start();
	EzI2Cs_1_ResumeInt();
	
	//init PRS
	PRS32_X_WritePolynomial(POLY);
	PRS32_X_WriteSeed(0);
	PRS32_X_Start();
	
	PRS32_Y_WritePolynomial(POLY);
	PRS32_Y_WriteSeed(0);
	PRS32_Y_Start();
	
	PRS32_Z_WritePolynomial(POLY);
	PRS32_Z_WriteSeed(0);
	PRS32_Z_Start();
	
	//init Timer
	Timer8_1_Start();
	Timer8_1_EnableInt();
	
	LCD_1_Position(0, 0);
	cprintf("DC Motor Module");
	LCD_1_Position(1, 5);
	cprintf("Start");
	
	//main loop
	while (TRUE)
	{
		
		//I2C Read
		if (bitCheck(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_UPDATE))
		{
			BYTE wate;
			bitSet(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_READ);
			for (wate = 0; wate < 0xff; wate++)
			{
				if (bitCheck(~MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_WRITE))
				{
					OutboxBuff = MBM_1_MyMailbox.Outbox;
					bitClear(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_UPDATE);
					i2cchekc = TRUE;
					break;
				}
			}
			bitClear(MBM_1_MyMailbox.Outbox.OutboxFlag, I2CIO_READ);
		}
		
		//I2C Write
		if (bitCheck(InboxBuff.InboxFlag, I2CIO_UPDATE))
		{
			BYTE wate;
			bitSet(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_WRITE);
			for (wate = 0; wate < 0xff; wate++)
			{
				if (~bitCheck(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_READ))
				{
					InboxBuff.InboxFlag = MBM_1_MyMailbox.Inbox.InboxFlag;
					MBM_1_MyMailbox.Inbox = InboxBuff;
					bitSet(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_UPDATE);
					InboxBuff.InboxFlag = 0;
					break;
				}
			}
			bitClear(MBM_1_MyMailbox.Inbox.InboxFlag, I2CIO_WRITE);
		}
		
		//calclate X motor
		if (sw_X)
		{
			static BYTE count_X;
			static BYTE rd_X;
			static INT pwm_X;
			static LONG iX;
			
			//stop & brake 
			if (bitCheck(OutboxBuff.TBrakeFlag, STOP_X))
			{
				//brake
				if (count_X < (STOPCOUNT_X - STOPINC_X))
				{
					//brake start
					if (rd_X)
					{
						PRS32_X_WriteSeed(0);
						
						//XAH off
						XAH_Data_ADDR = bitClear(XAH_DataShadow, XAH_MASK);
						//XBH off
						XBH_Data_ADDR = bitClear(XBH_DataShadow, XBH_MASK);
						//XAL prs on
						bitSet(XAL_GlobalSelect_ADDR, XAL_MASK);
						//XBL prs on
						bitSet(XBL_GlobalSelect_ADDR, XBL_MASK);
						
						bitSet(InboxBuff.CBrakeFlag, STOP_X);
						bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
						InboxBuff.X_crs = 0;
						pwm_X = 0;
						iX = 0;
						count_X = 0;
						rd_X = STOP;
					}
					//set prs
					prsSet(prs_X, count_X);
					PRS32_X_WriteSeed(prs_X);
					count_X += STOPINC_X;
				}
				//lock
				else if (count_X != 0xff)
				{
					//XAL on & prs off
					XAL_Data_ADDR = bitSet(XAL_DataShadow, XAL_MASK);
					bitClear(XAL_GlobalSelect_ADDR, XAL_MASK);
					//XBL on & prs off
					XBL_Data_ADDR = bitSet(XBL_DataShadow, XBL_MASK);
					bitClear(XBL_GlobalSelect_ADDR, XBL_MASK);
					
					count_X = 0xff;
				}
			}
			//rotation
			else
			{
				INT pX;
				LONG tmpx0;
				BYTE tmpx1;
				
				if (rd_X == STOP)
				{
					bitClear(InboxBuff.CBrakeFlag, STOP_X);
					count_X = 0;
				}
				
				//calclate PI
				pX = ((*(CHAR *)&(OutboxBuff.X_trs)) - pwm_X);
				iX += pX;
				tmpx0 = (OutboxBuff.Kp_X * (LONG)pX + OutboxBuff.Ki_X * iX);
				if (tmpx0 < 0)
				{
					pwm_X += (~((~tmpx0) >> OutboxBuff.bshift_X));
				}
				else
				{
					pwm_X += (tmpx0 >> OutboxBuff.bshift_X);
				}
				
				//CCW
				if (pwm_X < 0)
				{
					if (bitCheck(~rd_X, CCW))
					{
						PRS32_X_WriteSeed(0);
						
						//XAH off
						XAH_Data_ADDR = bitClear(XAH_DataShadow, XAH_MASK);
						//XBL & prs off
						XBL_Data_ADDR = bitClear(XBL_DataShadow, XBL_MASK);
						bitClear(XBL_GlobalSelect_ADDR, XBL_MASK);
						//XBH on
						XBH_Data_ADDR = bitSet(XBH_DataShadow, XBH_MASK);
						//XAL prs on
						bitSet(XAL_GlobalSelect_ADDR, XAL_MASK);
						
						rd_X = CCW;
					}
					
					if (pwm_X <= -128)
					{
						InboxBuff.X_crs = 0x80;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.X_crs)) = pwm_X;
						tmpx1 = (((~InboxBuff.X_crs) << 1) + 1);
					}
				}
				//CW
				else
				{
					if (bitCheck(~rd_X, CW))
					{
						PRS32_X_WriteSeed(0);
						
						//XBH off
						XBH_Data_ADDR = bitClear(XBH_DataShadow, XBH_MASK);
						//XAL & prs off
						XAL_Data_ADDR = bitClear(XAL_DataShadow, XAL_MASK);
						bitClear(XAL_GlobalSelect_ADDR, XAL_MASK);
						//XAH on
						XAH_Data_ADDR = bitSet(XAH_DataShadow, XAH_MASK);
						//XBL prs on
						bitSet(XBL_GlobalSelect_ADDR, XBL_MASK);
						
						rd_X = CW;
					}
					
					if (pwm_X >= 127)
					{
						InboxBuff.X_crs = 0x7f;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.X_crs)) = pwm_X;
						tmpx1 = ((InboxBuff.X_crs << 1) + 1);
					}
				}
				
				prsSet(prs_X, tmpx1);
				bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
			}
			
			sw_X = FALSE;
		}
		//end X
		
		//calclate Y motor
		if (sw_Y)
		{
			static BYTE count_Y;
			static BYTE rd_Y;
			static INT pwm_Y;
			static LONG iY;
			
			//stop & brake 
			if (bitCheck(OutboxBuff.TBrakeFlag, STOP_Y))
			{
				//brake
				if (count_Y < (STOPCOUNT_Y - STOPINC_Y))
				{
					//brake start
					if (rd_Y)
					{
						PRS32_Y_WriteSeed(0);
						
						//YAH off
						YAH_Data_ADDR = bitClear(YAH_DataShadow, YAH_MASK);
						//YBH off
						YBH_Data_ADDR = bitClear(YBH_DataShadow, YBH_MASK);
						//YAL prs on
						bitSet(YAL_GlobalSelect_ADDR, YAL_MASK);
						//YBL prs on
						bitSet(YBL_GlobalSelect_ADDR, YBL_MASK);
						
						bitSet(InboxBuff.CBrakeFlag, STOP_Y);
						bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
						InboxBuff.Y_crs = 0;
						pwm_Y = 0;
						iY = 0;
						count_Y = 0;
						rd_Y = STOP;
					}
					//set prs
					prsSet(prs_Y, count_Y);
					PRS32_Y_WriteSeed(prs_Y);
					count_Y += STOPINC_Y;
				}
				//lock
				else if (count_Y != 0xff)
				{
					//YAL on & prs off
					YAL_Data_ADDR = bitSet(YAL_DataShadow, YAL_MASK);
					bitClear(YAL_GlobalSelect_ADDR, YAL_MASK);
					//YBL on & prs off
					YBL_Data_ADDR = bitSet(YBL_DataShadow, YBL_MASK);
					bitClear(YBL_GlobalSelect_ADDR, YBL_MASK);
					
					count_Y = 0xff;
				}
			}
			//rotation
			else
			{
				INT pY;
				LONG tmpx0;
				BYTE tmpx1;
				
				if (rd_Y == STOP)
				{
					bitClear(InboxBuff.CBrakeFlag, STOP_Y);
					count_Y = 0;
				}
				
				//calclate PI
				pY = ((*(CHAR *)&(OutboxBuff.Y_trs)) - pwm_Y);
				iY += pY;
				tmpx0 = (OutboxBuff.Kp_Y * (LONG)pY + OutboxBuff.Ki_Y * iY);
				if (tmpx0 < 0)
				{
					pwm_Y += (~((~tmpx0) >> OutboxBuff.bshift_Y));
				}
				else
				{
					pwm_Y += (tmpx0 >> OutboxBuff.bshift_Y);
				}
				
				//CCW
				if (pwm_Y < 0)
				{
					if (bitCheck(~rd_Y, CCW))
					{
						PRS32_Y_WriteSeed(0);
						
						//YAH off
						YAH_Data_ADDR = bitClear(YAH_DataShadow, YAH_MASK);
						//YBL & prs off
						YBL_Data_ADDR = bitClear(YBL_DataShadow, YBL_MASK);
						bitClear(YBL_GlobalSelect_ADDR, YBL_MASK);
						//YBH on
						YBH_Data_ADDR = bitSet(YBH_DataShadow, YBH_MASK);
						//YAL prs on
						bitSet(YAL_GlobalSelect_ADDR, YAL_MASK);
						
						rd_Y = CCW;
					}
					
					if (pwm_Y <= -128)
					{
						InboxBuff.Y_crs = 0x80;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.Y_crs)) = pwm_Y;
						tmpx1 = (((~InboxBuff.Y_crs) << 1) + 1);
					}
				}
				//CW
				else
				{
					if (bitCheck(~rd_Y, CW))
					{
						PRS32_Y_WriteSeed(0);
						
						//YBH off
						YBH_Data_ADDR = bitClear(YBH_DataShadow, YBH_MASK);
						//YAL & prs off
						YAL_Data_ADDR = bitClear(YAL_DataShadow, YAL_MASK);
						bitClear(YAL_GlobalSelect_ADDR, YAL_MASK);
						//YAH on
						YAH_Data_ADDR = bitSet(YAH_DataShadow, YAH_MASK);
						//YBL prs on
						bitSet(YBL_GlobalSelect_ADDR, YBL_MASK);
						
						rd_Y = CW;
					}
					
					if (pwm_Y >= 127)
					{
						InboxBuff.Y_crs = 0x7f;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.Y_crs)) = pwm_Y;
						tmpx1 = ((InboxBuff.Y_crs << 1) + 1);
					}
				}
				
				prsSet(prs_Y, tmpx1);
				bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
			}
			
			sw_Y = FALSE;
		}
		//end Y
		
		//calclate Z motor
		if (sw_Z)
		{
			static BYTE count_Z;
			static BYTE rd_Z;
			static INT pwm_Z;
			static LONG iZ;
			
			//stop & brake 
			if (bitCheck(OutboxBuff.TBrakeFlag, STOP_Z))
			{
				//brake
				if (count_Z < (STOPCOUNT_Z - STOPINC_Z))
				{
					//brake start
					if (rd_Z)
					{
						PRS32_Z_WriteSeed(0);
						
						//ZAH off
						ZAH_Data_ADDR = bitClear(ZAH_DataShadow, ZAH_MASK);
						//ZBH off
						ZBH_Data_ADDR = bitClear(ZBH_DataShadow, ZBH_MASK);
						//ZAL prs on
						bitSet(ZAL_GlobalSelect_ADDR, ZAL_MASK);
						//ZBL prs on
						bitSet(ZBL_GlobalSelect_ADDR, ZBL_MASK);
						
						bitSet(InboxBuff.CBrakeFlag, STOP_Z);
						bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
						InboxBuff.Z_crs = 0;
						pwm_Z = 0;
						iZ = 0;
						count_Z = 0;
						rd_Z = STOP;
					}
					//set prs
					prsSet(prs_Z, count_Z);
					PRS32_Z_WriteSeed(prs_Z);
					count_Z += STOPINC_Z;
				}
				//lock
				else if (count_Z != 0xff)
				{
					//ZAL on & prs off
					ZAL_Data_ADDR = bitSet(ZAL_DataShadow, ZAL_MASK);
					bitClear(ZAL_GlobalSelect_ADDR, ZAL_MASK);
					//ZBL on & prs off
					ZBL_Data_ADDR = bitSet(ZBL_DataShadow, ZBL_MASK);
					bitClear(ZBL_GlobalSelect_ADDR, ZBL_MASK);
					
					count_Z = 0xff;
				}
			}
			//rotation
			else
			{
				INT pZ;
				LONG tmpx0;
				BYTE tmpx1;
				
				if (rd_Z == STOP)
				{
					bitClear(InboxBuff.CBrakeFlag, STOP_Z);
					count_Z = 0;
				}
				
				//calclate PI
				pZ = ((*(CHAR *)&(OutboxBuff.Z_trs)) - pwm_Z);
				iZ += pZ;
				tmpx0 = (OutboxBuff.Kp_Z * (LONG)pZ + OutboxBuff.Ki_Z * iZ);
				if (tmpx0 < 0)
				{
					pwm_Z += (~((~tmpx0) >> OutboxBuff.bshift_Z));
				}
				else
				{
					pwm_Z += (tmpx0 >> OutboxBuff.bshift_Z);
				}
				
				//CCW
				if (pwm_Z < 0)
				{
					if (bitCheck(~rd_Z, CCW))
					{
						PRS32_Z_WriteSeed(0);
						
						//ZAH off
						ZAH_Data_ADDR = bitClear(ZAH_DataShadow, ZAH_MASK);
						//ZBL & prs off
						ZBL_Data_ADDR = bitClear(ZBL_DataShadow, ZBL_MASK);
						bitClear(ZBL_GlobalSelect_ADDR, ZBL_MASK);
						//ZBH on
						ZBH_Data_ADDR = bitSet(ZBH_DataShadow, ZBH_MASK);
						//ZAL prs on
						bitSet(ZAL_GlobalSelect_ADDR, ZAL_MASK);
						
						rd_Z = CCW;
					}
					
					if (pwm_Z <= -128)
					{
						InboxBuff.Z_crs = 0x80;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.Z_crs)) = pwm_Z;
						tmpx1 = (((~InboxBuff.Z_crs) << 1) + 1);
					}
				}
				//CW
				else
				{
					if (bitCheck(~rd_Z, CW))
					{
						PRS32_Z_WriteSeed(0);
						
						//ZBH off
						ZBH_Data_ADDR = bitClear(ZBH_DataShadow, ZBH_MASK);
						//ZAL & prs off
						ZAL_Data_ADDR = bitClear(ZAL_DataShadow, ZAL_MASK);
						bitClear(ZAL_GlobalSelect_ADDR, ZAL_MASK);
						//ZAH on
						ZAH_Data_ADDR = bitSet(ZAH_DataShadow, ZAH_MASK);
						//ZBL prs on
						bitSet(ZBL_GlobalSelect_ADDR, ZBL_MASK);
						
						rd_Z = CW;
					}
					
					if (pwm_Z >= 127)
					{
						InboxBuff.Z_crs = 0x7f;
						tmpx1 = 255;
					}
					else
					{
						(*(CHAR *)&(InboxBuff.Z_crs)) = pwm_Z;
						tmpx1 = ((InboxBuff.Z_crs << 1) + 1);
					}
				}
				
				prsSet(prs_Z, tmpx1);
				bitSet(InboxBuff.InboxFlag, I2CIO_UPDATE);
			}
			
			sw_Z = FALSE;
		}
		//end Z
		
		//LCD print
		if ((!sw_X) && (!sw_Y) && (!sw_Z))
		{
			LCD_1_Position(0, 0);
			cprintf("B%1X M:%02X %02X %02X E%02X",
				OutboxBuff.TBrakeFlag,
				OutboxBuff.X_trs,
				OutboxBuff.Y_trs,
				OutboxBuff.Z_trs,
				ec);
			LCD_1_Position(1, 0);
			cprintf("B%1X M:%02X %02X %02X C%02X",
				InboxBuff.CBrakeFlag,
				InboxBuff.X_crs,
				InboxBuff.Y_crs,
				InboxBuff.Z_crs,
				ct);
		}
	}
	
}

//update motors prs
#pragma interrupt_handler _Timer8_1_ISR
#pragma nomac
void _Timer8_1_ISR(void)
{
	static BYTE sw;
	static BYTE i2ccount;
	
	//update X motor prs
	if (sw == 0)
	{
		if (sw_X)
		{
			MBM_1_SetBusyFlag();
			ec++;
		}
		else
		{
			MBM_1_ClearBusyFlag();
		}
		PRS32_X_WriteSeed(prs_X);
		sw_X = TRUE;
		sw = 1;
	}
	
	//update Y motor prs
	else if (sw == 1)
	{
		if (sw_Y)
		{
			MBM_1_SetBusyFlag();
			ec++;
		}
		else
		{
			MBM_1_ClearBusyFlag();
		}
		PRS32_Y_WriteSeed(prs_Y);
		sw_Y = TRUE;
		sw = 2;
	}
	
	//update Z motor prs
	else
	{
		if (sw_Z)
		{
			MBM_1_SetBusyFlag();
			ec++;
		}
		else
		{
			MBM_1_ClearBusyFlag();
		}
		PRS32_Z_WriteSeed(prs_Z);
		sw_Z = TRUE;
		sw = 0;
	}
	
	if (i2cchekc)
	{
		i2ccount = 0;
		i2cchekc = FALSE;
	}
	else
	{
		//1 count = 2.73 ms
		if (i2ccount > 35)
		{
			//stop
			bitSet(OutboxBuff.TBrakeFlag, (STOP_X | STOP_Y | STOP_Z));
		}
		else
		{
			i2ccount++;
		}
	}	
	
	ct++;
}
#pragma usemac

//putchar for LCD cprintf
int putchar(char c)
{
	char str[2] = {0};
	str[0] = c;
	LCD_1_PrString(str);
	return c;
}
