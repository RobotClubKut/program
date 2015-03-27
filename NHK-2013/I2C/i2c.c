

uint8_t I2CMODE;
typedef struct {
  struct {
    char  *buf;
    short wp;	//���ݒl
    short rp;	//�ڕW�l
    short maxlen;
  } mtx;
  struct {
    char  *buf;
    short wp;	//���ݒl
    short rp;	//�ڕW�l
    short maxlen;
  } stx;
  struct {
    char  *buf;
    short wp;
    short rp;
    short maxlen;
  } rx;
} i2cfifo;

volatile i2cfifo I2CFIFO;

void i2_init(uint8_t config,uint16_t fm,char *txbuf, short txl, char *rxbuf, short rxl)
{
  uint32_t DL;   
	
  LPC_SYSCON->PRESETCTRL |= (0x1<<1);
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
	
	//
  I2CFIFO.mtx.buf = txbuf;
 // I2CFIFO.stx.buf = txbuf;
  I2CFIFO.rx.buf = rxbuf;
  I2CFIFO.mtx.maxlen = txl;
 // I2CFIFO.stx.maxlen = txl;
  I2CFIFO.rx.maxlen = rxl;
  I2CFIFO.mtx.wp = I2CFIFO.mtx.rp = 0;
 // I2CFIFO.stx.wp = I2CFIFO.stx.rp = 0;
  I2CFIFO.rx.wp = I2CFIFO.rx.rp = 0;
	I2CMODE=config;

	//�s���ݒ�
  LPC_IOCON->PIO0_4 &= ~0x3F;	/*  I2C I/O config */
  LPC_IOCON->PIO0_4 |= 0x01;		/* I2C SCL */
  LPC_IOCON->PIO0_5 &= ~0x3F;	
  LPC_IOCON->PIO0_5 |= 0x01;		/* I2C SDA */	
	if(fm>400){		//Fast Mode Plus �t�@�[�X�g���[�h�v���X
		LPC_IOCON->PIO0_4 |= (0x2<<8);
		LPC_IOCON->PIO0_5 |= (0x2<<8);
	}
	//��ԃ��W�X�^�N���A
	LPC_I2C->CONCLR=(0x6C);

	//�T�C�N���N���b�N�ݒ�
	DL=SystemCoreClock/1000/fm/2;
	LPC_I2C->SCLL=DL;
	LPC_I2C->SCLH=DL;
	
	if(!(I2CMODE&1)){	//�X���C�u���[�h
		//�A�h���X�ݒ�

	}	

	//���荞�݃��[�h�L��
  NVIC_EnableIRQ(I2C_IRQn);
  LPC_I2C->CONSET |= 0x44;
	
}
void I2C_IRQHandler(void) {
	static uint8_t lp,tp;
	uint8_t StatValue;
	StatValue = LPC_I2C->STAT;
	switch(StatValue){
		
		case(0x00):	//�o�X�G���[
		LPC_I2C->CONSET = 0x14;
		LPC_I2C->CONCLR = 0x8;
		break;
		
		case(0x08):	//START�r�b�g���M�ς�
		case(0x10):  //RepeatedSTART�r�b�g���M�ς�
		if(I2CFIFO.mtx.buf[I2CFIFO.mtx.rp]&0x01){		//r���[�h
			LPC_I2C->DAT = I2CFIFO.mtx.buf[I2CFIFO.mtx.rp];
		}else{																					//t���[�h
			tp=2;
			lp=I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp+1)%I2CFIFO.mtx.maxlen];
			LPC_I2C->DAT = I2CFIFO.mtx.buf[I2CFIFO.mtx.rp];
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0x18):	//�A�h���X�������ݑ��M�ς�
		lp=I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp+tp++)%I2CFIFO.mtx.maxlen];
		LPC_I2C->DAT = lp;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;	
		break;

		case(0x20):	//NOTACK�Ή�
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;	
		break;
		
		case(0x28):	//1�o�C�g���M�ς�
		if(lp+1==tp){				//�ŏI�o�C�g���M�ς�
			I2CFIFO.mtx.rp=(I2CFIFO.mtx.rp+lp+2)%I2CFIFO.mtx.maxlen;
			LPC_I2C->CONSET |= 0x14;
			LPC_I2C->CONCLR |= 0x08;
		}else{							//���o�C�g���M
			LPC_I2C->DAT = I2CFIFO.mtx.buf[(I2CFIFO.mtx.rp+tp++)%I2CFIFO.mtx.maxlen];
			LPC_I2C->CONSET |= 0x04;
			LPC_I2C->CONCLR |= 0x08;
		}
		break;
		
		case(0x30):	//1�o�C�g���M�ς� NOTACK��M�ς�
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08|0x20;			//������񑗐M���邩�ǂ���
		break;
		
		case(0x38):	//���M���s
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

	//	�}�X�^���V�[�o
		case(0x40):	//�X���C�u�A�h���X�ǂݎ�著�M�ς�
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0x48): //NOTACK �Ԃ��ꂽ-
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;			//I2C�̏������̂Ƃ��ɍēx�v�����邩�ݒ�
		break;

		case(0x50):	//�f�[�^��M�ς�
		if(tp){		//�f�[�^��M
			I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = LPC_I2C->DAT;
		}else{		//�f�[�^����M
			lp = LPC_I2C->DAT;
			if(lp==0){		//�f�[�^����0�̂Ƃ�
				LPC_I2C->CONSET |= 0x14;
				LPC_I2C->CONCLR |= 0x08;
				break;
			}
			I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = lp;
		}
		
		if(lp==tp){	//���ōŏI�o�C�g
			LPC_I2C->CONCLR |= 0x0C;
		}else{						//�f�[�^�����܁[���B
			LPC_I2C->CONSET |= 0x04;
			LPC_I2C->CONCLR |= 0x08;
		}
		break;
		
		case(0x58):	//�f�[�^��M�ς݁@NOTACK���M�ς�
		I2CFIFO.rx.buf[(I2CFIFO.rx.wp+tp++)%I2CFIFO.rx.maxlen] = LPC_I2C->DAT;
		I2CFIFO.rx.wp+=tp+1;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;		
		LPC_I2C->CONSET |= 0x14;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
	//	�X���[�u���V�[�o
		case(0x60):	//�X���[�u�A�h���X+�������݂���M�ς�
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0x68):	//�}�X�^����s�����@�����Ď�������΂ꂽ
		tp=0;
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0x70):	//�[�l�����R�[����M�ς�
		tp=0;
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0x78):	//�}�X�^����s���� �����ă[�l�����R�[��
		tp=0;
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x80):	//�X���[�u�A�h���X�Ńf�[�^��M�ς� ACK���M�ς�
		if(tp==0){		//�f�[�^����M
			lp= LPC_I2C->DAT;
			if(lp==0){
				LPC_I2C->CONSET |= 0x04;
				LPC_I2C->CONCLR |= 0x08;				
				break;
			}
			I2CFIFO.rx.buf[I2CFIFO.rx.wp]  = lp;
		}
		if(tp++==lp){		//�ŏI�o�C�g��M����
		I2CFIFO.rx.wp+=tp;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;
			////////////////////////////���[�h�ɂ���Ă�NOTACK��Ԃ�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;	
		}else{
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;	
		}
		break;

		case(0x88):	//�X���[�u�A�h���X�Ńf�[�^��M�ς� NOTACK���M�ς�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

		case(0x90):	//�[�l�����R�[���Ńf�[�^��M�ς� ACK���M�ς�
		if(tp==0){		//�f�[�^����M
			lp= LPC_I2C->DAT;
			if(lp==0){
					////////////////////////////���[�h�ɂ���Ă�NOTACK��Ԃ�
				LPC_I2C->CONSET |= 0x04;
				LPC_I2C->CONCLR |= 0x08;				
				break;
			}
			I2CFIFO.rx.buf[I2CFIFO.rx.wp]  = lp;
		}
		if(tp++==lp){		//�ŏI�o�C�g��M����
		I2CFIFO.rx.wp+=tp;
		I2CFIFO.rx.wp%=I2CFIFO.rx.maxlen;
			////////////////////////////���[�h�ɂ���Ă�NOTACK��Ԃ�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;	
		}else{
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;	
		}
		break;

		case(0x98):	//�[�l�����R�[���Ńf�[�^��M�ς� NOTACK���M�ς�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0xA0):	//STOP�r�b�g�܂���RepeatedSTART��M
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;

	//�X���[�u�g�����X�~�b�^
		case(0xA8):	//�X���[�u�A�h���X�{�ǂݎ���M ACK�𑗐M�ς�
		tp=0;
		if(I2CFIFO.stx.rp==I2CFIFO.stx.wp){		//���M�o�b�t�@�[�ɉ����Ȃ��Ƃ�
			LPC_I2C->DAT = 0;									//�f�[�^��0���M
		}else{
			LPC_I2C->DAT = I2CFIFO.stx.buf[I2CFIFO.stx.rp];
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0xB0):	// �}�X�^����s���� �X���[�u�A�h���X�ŌĂяo��
		tp=0;
		if(I2CFIFO.stx.rp==I2CFIFO.stx.wp){		//���M�o�b�t�@�[�ɉ����Ȃ��Ƃ�
			LPC_I2C->DAT = 0;									//�f�[�^��0���M
		}else{
			LPC_I2C->DAT = I2CFIFO.stx.buf[I2CFIFO.stx.rp];
		}
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		break;
		
		case(0xB8):	// �f�[�^�𑗐M�ς݁@ACK����M�ς�
		LPC_I2C->DAT = I2CFIFO.stx.buf[(I2CFIFO.stx.rp+tp++)%I2CFIFO.stx.maxlen];
		LPC_I2C->CONSET |= 0x24;
		LPC_I2C->CONCLR |= 0x08;
		if(lp==tp){		//�S�f�[�^���M����
			I2CFIFO.stx.rp+=tp+1;
			I2CFIFO.stx.rp%=I2CFIFO.stx.maxlen;
		}
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;		
		break;
		
		case(0xC0):	// �f�[�^�𑗐M�ς݁@NOTACK����M�ς�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;		
		break;
		
		case(0xC8):	// �ŏI�f�[�^���M�ς݃f�[�^�𑗐M�ς݁@ACK����M�ς�
		LPC_I2C->CONSET |= 0x04;
		LPC_I2C->CONCLR |= 0x08;		////////�����ɓ����ׂ�����
		break;

		}	
		
		if(I2CFIFO.mtx.rp != I2CFIFO.mtx.wp)
			LPC_I2C->CONSET |= 0x20;
}

