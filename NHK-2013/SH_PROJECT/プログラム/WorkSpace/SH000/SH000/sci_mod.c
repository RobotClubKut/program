//
// SCIモジュール
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
// 1文字送信
//   引数   - unsigned char c : 送信データ
//   戻り値 - 0:送信失敗、1:送信成功
// --------------------------------------------------------
short SCI_putc(char c){
	// 改行コードの変換
	if(c == '\n'){
		if(!SCI_write('\r')) return 0;
		if(!SCI_write('\n')) return 0;
	}
	// 通常のデータ
	else{
		if(!SCI_write(c)) return 0;
	}
	return 1;
}

// --------------------------------------------------------
// 文字列送信
//   引数   - unsigned char *str : 送信データ
//   戻り値 - 送信文字数
// --------------------------------------------------------
short SCI_putstr(char *str){
	short len;
	
	len = 0;
	
	// 終端コードまで送信
	while(*str){
		if(!SCI_putc(*(str++))) return 0;
		len++;
	}
	
	// 送信文字数を返す
	return len;
}

// --------------------------------------------------------
// 文字列送信(改行付き)
//   引数   - unsigned char *str : 送信データ
//   戻り値 - 送信文字数
// --------------------------------------------------------
short SCI_puts(char *str){
	short len;
	
	// 文字列送信
	len = SCI_putstr(str);
	
	// 改行送信
	SCI_putc('\n');

	// 送信文字数を返す
	return len+1;
}

// --------------------------------------------------------
//  10進数文字かチェック
// --------------------------------------------------------
static short isDec(char c){
    if ('0'<=c && c<='9') return TRUE;
    return FALSE;
}

// --------------------------------------------------------
//  数値を10進数文字変換
// --------------------------------------------------------
static void uint2Dec(unsigned long n, char *buf){
    char c;
    short len = 0;
    short i, half;

    // 10進文字列へ変換し文字数をカウント
    do{
        if(n == 0)  i = 0;
        else        i = n % 10;
        buf[len] = (char)(i + '0');
        len++;
        n /= 10;
    }while(n != 0);

    // 文字の並び順を直す
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // 終端コードの挿入
    buf[len]='\0';
}

// --------------------------------------------------------
//  数値を16進数文字変換
// --------------------------------------------------------
static void uint2Hex(unsigned long n, short upper, char *buf){
    char c;
    char a = 'a';
    short len = 0;
    short i, half;

    // 大文字/小文字の設定
    if(upper) a = 'A';
    
    // 16進文字列へ変換し文字数をカウント
    do{
        i = n & 0x0F;
        if(i > 9)  buf[len] = (unsigned char)(i + a - 10);
        else       buf[len] = (unsigned char)(i + '0');
        len++;
        n >>= 4;
    }while(n != 0);

    // 文字の並び順を直す
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // 終端コードの挿入 */
    buf[len]='\0';
}

// --------------------------------------------------------
//  指定されたフォーマットで表示する
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

    // 文字数のカウント
    for(len=0; *str != '\0'; len++, str++);
    
    // マイナスなら文字数調整
    if(minus) len++;

    // 文字数の調整
    if(order){
        if(order>len)  order -= len;
        else           order  = 0;
    }

    // 右詰め
    if( ! alignLeft){
        // 詰め文字の設定
        if(fillZero){
            pad = '0';
            
            // マイナス表示
            if(minus){
                SCI_putc('-');
                minus = 0;
            }
        }

        for(i=0; i<order; i++)
            SCI_putc(pad);
    }

    // マイナス表示
    if(minus)  SCI_putc('-');

    // データの表示
    SCI_putstr(ptr);

    /* 左詰め */
    if(alignLeft)
        for(i=0; i<order; i++)
            SCI_putc(' ');
}


// --------------------------------------------------------
// フォーマット解釈
//   引数   - 
//   戻り値 - 
// --------------------------------------------------------
static char *parseFormat(char *str,void *value){
	short alignLeft=0;
	short fillZero=0;
	short order=0;
	short minus=0;
	char buf[12];
	char *ptr=buf;
	
	//左詰
	if(*str=='-'){ alignLeft = 1; str++; }
	
	//ゼロフィル
	if(*str=='0'){ fillZero = 1; str++; }
	
	// 文字数指定判定
	if(isDec(*str)){
		for(order=0;isDec(*str);){
			order *= 10;
			order += (*str - '0');
			str++;
		}
	}

	// 種類判定,表示準備
	switch(*str){
		case 'd':  // 符号付10進数(short型)
		case 'D':  // 符号付10進数(short型)
			if((signed short)value >= 0){
//				uint2Dec((unsigned short)value , buf);
				uint2Dec((unsigned long)value , buf);
			}else{
//				uint2Dec((unsigned short)(-(signed short)value) , buf); 
				uint2Dec((unsigned long)(-(signed short)value) , buf); 
				minus = 1;
			}
			break;
		case 'l':  // 符号付10進数(long型)
		case 'L':  // 符号付10進数(long型)
			if((signed long)value >= 0){
				uint2Dec((unsigned long)value , buf);
			}else{
				uint2Dec((unsigned long)(-(signed long)value) , buf); 
				minus = 1;
			}
			break;
		case 'u':   // 符号なし10進数
		case 'U':   // 符号なし10進数
			uint2Dec((unsigned short)value , buf);
			break;
		case 'x':   // 小文字16進数
			uint2Hex((unsigned long)value , 0 , buf);
			break;
		case 'X':   // 大文字16進数
			uint2Hex((unsigned long)value , 1 , buf);
			break;
		case 's':   // 文字列
		case 'S':   // 文字列
			ptr = (char *)value;
			break;
		case 'c':   // 1文字
		case 'C':   // 1文字
			buf[0] = (char)((unsigned long)value & 0xFF);
			buf[1] = '\0';
			break;
		default: 
			buf[0] = '\0';
			break;
	}

	// 表示
	printFormat(ptr,order,alignLeft,fillZero,minus);
	
	str++;
	return(str);
	
}


// --------------------------------------------------------
// printf
//   引数   - 
//   戻り値 - 
// --------------------------------------------------------
short SCI_printf(char *str , ...){
	va_list ap;
//	unsigned char *ptr;
	char *ptr;
	
	ptr = str;
	
	// 可変引数の初期化
	va_start(ap,str);
	
	while(*ptr){
		// 特殊文字
		if(*ptr=='%'){
			ptr++;
			
			if(*ptr=='%'){ SCI_putc('%'); ptr++;	}  // %表示
			else{
				ptr = parseFormat(ptr,va_arg(ap,void *));
				if(ptr == NULL) return -1;
			}
		}
		// 通常文字
		else{
			SCI_putc(*ptr);
			ptr++;
		}
	}
	va_end(ap);
	return (ptr-str);  // 送信文字数
}

// --------------------------------------------------------
// 1文字受信
//   引数   - 0:データ受信を待たない , 1:データ受信を待つ
//   戻り値 - 
// --------------------------------------------------------
unsigned char SCI_getc(short wait){
	unsigned char c;
	
	if(wait)  while(!SCI_read(&c));  // 受信まで待つ
	else      SCI_read(&c);          // 受信を待たない
	
	// 改行コードの変換
	if(c == 0x0D) c = '\n';
	return c;
}

// --------------------------------------------------------
// 文字列受信
//   引数   - データを格納するアドレス
//   戻り値 - 最後のデータが格納されているアドレス
// --------------------------------------------------------
unsigned char *SCI_gets(unsigned char *str){
	short i = 0;
	unsigned char c;
	
	// 改行コードまで受信
	while((c = SCI_getc(1)) != '\n'){
		str[i++] = c;
		SCI_putc(c);           // エコーバック
	}
	
	// 改行コードを終端コードに変換
	str[i] = '\0';
	
	return str;
}

// --------------------------------------------------------
// 1文字受信
//   引数   - 
//   戻り値 - 
// --------------------------------------------------------
short s_getc(unsigned char *c){
	return s_read(c);
}

#endif