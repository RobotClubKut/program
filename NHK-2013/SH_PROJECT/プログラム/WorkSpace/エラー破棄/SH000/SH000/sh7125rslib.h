
//CPU:SH2-7125F, ��=12.5MHz, sizeof(int)=32
//COM:BaudRate(default)=38400[bps], StartBit=1, StopBit=1, No-parity

#ifndef SHRSLIB_H
#define SHRSLIB_H

#ifndef set_imask
#include <machine.h>
#endif

// �ʐM���x
// N(BRR) = P��/(32*BaudRate)-1
// 80 =>   9645.1[bps] (  9600�ɑ΂�+0.47%)
// 40 =>  19054.9[bps] ( 19200�ɑ΂�-0.76%)
// 24 =>  31250.0[bps] ( 31250�ɑ΂� 0.00%)
// 19 =>  39062.5[bps] ( 38400�ɑ΂�+1.73%)
// 13 =>  55803.6[bps] ( 57600�ɑ΂�-3.12%)
//  6 => 111607.1[bps] (115200�ɑ΂�-3.12%)
#ifndef SHRS_BRR0
	#define SHRS_BRR0 19
#endif
#ifndef SHRS_BRR1
	#define SHRS_BRR1 19
#endif
#ifndef SHRS_BRR2
	#define SHRS_BRR2 19
#endif

#define SHRS_COMNUM 3

#ifndef SHRS_RECVBUFFERSIZE0
	#define SHRS_RECVBUFFERSIZE0 32
#endif
#ifndef SHRS_SENDBUFFERSIZE0
	#define SHRS_SENDBUFFERSIZE0 32
#endif
#ifndef SHRS_RECVBUFFERSIZE1
	#define SHRS_RECVBUFFERSIZE1 32
#endif
#ifndef SHRS_SENDBUFFERSIZE1
	#define SHRS_SENDBUFFERSIZE1 32
#endif
#ifndef SHRS_RECVBUFFERSIZE2
	#define SHRS_RECVBUFFERSIZE2 32
#endif
#ifndef SHRS_SENDBUFFERSIZE2
	#define SHRS_SENDBUFFERSIZE2 32
#endif

// --- ��M�o�b�t�@ ---
unsigned char SHRS_rbuffer0[SHRS_RECVBUFFERSIZE0];
unsigned char SHRS_rbuffer1[SHRS_RECVBUFFERSIZE1];
unsigned char SHRS_rbuffer2[SHRS_RECVBUFFERSIZE2];
volatile unsigned char *SHRS_rbuffer[SHRS_COMNUM]={SHRS_rbuffer0,SHRS_rbuffer1,SHRS_rbuffer2};
const int SHRS_rbuffersize[SHRS_COMNUM]={SHRS_RECVBUFFERSIZE0,SHRS_RECVBUFFERSIZE1,SHRS_RECVBUFFERSIZE2};
// SHRS_recv_wptrn �͎��ɏ������ރf�[�^�ʒu���w��
volatile int SHRS_recv_wptr[SHRS_COMNUM];
// SHRS_recv_rptrn==-1�̂Ƃ��̓f�[�^�Ȃ��C����ȊO�͎��ɓǂނׂ��f�[�^�ʒu���w��
volatile int SHRS_recv_rptr[SHRS_COMNUM];

// --- ���M�o�b�t�@ ---
unsigned char SHRS_sbuffer0[SHRS_SENDBUFFERSIZE0];
unsigned char SHRS_sbuffer1[SHRS_SENDBUFFERSIZE1];
unsigned char SHRS_sbuffer2[SHRS_SENDBUFFERSIZE2];
volatile unsigned char *SHRS_sbuffer[SHRS_COMNUM]={SHRS_sbuffer0,SHRS_sbuffer1,SHRS_sbuffer2};
const int SHRS_sbuffersize[SHRS_COMNUM]={SHRS_SENDBUFFERSIZE0,SHRS_SENDBUFFERSIZE1,SHRS_SENDBUFFERSIZE2};
// SHRS_send_wptrn �͎��ɏ������ރf�[�^�ʒu���w��
volatile int SHRS_send_wptr[SHRS_COMNUM];
// SHRS_send_rptrn==-1�̂Ƃ��̓f�[�^�Ȃ��C����ȊO�͎��ɓǂނׂ��f�[�^�ʒu���w��
volatile int SHRS_send_rptr[SHRS_COMNUM];

