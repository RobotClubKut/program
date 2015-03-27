.include "m644Pdef.inc"

.equ	Reverse		=1		;  "1"�ŕ��_���ʐM�A"0"�Ő��_�����M
.equ	Tx		=4		;  ���M�|�[�g�iPORTB�j
.equ	LED1		=1		;  PORTB,1

;���荞�ݎ��g�pSTACK
.def	STACK		=R15

;�ėp
.def	TEMP		=R16
.def	DATA		=R17
.def	DATA_H		=R16
.def	DATA_L		=R17

;�E�G�C�g�p
.def	CT_0		=R18
.def	CT_1		=R19
.def	CT_2		=R20

;�f�[�^
.def	Tx_DATA		=R17		;���M�f�[�^


.cseg				;�v���O�����������[�֐ؑցB���Ƀf�[�^������.DSEG�AEEPROM��.ESEG ������
.org	$0000			;�������݃X�^�[�g�Ԓn

	JMP	RESET		; 1:���Z�b�g
	JMP	RETURN		; 2:�O�����荞�ݗv��0
	JMP	RETURN		; 3:�O�����荞�ݗv��1
	JMP	RETURN		; 4:�s���ω������ݗv��0(PCINT  0�` 7 PIN)
	JMP	RETURN		; 5:�s���ω������ݗv��1(PCINT  8�`14 PIN)
	JMP	RETURN		; 6:�s���ω������ݗv��2(PCINT 16�`23 PIN)
	JMP	RETURN		; 7:�����ޯ�ތv������
	JMP	RETURN		; 8:���/����2 ��rA��v
	JMP	RETURN		; 9:���/����2 ��rB��v
	JMP	RETURN		;10:���/����2 ���ް�۰
	JMP	RETURN		;11:���/����1 �ߊl(������)����
	JMP	RETURN		;12:���/����1 ��rA��v(�����ԃ^�C�}�[�Ɏg�p)
	JMP	RETURN		;13:���/����1 ��rB��v
	JMP	RETURN		;14:���/����1 ���ް�۰
	JMP	RETURN		;15:���/����0 ��rA��v
	JMP	RETURN		;16:���/����0 ��rB��v
	JMP	RETURN		;17:T0�I�[�o�[�t���[
	JMP	RETURN		;18:SPI �]������
	JMP	RETURN		;19:USART ��M����
	JMP	RETURN		;20:USART ���M�ޯ̧�� 
	JMP	RETURN		;21:USART ���M����
	JMP	RETURN		;22:A/D�ϊ�����
	JMP	RETURN		;23:EEPROM �����
	JMP	RETURN		;24:��۸ޔ�r��o�͑J��
	JMP	RETURN		;25:2���ر� ����̪����ԕω�
	JMP	RETURN		;26:SPM���ߑ����

RESET:	;�X�^�b�N�|�C���^�̏�����
	LDI	R16,HIGH(RAMEND)	;�X�^�b�N�|�C���^���������BSRAM�������A�܂���256�޲Ĉȉ��̏ꍇ�͂��̍s���폜�B
	OUT	SPH,R16			;SRAM�������A�܂���256�޲Ĉȉ��̏ꍇ�͂��̍s���폜�B(ATmega48��)
	LDI	R16,LOW(RAMEND)		;SRAM�������ꍇ�͂��̍s���폜�B
	OUT	SPL,R16			;SRAM�������ꍇ�͂��̍s���폜�B
	;�|�[�g�a�̏�����
	LDI	TEMP,0b00000010		;�|�[�g�̏�Ԃ��`�B�|�[�g���͎��A0�Ńv���_�E��,1�Ńv���A�b�v�B
	OUT	PORTB,TEMP
	LDI	TEMP,0b00010010		;�|�[�g�̓��o�͐ݒ�B0�œ��́A1�ŏo�́B
	OUT	DDRB,TEMP
	;�|�[�g�b�̏�����
	LDI	TEMP,0b11111111		;�|�[�g�̏�Ԃ��`�B�|�[�g���͎��A0�Ńv���_�E��,1�Ńv���A�b�v�B
	OUT	PORTC,TEMP		;�ԊO��LED�̃|�[�g��2SA1317�o�R�Ȃ̂�0�ŐԊO��LED�_���A1�ŏ���
	LDI	TEMP,0b00000000		;�|�[�g�̓��o�͐ݒ�B0�œ��́A1�ŏo�́B
	OUT	DDRC,TEMP
	;�|�[�g�c�̏�����
	LDI	TEMP,0b11111111		;�|�[�g�̏�Ԃ��`�B�|�[�g���͎��A0�Ńv���_�E��,1�Ńv���A�b�v�B
	OUT	PORTD,TEMP
	LDI	TEMP,0b00000000		;�|�[�g�̓��o�͐ݒ�B0�œ��́A1�ŏo�́B
	OUT	DDRD,TEMP

;***************************************************************************
;���C�����[�`��
;***************************************************************************

	;RS232C���M�|�[�g������
	;�X�g�b�v�r�b�g"�P"�� 10bit �����M����B�i10��j
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	




;�e�X�g�\��
	LDI	Tx_DATA,0x21		;�����R�[�h"!"��]��
	RCALL	TxDATA_01		;"!"�𑗐M
	LDI	Tx_DATA,0x20		;�����R�[�h" "��]��
	RCALL	TxDATA_01		;" "(�X�y�[�X)�𑗐M

MAIN:

RCALL	WR_START_MESSAGE		;�X�^�[�g���b�Z�[�W�𑗐M����B

CALL	TM1000
	CBI	PORTB,LED1
CALL	TM1000
	SBI	PORTB,LED1
RJMP	MAIN
;����������������������������������������������������������������������������
;�T�u���[�`��
;����������������������������������������������������������������������������
;---------------------------------------------------------------------------
;����`�����݃��^�[��
;---------------------------------------------------------------------------
RETURN:
	IN	STACK,SREG
	OUT	SREG,STACK
	RETI				;����`�����݃��^�[��
;---------------------------------------------------------------------------
;���M
;---------------------------------------------------------------------------
TxDATA_01:

	CLC				;�L�����[�t���O�ɃX�^�[�g�r�b�g"�O"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	

	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	LSR	Tx_DATA			;�E�V�t�g����LSB�i���ʃr�b�g�j���L�����[�t���O�ɃZ�b�g����B
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	

	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
	;�E�G�C�g����ɃX�g�b�v�r�b�g�𑗐M
	SEC				;�L�����[�t���O�ɃX�g�b�v�r�b�g"�P"���Z�b�g
	RCALL	TxDATA_02		;�L�����[�t���O�̃f�[�^�𑗐M	
RET
;---------------------------------------------------------------------------
;�L�����[�t���O�𑗐M
;---------------------------------------------------------------------------
TxDATA_02:
	PUSH	TEMP
	PUSH	Tx_DATA

	CLR	Tx_DATA
	ROL	Tx_DATA			;�L�����[���܂߂�����]�����邱�Ƃɂ��A�L�����[��LSB�ɃZ�b�g�B

	LDI	TEMP,Reverse
	EOR	Tx_DATA,TEMP		;�r���I�_���a�����s���ALSB��K�v�ɉ����Ĕ��]������B

	BRNE	TxDATA_02_JP02
;	RJMP	TxDATA_02_JP02

TxDATA_02_JP01:
	NOP				;�^�C�~���O����
	CBI	PORTB,Tx
	RJMP	TxDATA_02_END
TxDATA_02_JP02:
	SBI	PORTB,Tx
	RJMP	TxDATA_02_END
TxDATA_02_END:
	POP	Tx_DATA
	POP	TEMP

RET
;---------------------------------------------------------------------------
;"AVR ATmega644P one-chip microcomputer." �\��
;---------------------------------------------------------------------------
WR_START_MESSAGE:

	LDI	ZH,high(WR_START_MESSAGE_DATA * 2) 	;�\���f�[�^�ۑ��A�h���X���w��B
	LDI	ZL,low (WR_START_MESSAGE_DATA * 2)
	RCALL	WRITE_01

	RET	
WR_START_MESSAGE_DATA:	.DB "AVR ATmega644P one-chip microcomputer.",13,10,0xFF	;�����݃f�[�^ �{ CRLF �{ 0xFF
;---------------------------------------------------------------------------
; �v���O�����������z�u�f�[�^�\��
;---------------------------------------------------------------------------
;�v���O�����������̓��[�h�P�ʂŃA�N�Z�X����B�P���[�h�Qbyte�Ȃ̂ŁAZ���W�Y�^�i�y�A�j���g�p���ăf�[�^��Ǎ��ށB
;ZL���W�X�^�̉��ʂP�r�b�g�Ń��[�h�̏�ʂW�r�b�g�Ɖ��ʂW�r�b�g�̂ǂ����ǂݍ��ނ̂����w�肷��B
;���������ăA�h���X��2�{�������̂�Z���W�X�^�ɏ������ނ��ƂŃf�[�^��Ǎ��ނ��Ƃ��ł���B
;LDI ZH,high(DATA + DATA)
;LDI ZL,low (DATA + DATA)
;LPM Rd,Z+
;DATA,Z+ �͊g���ԐڃA�h���b�V���O���߂Ȃ̂ŁA�T�|�[�g����Ȃ��@��̏ꍇ�́ALPM��R0�Ƀ��[�h���AZ���W�X�^���C���N�������g�����Ƃ��K�v�ɂȂ�B

WRITE_01:
	LPM	Tx_DATA,Z+		;Load Program Memory �� Tx_DATA + Z�|�C���^���C���N�������g
	CPI	Tx_DATA,$FF		;Tx_DATA = 0xFF�H 0xFF�͕�����̏I���������B
	BREQ	WRITE_01_END

	RCALL	TxDATA_01

	RJMP	WRITE_01
WRITE_01_END:
	RET

;---------------------------------------------------------------------------
;AVR�� 24bit �����ԃE�G�C�g/�^�C�}�[
;�E�G�C�g/�^�C�}�[ = n�~5+2 [�N���b�N] 
;�T�u���[�`���Ŏg�p�̏ꍇ�͏�L�v���X���L�N���b�N�]���Ɏ��Ԃ�������B
;RCALL,RET ���߂ŁA16�r�b�g�f�o�C�X��3+4�A22�r�b�g�f�o�C�X��4+5���v���X����B
; CALL,RET ���߂ŁA16�r�b�g�f�o�C�X��4+4�A22�r�b�g�f�o�C�X��5+5���v���X����B
;�ׂ��Ȓ����͏��Ȃ߂ɐݒ肵�ANOP�Œ�������B
;CT_2����ʁACT_0�����ʁB
;---------------------------------------------------------------------------
;CALL�ŌĂяo��������1�~���b
;20MHz�� CT_2=0x00,CT_0=0x0F,CT_0=0x9E + NOP X 0��
;16MHz�� CT_2=0x00,CT_0=0x0C,CT_0=0x7E + NOP X 0��
;10MHz�� CT_2=0x00,CT_0=0x07,CT_0=0xCE + NOP X 0��
; 8MHz�� CT_2=0x00,CT_0=0x06,CT_0=0x3E + NOP X 0��
; 1MHz�� CT_2=0x00,CT_0=0x00,CT_0=0xC6 + NOP X 0��
;---------------------------------------------------------------------------
TM1:
	LDI	CT_2,0x00
	LDI	CT_1,0x00
	LDI	CT_0,0xC6
TM1_LOOP:
	;HEX_2:HEX_1:HEX_0 ����P����
	SUBI	CT_0,1		;1�N���b�N
	SBCI	CT_1,0		;1�N���b�N
	SBCI	CT_2,0		;1�N���b�N
	BRNE	TM1_LOOP	;0�ɂȂ�܂Ń��[�v�B
				;���[�v��2�N���b�N�A�X���[��1�N���b�N�B
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���

	RET             
;---------------------------------------------------------------------------
;CALL�ŌĂяo��������10�~���b
;20MHz�� CT_2=0x00 , CT_0=0x9C , CT_0=0x3E + NOP X 0��
;16MHz�� CT_2=0x00 , CT_0=0x7C , CT_0=0xFE + NOP X 0��
;10MHz�� CT_2=0x00 , CT_0=0x4E , CT_0=0x1E + NOP X 0��
; 8MHz�� CT_2=0x00 , CT_0=0x3E , CT_0=0x7E + NOP X 0��
; 1MHz�� CT_2=0x00 , CT_0=0x07 , CT_0=0xCE + NOP X 0��
;---------------------------------------------------------------------------
TM10:
	LDI	CT_2,0x00
	LDI	CT_1,0x07
	LDI	CT_0,0xCE
TM10_LOOP:
	;HEX_2:HEX_1:HEX_0 ����P����
	SUBI	CT_0,1		;1�N���b�N
	SBCI	CT_1,0		;1�N���b�N
	SBCI	CT_2,0		;1�N���b�N
	BRNE	TM10_LOOP	;0�ɂȂ�܂Ń��[�v�B
				;���[�v��2�N���b�N�A�X���[��1�N���b�N�B
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���

	RET             
;---------------------------------------------------------------------------
;CALL�ŌĂяo��������100�~���b
;20MHz�� CT_2=0x06 , CT_0=0x1A , CT_0=0x7E + NOP X 0��
;16MHz�� CT_2=0x04 , CT_0=0xE1 , CT_0=0xFE + NOP X 0��
;10MHz�� CT_2=0x03 , CT_0=0x0D , CT_0=0x3E + NOP X 0��
; 8MHz�� CT_2=0x02 , CT_0=0x70 , CT_0=0xFE + NOP X 0��
; 1MHz�� CT_2=0x00 , CT_0=0x4E , CT_0=0x1E + NOP X 0��
;---------------------------------------------------------------------------
TM100:
	LDI	CT_2,0x00
	LDI	CT_1,0x4E
	LDI	CT_0,0x1E
TM100_LOOP:
	;HEX_2:HEX_1:HEX_0 ����P����
	SUBI	CT_0,1		;1�N���b�N
	SBCI	CT_1,0		;1�N���b�N
	SBCI	CT_2,0		;1�N���b�N
	BRNE	TM100_LOOP	;0�ɂȂ�܂Ń��[�v�B
				;���[�v��2�N���b�N�A�X���[��1�N���b�N�B
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���

	RET             
;---------------------------------------------------------------------------
;CALL�ŌĂяo��������500�~���b
;20MHz�� CT_2=0x1E , CT_0=0x84 , CT_0=0x7E + NOP X 0��
;16MHz�� CT_2=0x18 , CT_0=0x69 , CT_0=0xFE + NOP X 0��
;10MHz�� CT_2=0x0F , CT_0=0x42 , CT_0=0x3E + NOP X 0��
; 8MHz�� CT_2=0x0C , CT_0=0x34 , CT_0=0xFE + NOP X 0��
; 1MHz�� CT_2=0x01 , CT_0=0x86 , CT_0=0x9E + NOP X 0��
;---------------------------------------------------------------------------
TM500:
	LDI	CT_2,0x01
	LDI	CT_1,0x86
	LDI	CT_0,0x9E
TM500_LOOP:
	;HEX_2:HEX_1:HEX_0 ����P����
	SUBI	CT_0,1		;1�N���b�N
	SBCI	CT_1,0		;1�N���b�N
	SBCI	CT_2,0		;1�N���b�N
	BRNE	TM500_LOOP	;0�ɂȂ�܂Ń��[�v�B
				;���[�v��2�N���b�N�A�X���[��1�N���b�N�B
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���

	RET             
;---------------------------------------------------------------------------
;CALL�ŌĂяo��������1000�~���b
;20MHz�� CT_2=0x3D , CT_0=0x08 , CT_0=0xFE + NOP X 0��
;16MHz�� CT_2=0x30 , CT_0=0xD3 , CT_0=0xFE + NOP X 0��
;10MHz�� CT_2=0x1E , CT_0=0x84 , CT_0=0x7E + NOP X 0��
; 8MHz�� CT_2=0x18 , CT_0=0x69 , CT_0=0xFE + NOP X 0��
; 1MHz�� CT_2=0x03 , CT_0=0x0D , CT_0=0x3E + NOP X 0��
;---------------------------------------------------------------------------
TM1000:
	LDI	CT_2,0x03
	LDI	CT_1,0x0D
	LDI	CT_0,0x3E
TM1000_LOOP:
	;HEX_2:HEX_1:HEX_0 ����P����
	SUBI	CT_0,1		;1�N���b�N
	SBCI	CT_1,0		;1�N���b�N
	SBCI	CT_2,0		;1�N���b�N
	BRNE	TM1000_LOOP	;0�ɂȂ�܂Ń��[�v�B
				;���[�v��2�N���b�N�A�X���[��1�N���b�N�B
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���
;	NOP			;�ׂ��Ȓ���

	RET