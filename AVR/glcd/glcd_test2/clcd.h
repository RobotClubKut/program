#pragma once

//1�T�C�N��delay *50ns
#ifndef nop()
#define nop() __asm__ __volatile__ ("nop")
#endif

//Enable Pulse delay *460ns
#define clcd_epd() nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()


//PIN�ݒ�

//�f�[�^�s��
#define CLCD_DPORT PORTB
#define CLCD_DDDR DDRB
#define CLCD_DPIN PINB

//���W�X�^�s��
#define CLCD_RPORT PORTD
#define CLCD_RDDR DDRD
#define CLCD_RPIN PIND

//�f�[�^�s��
#define CLCD_DB0 0x01
#define CLCD_DB1 0x02
#define CLCD_DB2 0x04
#define CLCD_DB3 0x08
#define CLCD_DB4 0x10
#define CLCD_DB5 0x20
#define CLCD_DB6 0x40
#define CLCD_DB7 0x80
#define CLCD_ADB 0xff
#define CLCD_TRANS(data) (data)

//���W�X�^�s��
#define CLCD_RS 0x20
#define CLCD_RW 0x40
#define CLCD_E 0x80
#define CLCD_R 0x60
#define CLCD_ARB 0xe0


//�R�}���h�}�N��


//�f�B�X�v���C�N���A
#define CLCD_CLEAR 0x01
#define clcd_clear() clcd_cmd(CLCD_CLEAR)


//�J�[�\���z�[��
#define CLCD_HOME 0x02
#define clcd_home() clcd_cmd(CLCD_HOME)


//�G���g���[���[�h�Z�b�g
#define CLCD_ENTRY 0x04
#define clcd_entry(cmd) clcd_cmd(CLCD_ENTRY | (cmd))

//�A�h���X�J�E���^ �C���N�������g
#define AC_INC 0x02

//�A�h���X�J�E���^ �f�N�������g
#define AC_DEC 0x00

//�J�[�\���I�[�g�V�t�gon
#define COS_ON 0x01

//�J�[�\���I�[�g�V�t�goff
#define COS_OFF 0x00


//�X�N���[���ݒ�
#define CLCD_SCREEN 0x08
#define clcd_screen(cmd) clcd_cmd(CLCD_SCREEN | (cmd))

//�\��on
#define CDISPLAY_ON 0x04

//�\��off
#define CDISPLAY_OFF 0x00

//�J�[�\��on
#define CURSOR_ON 0x02

//�J�[�\��off
#define CURSOR_OFF 0x00

//�J�[�\���_��on
#define BLINK_ON 0x01

//�J�[�\���_��off
#define BLINK_OFF 0x00


//�V�t�g�ݒ�
#define CLCD_SHIFT 0x10
#define clcd_shift(cmd) clcd_cmd(CLCD_SHIFT | (cmd))

//�f�B�X�v���C�V�t�g
#define DISPLAY 0x80

//�J�[�\���V�t�g
#define CURSOR 0x00

//�E�V�t�g
#define RIGHT 0x04

//���V�t�g
#define LEFT 0x00


//�t�@���N�V�����Z�b�g
#define CLCD_FUNCTION 0x20
#define clcd_function(cmd) clcd_cmd(CLCD_FUNCTION | (cmd))

//8bit���[�h
#define MODE_8BIT 0x10

//4bit���[�h
#define MODE_4BIT 0x00

//2�s
#define USE_2LINE 0x08

//1�s
#define USE_1LINE 0x00

//5�~11�h�b�g
#define DOT_5X11 0x04

//5�~8�h�b�g
#define DOT_5X8 0x00


//�����o�^
#define CLCD_MAKE 0x40
#define clcd_make(add) clcd_cmd(CLCD_MAKE | (add))


//�J�[�\���ʒu�ݒ�
#define CLCD_POSITION 0x80
#define clcd_position(xp) clcd_cmd(CLCD_POSITION | ((xp) - 1))

//1�s��
#define LINE1 0x00

//2�s��
#define LINE2 0x40