char SHRS_openflag[SHRS_COMNUM]={0,0,0};

//��M����(ERI0,RXI0)�ŌĂяo�����
void SHRS_recv_ir0(void)
{
	unsigned char c;

	//�G���[(ORER,FER,PER)������΃N���A
	do{
		if(SCI0.SCSSR.BYTE & 0x38){
			SCI0.SCSSR.BYTE &= ~0x38;
		}
	}while(!(SCI0.SCSSR.BIT.RDRF));

	c=SCI0.SCRDR;	//�P�o�C�g�ǂݍ���
	SCI0.SCSSR.BIT.RDRF=0;

	//buffer full
	if (SHRS_recv_wptr[0] == SHRS_recv_rptr[0]) return;
	SHRS_rbuffer[0][SHRS_recv_wptr[0]]=c;
	if (SHRS_recv_rptr[0]<0) SHRS_recv_rptr[0]=SHRS_recv_wptr[0];
	if (++SHRS_recv_wptr[0] == SHRS_rbuffersize[0]) SHRS_recv_wptr[0]=0;
}

//��M����(ERI1,RXI1)�ŌĂяo�����
void SHRS_recv_ir1(void)
{
	unsigned char c;

	//�G���[(ORER,FER,PER)������΃N���A
	do{
		if(SCI1.SCSSR.BYTE & 0x38){
			SCI1.SCSSR.BYTE &= ~0x38;
		}
	}while(!(SCI1.SCSSR.BIT.RDRF));

	c=SCI1.SCRDR;	//�P�o�C�g�ǂݍ���
	SCI1.SCSSR.BIT.RDRF=0;

	//buffer full
	if (SHRS_recv_wptr[1] == SHRS_recv_rptr[1]) return;
	SHRS_rbuffer[1][SHRS_recv_wptr[1]]=c;
	if (SHRS_recv_rptr[1]<0) SHRS_recv_rptr[1]=SHRS_recv_wptr[1];
	if (++SHRS_recv_wptr[1] == SHRS_rbuffersize[1]) SHRS_recv_wptr[1]=0;
}

//��M����(ERI2,RXI2)�ŌĂяo�����
void SHRS_recv_ir2(void)
{
	unsigned char c;

	//�G���[(ORER,FER,PER)������΃N���A
	do{
		if(SCI2.SCSSR.BYTE & 0x38){
			SCI2.SCSSR.BYTE &= ~0x38;
		}
	}while(!(SCI2.SCSSR.BIT.RDRF));

	c=SCI2.SCRDR;	//�P�o�C�g�ǂݍ���
	SCI2.SCSSR.BIT.RDRF=0;

	//buffer full
	if (SHRS_recv_wptr[2] == SHRS_recv_rptr[2]) return;
	SHRS_rbuffer[2][SHRS_recv_wptr[2]]=c;
	if (SHRS_recv_rptr[2]<0) SHRS_recv_rptr[2]=SHRS_recv_wptr[2];
	if (++SHRS_recv_wptr[2] == SHRS_rbuffersize[2]) SHRS_recv_wptr[2]=0;
}

//���M����(TXI0,TEI0)�ŌĂяo�����
void SHRS_send_ir0(void)
{
	int rp;
		
	rp=SHRS_send_rptr[0];
	if(rp<0){
		SCI0.SCSCR.BIT.TIE=0;
		return;
	}

	while(!(SCI0.SCSSR.BIT.TDRE));
	SCI0.SCTDR=SHRS_sbuffer[0][rp++];
	SCI0.SCSSR.BIT.TDRE=0;

	if(rp==SHRS_sbuffersize[0]) rp=0;
	if(rp==SHRS_send_wptr[0]) rp=-1;
	SHRS_send_rptr[0]=rp;
}

//���M����(TXI1,TEI1)�ŌĂяo�����
void SHRS_send_ir1(void)
{
	int rp;
		
	rp=SHRS_send_rptr[1];
	if(rp<0){
		SCI1.SCSCR.BIT.TIE=0;
		return;
	}

	while(!(SCI1.SCSSR.BIT.TDRE));
	SCI1.SCTDR=SHRS_sbuffer[1][rp++];
	SCI1.SCSSR.BIT.TDRE=0;

	if(rp==SHRS_sbuffersize[1]) rp=0;
	if(rp==SHRS_send_wptr[1]) rp=-1;
	SHRS_send_rptr[1]=rp;
}

