/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <stdlib.h>

uint8 arm;
uint8 buffer[32];

void LIN_Slave_init()
{
	if(0u != l_sys_init()){
		
		CyHalt(0x00);
		
	}
	
	if(0u != l_ifc_init(LIN_1_IFC_HANDLE)){
	
		CyHalt(0x00);
		
	}
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
	PWM_1_Start();
	PWM_2_Start();
	LIN_Slave_init();
	UART_1_Start();
	UART_1_EnableTxInt();
	

	
    for(;;)
    {
    	 /* Place your application code here. */
		
//		if(l_flg_tst_arm() == 1)
//		{

			arm = l_u8_rd_arm();
			
//		}
		
		if((arm & (1 << 0))/* && (Pin_5_Read() == 0) && (Pin_6_Read() == 0)*/)
		{
			PWM_1_WriteCompare1(255);
			PWM_1_WriteCompare2(0);
			PWM_2_WriteCompare1(255);
			PWM_2_WriteCompare2(0);
		}
		

		if((arm & (1 << 1))/* && (Pin_7_Read() == 0) && (Pin_8_Read() == 0)*/)
		{
			PWM_1_WriteCompare1(0);
			PWM_1_WriteCompare2(255);
			PWM_2_WriteCompare1(0);
			PWM_2_WriteCompare2(255);
			
		}
		
		
		
		
		else
		{
			PWM_1_WriteCompare1(0);
			PWM_1_WriteCompare2(0);
			PWM_2_WriteCompare1(0);
			PWM_2_WriteCompare2(0);
		}
		
		if(UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_EMPTY)
		{
				
			sprintf(buffer,"%5d \n",(int)arm);
			UART_1_PutString(buffer);
				
		}
    }
}

/* [] END OF FILE */
