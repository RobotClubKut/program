//cpu�N���b�N 20MHz
#define F_CPU 20000000

//usart �{�[���[�g
#define BOUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


//�v���g�^�C�v�錾
char usart_receive (void);
void usart_init (uint16_t);

//�G���g���[�|�C���g
int main (void)
{
	uint8_t i;
	char buff = 0, str[17] = "     ready";

	//LCD 8bit ������ �� 8bit���[�h, 2�s, 5�~8�h�b�g, �\��on, �J�[�\��off, �J�[�\���_��off, AC�f�N�������g, �J�[�\���I�[�g�V�t�goff
	lcd_init (MODE_8BIT | USE_2LINE | DOT_5X8, DISPLAY_ON | CURSOR_OFF | BLINK_OFF, AC_DEC | COS_OFF);

	//usart ������
	usart_init (BOUD);

	//usart��������
	lcd_position (0 | LINE1);
	lcd_str ("usart receive");
	lcd_position (0 | LINE2);
	lcd_str (str);

	//�����[�v
	while(1)
	{
		//�J�[�\����2�s�ڂɐݒ�
		lcd_position (0 | LINE2);

		//16��������
		for (i = 0; i < 16; i++)
		{
			//���s�̂Ƃ�
			if ('\n' == (buff = usart_receive ()))
			{
				//�o�b�t�@�N���A
				while (str[i] != '\0')
					str[i++] = '\0';
				break;
			}

			//�����\��
			lcd_ch (str[i] = buff);
		}

		//�f�B�X�v���C�N���A
		lcd_clear ();

		//�o�b�t�@�̏�������
		lcd_str (str);
	}
	return 0;
}


//usart��M
char usart_receive (void)
{
	// ��M����܂őҋ@
	loop_until_bit_is_set (UCSRA, RXC);
	
	// ��M
	return UDR;
}

//usart ������
void usart_init (uint16_t boud)
{
	boud = (((F_CPU >> 4) / boud) - 1);
	UBRRH = (uint8_t)(boud >> 8);
	UBRRL = (uint8_t)boud;
	UCSRB = _BV (TXEN) | _BV (RXEN);
	UCSRC = _BV (UCSZ1) | _BV (UCSZ0);
	return;
}
