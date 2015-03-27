// http://www7.big.jp/~kerokero/avr/
// ��������@usada@kxb.biglobe.ne.jp

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>

#include "port.h"


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
BYTE Trans( BYTE tdat )
{
	BYTE rdat1,rdat2,rdat3;
	BYTE i=0x01;
	do{
		//// �o�̓f�[�^���Z�b�g
		if(!(tdat & i)){
			pod.TCOMM = 0;
		}
		else{
			pod.TCOMM = 1;
		}

		//// �N���b�N��������
		pod.TCLK = 0;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		rdat1 >>= 1;
		rdat2 >>= 1;
		rdat3 >>= 1;

		//// �N���b�N���グ��
		pod.TCLK = 1;
		//// �f�[�^���󂯎��
		if(pib.RDATA) rdat1 |= 0x80;
		asm("nop");
		if(pib.RDATA) rdat2 |= 0x80;
		asm("nop");
		if(pib.RDATA) rdat3 |= 0x80;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");

		//// �W��J��Ԃ�
		i<<=1;
	}while(i);

	///// �m�C�Y�΍�(������)
	BYTE tmp = rdat1 ^ rdat2;
	rdat1 &= ~tmp;
	rdat3 &=  tmp;
	rdat1 |=  rdat3;

	return rdat1;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
BYTE CheckACK( void )
{
	//// ���100��s(������̂�҂�)
	BYTE w = 150;
	do{
		if(pib.RACK) continue;
		if(pib.RACK) continue;
		if(pib.RACK) continue;
		break;
	}while(--w);

	if(!w)
		return 0;		// false

	//// ���100��s(�オ��̂�҂�)
	w = 150;
	do{
		if(!pib.RACK) continue;
		if(!pib.RACK) continue;
		if(!pib.RACK) continue;
		break;
	}while(--w);

	if(!w)
		return 0;		// false

	return 1;	// true
}


BYTE dwmbit[] PROGMEM ={
	0b00000000,
	0b00001000,
	0b00000001,
	0b00001001,
	0b00000010,
	0b00001010,
	0b00000011,
	0b00001011,
	0b00000100,
	0b00001100,
	0b00000101,
	0b00001101,
	0b00000110,
	0b00001110,
	0b00000111,
	0b00001111,
};

//////////////////////////////////////////////////////////////////
inline void rsout( BYTE data )
{
	#if defined (__AVR_ATtiny2313__)
		while(!(UCSRA & 1<<UDRE));
	#else
		while(!(USR & 1<<UDRE));
	#endif
	UDR = data;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
__attribute__((naked))
int main( void )
{
	PORTB = 0xFF;		// �v���A�b�v
	DDRB  = 0x00;		// ����

	PORTD = 0xFF;
	DDRD  = 0x00;

	pdd.TCOMM = 1;
	pdd.TSEL  = 1;
	pdd.TCLK  = 1;


	{	///// UART�ݒ�
		#if defined (__AVR_ATtiny2313__)
			UBRRL = 12;			// 8000000 / 16 / 38400 = (12+1);
			UBRRH = 0;
			UCSRC = (0<<USBS)|(3<<UCSZ0);
			UCSRB = 1<<TXEN; 
		#else
			UBRR = 12;			// 8000000 / 16 / 38400 = (12+1);
			UCR  = 1<<TXEN;
		#endif
		pdd.TxD = 1;
	}


	BYTE SEL=0;
	for(;;){

		///////////////// ���u�I��
		if(SEL == 0){
			pod.TSEL = 0;
		}
		else{
			pod.TSEL = 1;
		}

		//// �I����̂v�`�h�s
		for(int i=0;i<70;i++) asm("nop");

		BYTE tb = 0;
		do{
			BYTE keydata[8];


			BYTE res,cID;
			res = Trans(0x01);				// PAD�֗v��
			if(!CheckACK())	break;

			cID = Trans(0x42);				// GET ID (0x41)
			if(!CheckACK())	break;

			res = Trans(0x00);				// GET ID ('Z')
			if(res != 0x5A)	break;

			if(!CheckACK())	break;
			keydata[0] = ~Trans(0x00);		// GET KEYDATA(���])

			if(!CheckACK())	break;
			keydata[1] = ~Trans(0x00);		// GET KEYDATA(���])
			tb = 2;

			if((cID == 0x53)||(cID == 0x73)){
				if(!CheckACK())	break;
				keydata[2] = Trans(0x00);			// GET ANALOG STICK RIGHT X

				if(!CheckACK())	break;
				keydata[3] = Trans(0x00);			// GET ANALOG STICK RIGHT Y

				if(!CheckACK())	break;
				keydata[4] = Trans(0x00);			// GET ANALOG STICK LEFT X

				if(!CheckACK())	break;
				keydata[5] = Trans(0x00);			// GET ANALOG STICK LEFT Y
				tb = 6;
			}

			{	//// �ϊ� �� ���M ////
				BYTE *ss    = dwmbit;
				BYTE *tsdat = keydata;

				while(tb){
					tb--;
					BYTE tmp = *tsdat++;

					{
						BYTE tm = (tmp & 0xF0) | pgm_read_byte( ss++ );
						rsout(tm);
					}

					{
						BYTE tm = (tmp<<4)   | pgm_read_byte( ss++ );
						rsout(tm);
					}
				}
			}

		}while(0);


		{	//// �I��������
			pod.TSEL = 1;
		}


		SEL++;
		SEL &= 3;
	}


	return 0;
}
