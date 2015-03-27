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

int timer_flag = 0; 
int	pulse_count = 0;
/////モータ駆動//////////////////
void Rail_Y_Motor(int16 pwm) // pwm -255 ~ 255
{
	if(pwm > 255)
	{
		pwm = 255;
	}
	if(pwm < -255)
	{
		pwm = -255;
	}
	if(pwm > 0)
	{	
		PWM_2_WriteCompare1((uint8)(pwm));
		PWM_2_WriteCompare2(0);
	}
	else if(pwm < 0)
	{
		PWM_2_WriteCompare1(0);
		PWM_2_WriteCompare2((uint8)(-pwm));
	}
}
void Rail_Y_Brake()
{
	PWM_2_WriteCompare1(255);
	PWM_2_WriteCompare2(255);
}
void Rail_Z_Motor(int16 pwm) // pwm -255 ~ 255
{
	if(pwm > 255)
	{
		pwm = 255;
	}
	if(pwm < -255)
	{
		pwm = -255;
	}
	if(pwm > 0)
	{	
		PWM_1_WriteCompare1(0);
		PWM_1_WriteCompare2((uint8)(pwm));
	}
	else if(pwm < 0)
	{
		PWM_1_WriteCompare1((uint8)(-pwm));
		PWM_1_WriteCompare2(0);
	}
}
void Rail_Z_Brake()
{
	PWM_1_WriteCompare1(255);
	PWM_1_WriteCompare2(255);
}


int main()
{
	
	int i = 0;
	char rx_data[40] = "yes\n";
	char buffer[40];
	uint8 count = 0;
	uint8 trans = 0;
	uint8 buffur_size = 0;
	int16 photo;
	uint8 print_mode = 0;
	int16 Black = 1000;
	int16 White = 3000;
	uint8 pwm_select = 0;
	
	uint8 motor_status = 0;
	uint8 motor_up_down_flag = 0;
	uint8 motor_front_back_flag = 0;



	// 初期化
	CyGlobalIntEnable; 
	PWM_1_Start();
	PWM_2_Start();
//	QuadDec_1_Start();
//	isr_1_StartEx(motor_isr);
	UART_1_Start();
	UART_1_EnableTxInt();
	UART_1_EnableRxInt();
	ADC_DelSig_1_Start();
	ADC_DelSig_1_StartConvert();
  
	PWM_1_WriteCompare1(0);
	PWM_1_WriteCompare2(0);
	
	for(;;)
	{
		// フォトリフレクタAD変換
		if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS))
        {
            photo = ADC_DelSig_1_GetResult16();
			trans = 1;
        }
		// Bluetooth送信
		if((UART_1_ReadTxStatus() & UART_1_TX_STS_FIFO_EMPTY)&&(trans == 1))
		{
			//sprintf(buffer,"photo = %6.4f[V]\n",photo*0.00122);
			//sens
			if(print_mode){
				if(photo < Black+600){
					sprintf(buffer,"photo = Black %6.4f[V]\n",photo*0.00122);
				}
				else if(photo > White-600){
					sprintf(buffer,"photo = White %6.4f[V]\n",photo*0.00122);
				}
				
				else
				{
					//sprintf(buffer,"photo = NULL  %6.4f[V]\n",photo*0.00122);
				}
			}
			//voltage
			else{
				sprintf(buffer,"photo = %6.4f[V]\n",photo*0.00122);
			}
			UART_1_PutString(buffer);
			//UART_1_PutString("test\n");
			trans = 0;
		}
		if(pwm_select == 2)
		{
			PWM_1_WriteCompare1(0);
			PWM_1_WriteCompare2(200);
		}
		else if(pwm_select == 1)
		{
			PWM_1_WriteCompare1(200);
			PWM_1_WriteCompare2(0);
		}
		else
		{
			PWM_1_WriteCompare1(0);
			PWM_1_WriteCompare2(0);
		}
		
		// Bluetooth 受信処理
		buffur_size = UART_1_GetRxBufferSize();
		if(buffur_size != 0)
		{
			for(count = 0;count < buffur_size;count++){
            	rx_data[count] = UART_1_GetByte() & 0xff;
				if((rx_data[count] == 'v')||(rx_data[count] == 'V'))
				{
					print_mode = 0;
				}
				else if((rx_data[count] == 's')||(rx_data[count] == 'S'))
				{
					print_mode = 1;
				}
				else if((rx_data[count] == 'b')||(rx_data[count] == 'B'))
				{
					Black = photo;
				}
				else if((rx_data[count] == 'w')||(rx_data[count] == 'W'))
				{
					White = photo;
				}
				else if((rx_data[count] == 'l')||(rx_data[count] == 'L'))
				{
					if(pwm_select == 0){
						pwm_select = 2;
					}
					else if(pwm_select == 1){
						PWM_1_WriteCompare1(0);
						PWM_1_WriteCompare2(0);
						CyDelay(250);
						pwm_select = 2;
					}
				}
				else if((rx_data[count] == 'r')||(rx_data[count] == 'R'))
				{
					if(pwm_select == 0){
						pwm_select = 1;
					}
					else if(pwm_select == 2){
						PWM_1_WriteCompare1(0);
						PWM_1_WriteCompare2(0);
						CyDelay(250);
						pwm_select = 1;
					}
				}
				else if((rx_data[count] == 'f')||(rx_data[count] == 'F'))
				{
					pwm_select = 0;
				}
				
			}
			rx_data[count] = '\0';
			UART_1_ClearRxBuffer();
			trans = 1;
        }
	}
}



