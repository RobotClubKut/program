//
// SCI���W���[��
//
//
// 2007.02.15 K.Nishimura
//

#ifndef SCI_MODC
#define SCI_MODC

#include <stdarg.h>
#include "iodefine.h"
#include "sci_mod.h"

extern void SCI_init(void);
extern short SCI_write(unsigned char c);
extern short SCI_read(unsigned char *c);

short SCI_printf(char *str , ...);
short SCI_putc(char c);
short SCI_puts(char *str);
short SCI_putstr(char *str);
unsigned char *SCI_gets(unsigned char *str);
unsigned char SCI_getc(short wait);
short s_getc(unsigned char *c);

// --------------------------------------------------------
// 1�������M
//   ����   - unsigned char c : ���M�f�[�^
//   �߂�l - 0:���M���s�A1:���M����
// --------------------------------------------------------
short SCI_putc(char c){
	// ���s�R�[�h�̕ϊ�
	if(c == '\n'){
		if(!SCI_write('\r')) return 0;
		if(!SCI_write('\n')) return 0;
	}
	// �ʏ�̃f�[�^
	else{
		if(!SCI_write(c)) return 0;
	}
	return 1;
}

// --------------------------------------------------------
// �����񑗐M
//   ����   - unsigned char *str : ���M�f�[�^
//   �߂�l - ���M������
// --------------------------------------------------------
short SCI_putstr(char *str){
	short len;
	
	len = 0;
	
	// �I�[�R�[�h�܂ő��M
	while(*str){
		if(!SCI_putc(*(str++))) return 0;
		len++;
	}
	
	// ���M��������Ԃ�
	return len;
}

// --------------------------------------------------------
// �����񑗐M(���s�t��)
//   ����   - unsigned char *str : ���M�f�[�^
//   �߂�l - ���M������
// --------------------------------------------------------
short SCI_puts(char *str){
	short len;
	
	// �����񑗐M
	len = SCI_putstr(str);
	
	// ���s���M
	SCI_putc('\n');

	// ���M��������Ԃ�
	return len+1;
}

// --------------------------------------------------------
//  10�i���������`�F�b�N
// --------------------------------------------------------
static short isDec(char c){
    if ('0'<=c && c<='9') return TRUE;
    return FALSE;
}

// --------------------------------------------------------
//  ���l��10�i�������ϊ�
// --------------------------------------------------------
static void uint2Dec(unsigned long n, char *buf){
    char c;
    short len = 0;
    short i, half;

    // 10�i������֕ϊ������������J�E���g
    do{
        if(n == 0)  i = 0;
        else        i = n % 10;
        buf[len] = (char)(i + '0');
        len++;
        n /= 10;
    }while(n != 0);

    // �����̕��я��𒼂�
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // �I�[�R�[�h�̑}��
    buf[len]='\0';
}

// --------------------------------------------------------
//  ���l��16�i�������ϊ�
// --------------------------------------------------------
static void uint2Hex(unsigned long n, short upper, char *buf){
    char c;
    char a = 'a';
    short len = 0;
    short i, half;

    // �啶��/�������̐ݒ�
    if(upper) a = 'A';
    
    // 16�i������֕ϊ������������J�E���g
    do{
        i = n & 0x0F;
        if(i > 9)  buf[len] = (unsigned char)(i + a - 10);
        else       buf[len] = (unsigned char)(i + '0');
        len++;
        n >>= 4;
    }while(n != 0);

    // �����̕��я��𒼂�
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // �I�[�R�[�h�̑}�� */
    buf[len]='\0';
}

// --------------------------------------------------------
//  �w�肳�ꂽ�t�H�[�}�b�g�ŕ\������
// --------------------------------------------------------
static void printFormat(
//  unsigned char *ptr,
  char *ptr,
  short order, 
  short alignLeft, 
  short fillZero, 
  short minus)
{
    char *str = ptr;
    char pad = ' ';
    short len = 0;
    long  i;

    // �������̃J�E���g
    for(len=0; *str != '\0'; len++, str++);
    
    // �}�C�i�X�Ȃ當��������
    if(minus) len++;

    // �������̒���
    if(order){
        if(order>len)  order -= len;
        else           order  = 0;
    }

    // �E�l��
    if( ! alignLeft){
        // �l�ߕ����̐ݒ�
        if(fillZero){
            pad = '0';
            
            // �}�C�i�X�\��
            if(minus){
                SCI_putc('-');
                minus = 0;
            }
        }

        for(i=0; i<order; i++)
            SCI_putc(pad);
    }

    // �}�C�i�X�\��
    if(minus)  SCI_putc('-');

    // �f�[�^�̕\��
    SCI_putstr(ptr);

    /* ���l�� */
    if(alignLeft)
        for(i=0; i<order; i++)
            SCI_putc(' ');
}


// --------------------------------------------------------
// �t�H�[�}�b�g����
//   ����   - 
//   �߂�l - 
// --------------------------------------------------------
static char *parseFormat(char *str,void *value){
	short alignLeft=0;
	short fillZero=0;
	short order=0;
	short minus=0;
	char buf[12];
	char *ptr=buf;
	
	//���l
	if(*str=='-'){ alignLeft = 1; str++; }
	
	//�[���t�B��
	if(*str=='0'){ fillZero = 1; str++; }
	
	// �������w�蔻��
	if(isDec(*str)){
		for(order=0;isDec(*str);){
			order *= 10;
			order += (*str - '0');
			str++;
		}
	}

	// ��ޔ���,�\������
	switch(*str){
		case 'd':  // �����t10�i��(short�^)
		case 'D':  // �����t10�i��(short�^)
			if((signed short)value >= 0){
//				uint2Dec((unsigned short)value , buf);
				uint2Dec((unsigned long)value , buf);
			}else{
//				uint2Dec((unsigned short)(-(signed short)value) , buf); 
				uint2Dec((unsigned long)(-(signed short)value) , buf); 
				minus = 1;
			}
			break;
		case 'l':  // �����t10�i��(long�^)
		case 'L':  // �����t10�i��(long�^)
			if((signed long)value >= 0){
				uint2Dec((unsigned long)value , buf);
			}else{
				uint2Dec((unsigned long)(-(signed long)value) , buf); 
				minus = 1;
			}
			break;
		case 'u':   // �����Ȃ�10�i��
		case 'U':   // �����Ȃ�10�i��
			uint2Dec((unsigned short)value , buf);
			break;
		case 'x':   // ������16�i��
			uint2Hex((unsigned long)value , 0 , buf);
			break;
		case 'X':   // �啶��16�i��
			uint2Hex((unsigned long)value , 1 , buf);
			break;
		case 's':   // ������
		case 'S':   // ������
			ptr = (char *)value;
			break;
		case 'c':   // 1����
		case 'C':   // 1����
			buf[0] = (char)((unsigned long)value & 0xFF);
			buf[1] = '\0';
			break;
		default: 
			buf[0] = '\0';
			break;
	}

	// �\��
	printFormat(ptr,order,alignLeft,fillZero,minus);
	
	str++;
	return(str);
	
}


// --------------------------------------------------------
// printf
//   ����   - 
//   �߂�l - 
// --------------------------------------------------------
short SCI_printf(char *str , ...){
	va_list ap;
//	unsigned char *ptr;
	char *ptr;
	
	ptr = str;
	
	// �ψ����̏�����
	va_start(ap,str);
	
	while(*ptr){
		// ���ꕶ��
		if(*ptr=='%'){
			ptr++;
			
			if(*ptr=='%'){ SCI_putc('%'); ptr++;	}  // %�\��
			else{
				ptr = parseFormat(ptr,va_arg(ap,void *));
				if(ptr == NULL) return -1;
			}
		}
		// �ʏ핶��
		else{
			SCI_putc(*ptr);
			ptr++;
		}
	}
	va_end(ap);
	return (ptr-str);  // ���M������
}

// --------------------------------------------------------
// 1������M
//   ����   - 0:�f�[�^��M��҂��Ȃ� , 1:�f�[�^��M��҂�
//   �߂�l - 
// --------------------------------------------------------
unsigned char SCI_getc(short wait){
	unsigned char c;
	
	if(wait)  while(!SCI_read(&c));  // ��M�܂ő҂�
	else      SCI_read(&c);          // ��M��҂��Ȃ�
	
	// ���s�R�[�h�̕ϊ�
	if(c == 0x0D) c = '\n';
	return c;
}

// --------------------------------------------------------
// �������M
//   ����   - �f�[�^���i�[����A�h���X
//   �߂�l - �Ō�̃f�[�^���i�[����Ă���A�h���X
// --------------------------------------------------------
unsigned char *SCI_gets(unsigned char *str){
	short i = 0;
	unsigned char c;
	
	// ���s�R�[�h�܂Ŏ�M
	while((c = SCI_getc(1)) != '\n'){
		str[i++] = c;
		SCI_putc(c);           // �G�R�[�o�b�N
	}
	
	// ���s�R�[�h���I�[�R�[�h�ɕϊ�
	str[i] = '\0';
	
	return str;
}

// --------------------------------------------------------
// 1������M
//   ����   - 
//   �߂�l - 
// --------------------------------------------------------
short s_getc(unsigned char *c){
	return s_read(c);
}

#endif