//3�s��
#define LINE3 0x14

//4�s��
#define LINE4 0x54


//�֐�

uint8_t clcd_ch (char);
void clcd_nbf_ch (char);
void clcd_str (char *);
uint8_t clcd_cmd (uint8_t);
void clcd_nbf_cmd (uint8_t);
void clcd_make_ch (uint8_t, char *);
void clcd_make_8ch (char *);
void clcd_init (uint8_t, uint8_t, uint8_t);
uint8_t clcd_bf (void);

//�������M *8bit���[�h
uint8_t clcd_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (ch);
	CLCD_DPORT = CLCD_TRANS (ch);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//�������M (BF�Ȃ�) *8bit���[�h
void clcd_nbf_ch (char ch)
{
	CLCD_RPORT &= ~CLCD_RW;
	CLCD_RPORT |= CLCD_RS;
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (ch);
	CLCD_DPORT = CLCD_TRANS (ch);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (1);
	return;
}

//�����񑗐M
void clcd_str (char *str) 
{
	while (*str != '\0') 
		clcd_ch (*(str++));
	return;
}

//�R�}���h���M *8bit���[�h
uint8_t clcd_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (cmd);
	CLCD_DPORT = CLCD_TRANS (cmd);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	return clcd_bf ();
}

//�R�}���h���M (BF�Ȃ�) *8bit���[�h
void clcd_nbf_cmd (uint8_t cmd)
{
	CLCD_RPORT &= ~(CLCD_RW | CLCD_RS);
//	CLCD_DPORT &= ~CLCD_ADB;	
//	CLCD_DPORT |= CLCD_TRANS (cmd);
	CLCD_DPORT = CLCD_TRANS (cmd);
	CLCD_RPORT |= CLCD_E;
	clcd_epd ();
	CLCD_RPORT &= ~CLCD_E;
	_delay_ms (1);
	return;
}

//�����o�^
void clcd_make_ch (uint8_t add, char *data)
{
	uint8_t i;
	clcd_make ((add | 0x07) << 3);
	for (i = 0; i < 8; i++)
		clcd_ch (*(data++));
	return;
}

//8�����o�^
void clcd_make_8ch (char *data)
{
	uint8_t i;
	clcd_make (0);
	for (i =0 ; i < CLCD_MAKE; i++)
		clcd_ch (*(data++));
	return;
}


//Busy Frag �m�F
uint8_t clcd_bf ()
{
	uint8_t add;

	CLCD_DPORT &= ~CLCD_ADB;
	CLCD_DDDR &= ~CLCD_ADB;
	CLCD_RPORT &= ~CLCD_RS;
	CLCD_RPORT |= CLCD_RW;
	do
	{
		clcd_epd ();
		CLCD_RPORT |= CLCD_E;
		clcd_epd ();
		add = CLCD_DPIN;
		CLCD_RPORT &= ~CLCD_E;
	}
	while ((add & CLCD_DB7) > 0);

	CLCD_DDDR |= CLCD_ADB;
	CLCD_RPORT &= ~CLCD_RW;
	clcd_epd ();
	return add;
}

//LCD������
void clcd_init (uint8_t func, uint8_t scr, uint8_t ent)
{
	//�|�[�g�ݒ�
	CLCD_DDDR |= CLCD_ADB;
	CLCD_RDDR |= CLCD_ARB;
	CLCD_DPORT &= ~CLCD_ADB;
	CLCD_RPORT &= ~CLCD_ARB;

	_delay_ms (50);

	//����8bit���[�h�ݒ�
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_ms (5);
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_us (500);
	clcd_nbf_cmd (CLCD_FUNCTION | MODE_8BIT);
	_delay_us (100);

	//�t�@���N�V�����Z�b�g
	clcd_function (func);

	//�X�N���[���ݒ�
	clcd_screen (scr);

	//�f�B�X�v���C�N���A
	clcd_clear ();

	//�G���g���[���[�h�Z�b�g
	clcd_entry (ent);

	return;
}