//���M����(TXI2,TEI2)�ŌĂяo�����
void SHRS_send_ir2(void)
{
	int rp;
		
	rp=SHRS_send_rptr[2];
	if(rp<0){
		SCI2.SCSCR.BIT.TIE=0;
		return;
	}

	while(!(SCI2.SCSSR.BIT.TDRE));
	SCI2.SCTDR=SHRS_sbuffer[2][rp++];
	SCI2.SCSSR.BIT.TDRE=0;

	if(rp==SHRS_sbuffersize[2]) rp=0;
	if(rp==SHRS_send_wptr[2]) rp=-1;
	SHRS_send_rptr[2]=rp;
}

// �|�[�g�̃I�[�v��
int SHRS_Open(int ncom)
{
	int i;
	
	if(SHRS_openflag[ncom]) return 1;
	switch(ncom){
		// ----- SCI0 -----
		case 0:
			INTC.IPRL.WORD &= ~0xF000;
			INTC.IPRL.WORD |=  0xF000;	// ���荞�ݗD�惌�x��(SCI0)=15
			STB.CR3.BIT._SCI0=0;	// SCI1�N���b�N�����J�n
			SCI0.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
			SCI0.SCSMR.BYTE=0x00;	// ASYNC 8 BIT, NON PARITY, 1 STOP BIT, CLOCK=P��(25MHz)
			SCI0.SCSDCR.BIT.DIR=0;	// DIR=0:LSB first
			SCI0.SCBRR = SHRS_BRR0;	// N = P��/(32*BaudRate)-1
			for(i=0;;i++)if(i==130) break;
		#ifdef SHRS_TXD0_PA11
			PFC.PACRL3.BYTE.H &= ~0xF0;
			PFC.PACRL3.BYTE.H |=  0x60;	// PA11���[�h=TXD0
		#else
		#ifdef SHRS_TXD0_PE2
			PFC.PECRL1.BYTE.H &= ~0x0F;
			PFC.PECRL1.BYTE.H |=  0x06;	// PE2���[�h=TXD0
		#else
			//default(TXD0_PA1)
			PFC.PACRL1.BYTE.L &= ~0xF0;
			PFC.PACRL1.BYTE.L |=  0x10;	// PA1���[�h=TXD0
		#endif
		#endif

		#ifdef SHRS_RXD0_PA10
			PFC.PACRL3.BYTE.H &= ~0x0F;
			PFC.PACRL3.BYTE.H |=  0x06;	// PA10���[�h=RXD0
		#else
		#ifdef SHRS_RXD0_PE1
			PFC.PECRL1.BYTE.L &= ~0xF0;
			PFC.PECRL1.BYTE.L |=  0x60;	// PE1���[�h=RXD0
		#else
			//default(RXD0_PA0)
			PFC.PACRL1.BYTE.L &= ~0x0F;
			PFC.PACRL1.BYTE.L |=  0x01;	// PA0���[�h=RXD0
		#endif
		#endif
			SCI0.SCSCR.BYTE=0x70;	// TIE=0,TE=1,TR=1,RIE=1
			break;
		// ----- SCI1 -----
		case 1:
			INTC.IPRL.WORD &= ~0x0F00;
			INTC.IPRL.WORD |=  0x0F00;	// ���荞�ݗD�惌�x��(SCI1)=15
			STB.CR3.BIT._SCI1=0;	// SCI1�N���b�N�����J�n
			SCI1.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
			SCI1.SCSMR.BYTE=0x00;	// ASYNC 8 BIT, NON PARITY, 1 STOP BIT, CLOCK=P��(25MHz)
			SCI1.SCSDCR.BIT.DIR=0;	// DIR=0:LSB first
			SCI1.SCBRR = SHRS_BRR1;	// N = P��/(32*BaudRate)-1
			for(i=0;;i++)if(i==130) break;
		#ifdef SHRS_TXD1_PA15
			PFC.PACRL4.BYTE.H &= ~0xF0;
			PFC.PACRL4.BYTE.H |=  0x60;	// PA15���[�h=TXD1
		#else
		#ifdef SHRS_TXD1_PE5
			PFC.PECRL2.BYTE.L &= ~0xF0;
			PFC.PECRL2.BYTE.L |=  0x60;	// PE5���[�h=TXD1
		#else
			//default(TXD1_PA4)
			PFC.PACRL2.BYTE.L &= ~0x0F;
			PFC.PACRL2.BYTE.L |=  0x01;	// PA4���[�h=TXD1
		#endif
		#endif

		#ifdef SHRS_RXD1_PA14
			PFC.PACRL4.BYTE.H &= ~0x0F;
			PFC.PACRL4.BYTE.H |=  0x06;	// PA14���[�h=RXD1
		#else
		#ifdef SHRS_RXD1_PE4
			PFC.PECRL2.BYTE.L &= ~0x0F;
			PFC.PECRL2.BYTE.L |=  0x06;	// PE4���[�h=RXD1
		#else
			//default(RXD1_PA3)
			PFC.PACRL1.BYTE.H &= ~0xF0;
			PFC.PACRL1.BYTE.H |=  0x10;	// PA3���[�h=RXD1
		#endif
		#endif
			SCI1.SCSCR.BYTE=0x70;	// TIE=0,TE=1,TR=1,RIE=1
			break;
		// ----- SCI2 -----
		case 2:
			INTC.IPRL.WORD &= ~0x00F0;
			INTC.IPRL.WORD |=  0x00F0;	// ���荞�ݗD�惌�x��(SCI2)=15
			STB.CR3.BIT._SCI2=0;	// SCI1�N���b�N�����J�n
			SCI2.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
			SCI2.SCSMR.BYTE=0x00;	// ASYNC 8 BIT, NON PARITY, 1 STOP BIT, CLOCK=P��(25MHz)
			SCI2.SCSDCR.BIT.DIR=0;	// DIR=0:LSB first
			SCI2.SCBRR = SHRS_BRR2;	// N = P��/(32*BaudRate)-1
			for(i=0;;i++)if(i==130) break;
			PFC.PACRL3.BYTE.L=0x66;	// PA8���[�h=RXD2, PA9���[�h=TXD2
			SCI2.SCSCR.BYTE=0x70;	// TIE=0,TE=1,TR=1,RIE=1
			break;
	}
	SHRS_recv_wptr[ncom]=0;
	SHRS_recv_rptr[ncom]=-1;
	SHRS_send_wptr[ncom]=0;
	SHRS_send_rptr[ncom]=-1;
	SHRS_openflag[ncom]=1;
	set_imask(0);	//���x���P�ȏ�̊��荞�݂�����
	return 0;
}

