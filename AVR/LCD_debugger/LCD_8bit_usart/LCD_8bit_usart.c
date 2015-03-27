//cpu�N���b�N���g�� 20MHz
#define F_CPU 20000000

//usart �{�[���[�g
#define BOUD 9600


//�C���N���[�h
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

//�v���g�^�C�v�錾
uint8_t usart_receive (void);
void usart_init (uint16_t);


//�G���g���[�|�C���g
int main (void)
{
	uint8_t i;
	char buff, str[17] = "     ready";

	//LCD ������ �� 8bit���[�h, 2�s, 5�~8�h�b�g, �\��on, �J�[�\��on, �J�[�\���_��on, AC�f�N�������g,�@�J�[�\���I�[�g�V�t�goff
	lcd_init (MODE_8BIT | USE_2LINE | DOT_5X8, DISPLAY_ON | CURSOR_ON | BLINK_ON, AC_DEC | COS_OFF);

	//usart ������
	usart_init (BOUD);

	//usart ��������
	lcd_position (0 | LINE1);
	lcd_str ("usart recive");
	lcd_position (0 | LINE2);
	lcd_str (str);

	//�����[�v
	while(1)
	{
		//�J�[�\���̈ʒu�ݒ�
		lcd_position (0 | LINE2);

		//16��������
		for (i = 0; i < 16; i++)
		{
			//usart ��M
			if ('\n' == (buff = usart_receive ()))	//���s�̂Ƃ�
			{
				//�o�b�t�@�N���A
				while (str[i] != '\0')
					str[i++] = '\0';
				break;
			}

			//1�����\��
			lcd_ch (str[i] = buff);
		}

		//�\���N���A
		lcd_clear ();

		//�o�b�t�@�\��
		lcd_str (str);
	}
	return 0;
}


/***************�֐�***************************************************************************************************************************/

//usart������
void usart_init (uint16_t boud)
{
	boud = (uint16_t)(((F_CPU >> 4) / boud) - 1);
	UBRRH = (uint8_t)(boud >> 8);
	UBRRL = (uint8_t)boud;
	UCSRB = _BV (TXEN) | _BV (RXEN);
	UCSRC = _BV (UCSZ1) | _BV (UCSZ0);
	return;
}

//usart��M
uint8_t usart_receive (void)
{
	// ��M����܂őҋ@
	loop_until_bit_is_set (UCSRA, RXC);
	
	// ��M
	return UDR;
}
