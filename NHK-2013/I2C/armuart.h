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

   uart_init (br38400, txb, sizeof(txb), rxb, sizeof(rxb));

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
} UARTFIFO;

volatile UARTFIFO FIFO;


// SCI������
void uart_init (uint32_t baudrate, char *txbuf, short txl, char *rxbuf, short rxl)
{
  uint32_t DL,i;                                      	// �{�[���[�g������̕ϐ���`

  // ��M�f�[�^�p�ϐ�������
  FIFO.tx.buf = txbuf;
  FIFO.rx.buf = rxbuf;
  FIFO.tx.maxlen = txl;
  FIFO.rx.maxlen = rxl;
  FIFO.tx.wp = FIFO.tx.rp = 0;
  FIFO.rx.wp = FIFO.rx.rp = 0;

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
  if ((s = (FIFO.tx.rp - FIFO.tx.wp)) <= 0)
    s += FIFO.tx.maxlen;
  return s - 1;
}

// ��M�o�b�t�@�`�F�b�N
short uart_rx_buff (void)
{
  short s;
  if ((s = (FIFO.rx.wp - FIFO.rx.rp)) < 0)
		s += FIFO.rx.maxlen;
  return s;
}

// ��M�o�b�t�@�N���A
void uart_rx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  FIFO.rx.wp = FIFO.rx.rp = 0;
	LPC_UART->IER |= (0x01);	
}

// ���M�o�b�t�@�N���A
void uart_tx_purge (void)
{
	LPC_UART->IER &= ~(0x01);	
  FIFO.tx.wp = FIFO.tx.rp = 0;
}

// 1�o�C�g���M
void uart_putc (char c)
{
  volatile short t;

  t = (FIFO.tx.wp + 1) % FIFO.tx.maxlen;
  while (t == FIFO.tx.rp) ;			//�㏑���ҋ@
	if(LPC_UART->IER&0x02){
		FIFO.tx.buf[FIFO.tx.wp] = c;
		FIFO.tx.wp = t;
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

  while (FIFO.rx.rp == FIFO.rx.wp) ;
//	if(FIFO.rx.rp != FIFO.rx.wp)
	c = FIFO.rx.buf[FIFO.rx.rp++];
  FIFO.rx.rp %= FIFO.rx.maxlen;
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
	char buf[FIFO.tx.maxlen};

	va_start(vl,format);
	vsprintf(buf,format,vl);

	return uart_puts(buf);
}
#endif

// ���荞�݊֐�
void UART_IRQHandler(void)
{
	char c;
  volatile short t;
	uint8_t iir=(uint8_t)(0xf&LPC_UART->IIR);
			
  // ��M
  if (iir&0x4) {
    c = LPC_UART->RBR;
    t = (FIFO.rx.wp + 1) % FIFO.rx.maxlen;
    FIFO.rx.buf[FIFO.rx.wp] = c;
    if (t != FIFO.rx.rp) FIFO.rx.wp = t;
	LPC_GPIO1->DATA^=(1<<5);
  }
  // ���M
  if (iir&0x2) {
    if (FIFO.tx.wp != FIFO.tx.rp) {
      LPC_UART->THR = FIFO.tx.buf[FIFO.tx.rp++];
      FIFO.tx.rp %= FIFO.tx.maxlen;
    } else
      LPC_UART->IER &= ~(1<<1)	;	
  }
//	LPC_UART->LSR &= ~(0xF);
}