// �|�[�g�̃N���[�Y
int SHRS_Close(int ncom)
{
	if(!SHRS_openflag[ncom]) return 1;
	switch(ncom){
		case 0:
			SCI0.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
		    STB.CR3.BIT._SCI0=1;	// SCI0�N���b�N������~
			break;
		case 1:
			SCI1.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
		    STB.CR3.BIT._SCI1=1;	// SCI1�N���b�N������~
			break;
		case 2:
			SCI2.SCSCR.BYTE=0x00;	// clear RIE,TIE,TEIE,MPIE,TE,RE
		    STB.CR3.BIT._SCI2=1;	// SCI2�N���b�N������~
			break;
	}
	SHRS_openflag[ncom]=0;
	return 0;
}

// �f�[�^�̎�M
int SHRS_Recv(int ncom, char *buf, int n)
{
	int i,rp;
	
	if(!SHRS_openflag[ncom]) return 0;

	if(n>SHRS_rbuffersize[ncom]) n=SHRS_rbuffersize[ncom];
	
	for(i=0;i<n;i++){
		rp=SHRS_recv_rptr[ncom];
		if (rp<0) break;

		*buf++ = SHRS_rbuffer[ncom][rp++];

		if(rp==SHRS_rbuffersize[ncom]) rp=0;
		if(rp==SHRS_recv_wptr[ncom]) rp=-1;
		SHRS_recv_rptr[ncom]=rp;
	}
	return i;
}

// ��M�o�b�t�@�̃`�F�b�N
// (�o�b�t�@���Ɋi�[�ς݂̃f�[�^�����o�C�g�P�ʂŕԂ�)
int SHRS_CheckRecv(int ncom)
{
	int rp,wp;
	
	if(!SHRS_openflag[ncom]) return 0;

	rp=SHRS_recv_rptr[ncom];
	wp=SHRS_recv_wptr[ncom];

	if (rp<0) return 0;

	if (wp>rp){
		return wp-rp;
	}else{
		return SHRS_rbuffersize[ncom]-(rp-wp);
	}
}