// ���M�o�b�t�@�`�F�b�N
short i2cm_tx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.mtx.rp - I2CFIFO.mtx.wp)) <= 0)
    s += I2CFIFO.mtx.maxlen;
  return s - 1;
}
short i2cs_tx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.stx.rp - I2CFIFO.stx.wp)) <= 0)
    s += I2CFIFO.stx.maxlen;
  return s - 1;
}
// ��M�o�b�t�@�`�F�b�N
short i2c_rx_buff (void)
{
  short s;
  if ((s = (I2CFIFO.rx.wp - I2CFIFO.rx.rp)) < 0)
		s += I2CFIFO.rx.maxlen;
  return s;
}

// ��M�o�b�t�@�N���A
void i2c_rx_purge (void)
{
  I2CFIFO.rx.wp = I2CFIFO.rx.rp = 0;
}

// ���M�o�b�t�@�N���A
void i2cm_tx_purge (void)
{
  I2CFIFO.mtx.wp = I2CFIFO.mtx.rp = 0;
}
void i2cs_tx_purge (void)
{
  I2CFIFO.stx.wp = I2CFIFO.stx.rp = 0;
}
//	�ꕶ���o�b�t�@�[�߂�
void i2cm_txd(char c){
  volatile short t;
  t = (I2CFIFO.mtx.wp + 1) % I2CFIFO.mtx.maxlen;
  while (t == I2CFIFO.mtx.rp) ;			//�㏑���ҋ@
	I2CFIFO.mtx.buf[I2CFIFO.mtx.wp] = c;
	I2CFIFO.mtx.wp = t;
	LPC_I2C->CONSET |= 0x20;
}
void i2cs_txd(char c){
  volatile short t;
  t = (I2CFIFO.stx.wp + 1) % I2CFIFO.stx.maxlen;
  while (t == I2CFIFO.stx.rp) ;			//�㏑���ҋ@
	I2CFIFO.stx.buf[I2CFIFO.stx.wp] = c;
	I2CFIFO.stx.wp = t;
//	LPC_I2C->CONSET |= 0x20;
}
// �ꕶ�����M
void i2cm_putc (char ad,char s){
	i2cm_txd(ad<<1);
	i2cm_txd(1);
  i2cm_txd (s);
}
// �f�[�^���M
void i2cm_puts (char ad,char *st){
	short l=0;
	i2cm_txd(ad<<1);
	while (*st++)	l++;
	i2cm_txd(l);
  while (*st) {
    i2cm_txd (*st);
    if (*st++ == '\n') i2cm_txd ('\r');
  }
}
/*
void i2cs_txd (char *st){
	i2cm_putc(ad<<1);
  while (*st) {
    i2cm_putc (*st);
    if (*st++ == '\n') i2cm_putc ('\r');
  }
}

// �f�[�^��M
void i2cm_rxb(char ad){
	i2cm_putc(ad<<1);
}
*/
// ��M�f�[�^�o�b�t�@���1�����ǂݏo��
char i2c_getc(void){
  char c=0;
  while (I2CFIFO.rx.rp == I2CFIFO.rx.wp) ;
//	if(I2CFIFO.rx.rp != I2CFIFO.rx.wp)
	c = I2CFIFO.rx.buf[I2CFIFO.rx.rp++];
  I2CFIFO.rx.rp %= I2CFIFO.rx.maxlen;
  return c;
}
// ��M�f�[�^�o�b�t�@���1�f�[�^�ǂݏo��
