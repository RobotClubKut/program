/**************************************
	UART on ARM LPC1114			by nakach
**************************************/

/*-------------------------------------
�g����
	   �܂��O���[�o���ϐ��œK���ȃT�C�Y(���o�C�g�`���\�o�C�g���x)�̔z���2�錾��
   �܂��D
    char txb[10], rxb[10];
   ���ɒʐM�������ʐM���x�ƁC��ɐ錾�����ϐ��Ƃ��̃T�C�Y���e�������֐��̈�����
	 �^���܂��D
	 ���̗��38400[bps]�ŒʐM����Ƃ��Ă��܂��D

   uart_init (38400, txb, sizeof(txb), rxb, sizeof(rxb));

   �����SCI�̏������Ƒ���M�Ɏg�p���郊���O�o�b�t�@�̃|�C���^������������܂��D
	 �܂��A�z��̃T�C�Y���o�b�t�@�[�T�C�Y�ƂȂ�܂��B
	 �o�b�t�@�㏑�����Ȃ��悤�ҋ@����d�l�ɂȂ��Ă��܂��B
	 ��x�ɑ�ʂɑ��M����ꍇ�́A���ꂾ���o�b�t�@�[��傫�����Ă��������B
-------------------------------------*/
typedef struct {
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } tx;
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } rx;
} uartfifo;

volatile uartfifo UARTFIFO;


// SCI������
void uart_init (uint32_t baudrate, char *txbuf, short txl, char *rxbuf, short rxl)
{
  uint32_t DL,i;                                      	// �{�[���[�g������̕ϐ���`

  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
  // ��M�f�[�^�p�ϐ�������
  UARTFIFO.tx.buf = txbuf;
  UARTFIFO.rx.buf = rxbuf;
  UARTFIFO.tx.maxlen = txl;
  UARTFIFO.rx.maxlen = rxl;
  UARTFIFO.tx.wp = UARTFIFO.tx.rp = 0;
  UARTFIFO.rx.wp = UARTFIFO.rx.rp = 0;

  LPC_IOCON->PIO1_6 |= 0x01;                        	// RXD�@�\�ɐݒ�(FUNC=001)
  LPC_IOCON->PIO1_7 |= 0x01;                        	// TXD�@�\�ɐݒ�(FUNC=001)
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);             	//UART�փN���b�N����
  LPC_SYSCON->UARTCLKDIV = 0x01;                    	//�{�[���[�g�E�W�F�l���[�^�փN���b�N����
  DL = (SystemCoreClock * LPC_SYSCON->SYSAHBCLKDIV) 	// �{�[���[�g������̎Z�o
     / (16 * baudrate * LPC_SYSCON->UARTCLKDIV);
  LPC_UART->LCR |= (1<<7);                          	//�f�B�o�C�U�E���b�`�E�A�N�Z�X�L���iDLAB=1)
  LPC_UART->DLM = DL / 256;                         	//�{�[���[�g�̐ݒ�iU0DLM)
  LPC_UART->DLL = DL % 256;                         	// �{�[���[�g�̐ݒ�iU0DLL)
  LPC_UART->LCR &= ~(1<<7);                         	//�f�B�o�C�U�E���b�`�E�A�N�Z�X�����iDLAB=0)
  LPC_UART->LCR = 0x03;                             	//�f�[�^�̃t�H�[�}�b�g�ݒ�
  LPC_UART->FCR = 0x07;                             	//���o�̓o�b�t�@�̏�����
	LPC_UART->IER |= (0x01);														//��M���荞�݃I��
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(UART_IRQn,1);

	for(i=0;;i++)if(i==1300) break;

}

// ���M�o�b�t�@�`�F�b�N
short uart_tx_buff (void)
{
  short s;
  if ((s = (UARTFIFO.tx.rp - UARTFIFO.tx.wp)) <= 0)
    s += UARTFIFO.tx.maxlen;
  return s - 1;
}

// ��M�o�b�t�@�`�F�b�N
short uart_rx_buff (void)
{
  short s;
  if ((s = (UARTFIFO.rx.wp - UARTFIFO.rx.rp)) < 0)
		s += UARTFIFO.rx.maxlen;
  return s;
}

// ��M�o�b�t�@�N���A
void uart_rx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  UARTFIFO.rx.wp = UARTFIFO.rx.rp = 0;
	LPC_UART->IER |= (0x01);	
}

// ���M�o�b�t�@�N���A
void uart_tx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  UARTFIFO.tx.wp = UARTFIFO.tx.rp = 0;
}

// 1�o�C�g���M
void uart_putc (char c)
{
  volatile short t;

  t = (UARTFIFO.tx.wp + 1) % UARTFIFO.tx.maxlen;
  while (t == UARTFIFO.tx.rp) ;			//�㏑���ҋ@
	if(LPC_UART->IER&0x02){
		UARTFIFO.tx.buf[UARTFIFO.tx.wp] = c;
		UARTFIFO.tx.wp = t;
	}
	else{
		LPC_UART->THR=c;
	}
	LPC_UART->IER |= (0x02);	
}

// �e�L�X�g���M (null�^�[�~�l�[�V����)
void uart_puts (char *st)
{
  while (*st) {
    uart_putc (*st);
    if (*st++ == '\n') uart_putc ('\r');
  }
}

// �o�C�i���񑗐M (�T�C�Y�w��)
void uart_putsb (char *st, short l)
{
  short i;

  for (i = 0; i < l; i++) uart_putc (*st++);
}

// ��M�f�[�^�o�b�t�@���1�����ǂݏo��
char uart_getc(void)
{
  char c=0;

  while (UARTFIFO.rx.rp == UARTFIFO.rx.wp) ;
//	if(UARTFIFO.rx.rp != UARTFIFO.rx.wp)
	c = UARTFIFO.rx.buf[UARTFIFO.rx.rp++];
  UARTFIFO.rx.rp %= UARTFIFO.rx.maxlen;
  return c;
}

// �������M
short uart_gets (char *s, short len)
{
  short i = 0;
  char c;
  while (1) {
    c = uart_getc ();
    if ((c == '\n') || (c == '\r')) {
      s[i] = '\0'; if (i != 0) i++;
      uart_putc ('\n');
      break;
    } else if ((i > 0) && (c == '\b')) {
      uart_puts ("\b \b");
      i--;
    } else if ((i < len) && (i >= 0) && (c >= ' ') && (c <= '~')) {
      s[i++] = (char)c;
      uart_putc (c);
    } else uart_putc ('\a');
  }
  return i;
}
//	���s�t�@�C���T�C�Y����
#ifdef UART_USE_PRINTF
#include <stdio.h>
#include <stdarg.h>
void uart_printf(char *format, ...)
{
	va_list vl;
	char buf[UARTFIFO.tx.maxlen};

	va_start(vl,format);
	vsprintf(buf,format,vl);

	return uart_puts(buf);
}
#endif

// ���荞�݊֐�
void UART_IRQHandler(void)
{
	volatile char c;
  volatile short t;
	uint8_t iir=(uint8_t)(0xf&LPC_UART->IIR);
			
  // ��M
  if (iir&0x4) {
    c = LPC_UART->RBR;
    t = (UARTFIFO.rx.wp + 1) % UARTFIFO.rx.maxlen;
    UARTFIFO.rx.buf[UARTFIFO.rx.wp] = c;
    if (t != UARTFIFO.rx.rp) UARTFIFO.rx.wp = t;
  }
  // ���M
  if (iir&0x2) {
    if (UARTFIFO.tx.wp != UARTFIFO.tx.rp) {
      LPC_UART->THR = UARTFIFO.tx.buf[UARTFIFO.tx.rp++];
      UARTFIFO.tx.rp %= UARTFIFO.tx.maxlen;
    } else
      LPC_UART->IER &= ~(1<<1)	;	
  }
//	LPC_UART->LSR &= ~(0xF);
}