// ���M�o�b�t�@�̃`�F�b�N
// (�o�b�t�@�̋󂫂��o�C�g�P�ʂŕԂ�)
int SHRS_CheckSend(int ncom)
{
	int rp,wp;
	
	if(!SHRS_openflag[ncom]) return 0;

	wp=SHRS_send_wptr[ncom];
	rp=SHRS_send_rptr[ncom];

	if (rp<0) return SHRS_sbuffersize[ncom];

	if (wp>rp){
		return SHRS_sbuffersize[ncom]-(wp-rp);
	}else{
		return (rp-wp);
	}
}

// ��M�o�b�t�@�̃N���A
int SHRS_ClearRecv(int ncom)
{
	if(!SHRS_openflag[ncom]) return 1;
	SHRS_recv_rptr[ncom]=-1;
	return 0;
}

// ���M�o�b�t�@�̃N���A
int SHRS_ClearSend(int ncom)
{
	if(!SHRS_openflag[ncom]) return 1;
	switch(ncom){
		case 0: SCI0.SCSCR.BIT.TIE=0; break;
		case 1: SCI1.SCSCR.BIT.TIE=0; break;
		case 2: SCI2.SCSCR.BIT.TIE=0; break;
	}
	SHRS_send_rptr[ncom]=-1;
	return 0;
}

// �P�����̎�M
int SHRS_Getc(int ncom)
{
	char c;
	if(!SHRS_openflag[ncom]) return -1;
	if (!SHRS_Recv(ncom,&c,1)) return -1;
	return c;
}

// ������(�Ōオ\n/\r/0�̂����ꂩ)�̎�M
int SHRS_Gets(int ncom, char *s)
{
	int n=0;
	if(!SHRS_openflag[ncom]) return n;

	for(;;){
		if (SHRS_Recv(ncom,s,1)==1) {
			if(*s=='\n' || *s=='\r' || *s==0){
				*s=0;
				n++;
				break;
			}else{
				s++;
				n++;
			}
		}
	}
	return n;
}

// �f�[�^�̑��M
// (�f�[�^�͑��M�o�b�t�@�֊i�[�����)
// ���M�����O�o�b�t�@�����̕s����C�� 2011.6.15
int SHRS_Send(int ncom, char *buf, int n)
{
	int i,wp;
	
	if(!SHRS_openflag[ncom]) return 0;
	
	for(i=0;i<n;i++){
		wp=SHRS_send_wptr[ncom];
		if (wp == SHRS_send_rptr[ncom]) return i;	//buffer full

		SHRS_sbuffer[ncom][wp]=*buf++;

		if ((wp+1) == SHRS_sbuffersize[ncom]) SHRS_send_wptr[ncom]=0;
		else SHRS_send_wptr[ncom]++;

		if (SHRS_send_rptr[ncom]<0) SHRS_send_rptr[ncom]=wp;

		switch(ncom){
			case 0:	SCI0.SCSCR.BIT.TIE=1; break;
			case 1:	SCI1.SCSCR.BIT.TIE=1; break;
			case 2:	SCI2.SCSCR.BIT.TIE=1; break;
		}
	}
	return n;
}

//�P�����̑��M
int SHRS_Putc(int ncom, char c)
{
;	if(!SHRS_openflag[ncom]) return 0;
	return SHRS_Send(ncom,&c,1);
}

//������̑��M�i�Ō��\n�����j
int SHRS_Puts(int ncom, char *s)
{
	int n=0;
	if(!SHRS_openflag[ncom]) return n;
	while(*s){
		SHRS_Putc(ncom,*s++);
		n++;
	}
	SHRS_Putc(ncom,'\n');
	n++;
	return n;
}

//������̑��M�i�Ō�ɉ������Ȃ��j
int SHRS_Sends(int ncom, char *s)
{
	int n=0;

	if(!SHRS_openflag[ncom]) return 0;
	while(*s){
		SHRS_Putc(ncom, *s++);
		n++;
	}
	return n;
}

//SHRS_Printf()�֐����g���Ǝ��s�t�@�C���̃T�C�Y���傫���Ȃ�D
#ifdef SHRS_USE_PRINTF
#include <stdio.h>
#include <stdarg.h>
#ifndef SHRS_PRINTF_BUFFERSIZE
	#define SHRS_PRINTF_BUFFERSIZE	256
#endif
int SHRS_Printf(int ncom, char *format, ...)
{
	va_list vl;
	char buf[SHRS_PRINTF_BUFFERSIZE];

	va_start(vl,format);
	vsprintf(buf,format,vl);

	return SHRS_Puts(ncom,buf);
}
#endif

#endif
