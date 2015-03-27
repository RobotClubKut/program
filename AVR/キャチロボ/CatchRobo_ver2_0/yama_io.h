#include <avr/io.h>

// =============================================
//    ビットレジスタ用共用体
// =============================================
typedef union{
    // ▼====== 全ビットアクセス用メンバ
    unsigned char    all    : 8;
    // ▼====== 各ビットアクセス用フラグ
    struct{
       unsigned char    b0 : 1;
       unsigned char    b1 : 1;
       unsigned char    b2 : 1;
       unsigned char    b3 : 1;
       unsigned char    b4 : 1;
       unsigned char    b5 : 1;
       unsigned char    b6 : 1;
       unsigned char    b7 : 1;
    }bit;
}SFR8;

// =============================================
//    レジスタのアドレスマッピング
// =============================================
#define R_PORTA    (*(volatile SFR8 *)(&PORTA))
#define R_PORTB    (*(volatile SFR8 *)(&PORTB))
#define R_PORTC    (*(volatile SFR8 *)(&PORTC))
#define R_PORTD    (*(volatile SFR8 *)(&PORTD))

#define R_PINA    (*(volatile SFR8 *)(&PINA))
#define R_PINB    (*(volatile SFR8 *)(&PINB))
#define R_PINC    (*(volatile SFR8 *)(&PINC))
#define R_PIND    (*(volatile SFR8 *)(&PIND))

// =============================================
//    ビット単位での定義
// =============================================
#define PORTA_0 R_PORTA.bit.b0
#define PORTA_1 R_PORTA.bit.b1
#define PORTA_2 R_PORTA.bit.b2
#define PORTA_3 R_PORTA.bit.b3
#define PORTA_4 R_PORTA.bit.b4
#define PORTA_5 R_PORTA.bit.b5
#define PORTA_6 R_PORTA.bit.b6
#define PORTA_7 R_PORTA.bit.b7

#define PORTB_0 R_PORTB.bit.b0
#define PORTB_1 R_PORTB.bit.b1
#define PORTB_2 R_PORTB.bit.b2
#define PORTB_3 R_PORTB.bit.b3
#define PORTB_4 R_PORTB.bit.b4
#define PORTB_5 R_PORTB.bit.b5
#define PORTB_6 R_PORTB.bit.b6
#define PORTB_7 R_PORTB.bit.b7

#define PORTC_0 R_PORTC.bit.b0
#define PORTC_1 R_PORTC.bit.b1
#define PORTC_2 R_PORTC.bit.b2
#define PORTC_3 R_PORTC.bit.b3
#define PORTC_4 R_PORTC.bit.b4
#define PORTC_5 R_PORTC.bit.b5
#define PORTC_6 R_PORTC.bit.b6
#define PORTC_7 R_PORTC.bit.b7

#define PORTD_0 R_PORTD.bit.b0
#define PORTD_1 R_PORTD.bit.b1
#define PORTD_2 R_PORTD.bit.b2
#define PORTD_3 R_PORTD.bit.b3
#define PORTD_4 R_PORTD.bit.b4
#define PORTD_5 R_PORTD.bit.b5
#define PORTD_6 R_PORTD.bit.b6
#define PORTD_7 R_PORTD.bit.b7



#define PINA_0 R_PINA.bit.b0
#define PINA_1 R_PINA.bit.b1
#define PINA_2 R_PINA.bit.b2
#define PINA_3 R_PINA.bit.b3
#define PINA_4 R_PINA.bit.b4
#define PINA_5 R_PINA.bit.b5
#define PINA_6 R_PINA.bit.b6
#define PINA_7 R_PINA.bit.b7

#define PINB_0 R_PINB.bit.b0
#define PINB_1 R_PINB.bit.b1
#define PINB_2 R_PINB.bit.b2
#define PINB_3 R_PINB.bit.b3
#define PINB_4 R_PINB.bit.b4
#define PINB_5 R_PINB.bit.b5
#define PINB_6 R_PINB.bit.b6
#define PINB_7 R_PINB.bit.b7

#define PINC_0 R_PINC.bit.b0
#define PINC_1 R_PINC.bit.b1
#define PINC_2 R_PINC.bit.b2
#define PINC_3 R_PINC.bit.b3
#define PINC_4 R_PINC.bit.b4
#define PINC_5 R_PINC.bit.b5
#define PINC_6 R_PINC.bit.b6
#define PINC_7 R_PINC.bit.b7

#define PIND_0 R_PIND.bit.b0
#define PIND_1 R_PIND.bit.b1
#define PIND_2 R_PIND.bit.b2
#define PIND_3 R_PIND.bit.b3
#define PIND_4 R_PIND.bit.b4
#define PIND_5 R_PIND.bit.b5
#define PIND_6 R_PIND.bit.b6
#define PIND_7 R_PIND.bit.b7


   
 
