// http://www7.big.jp/~kerokero/avr/
// Ç§ÇæÇ™ÇÌÅ@usada@kxb.biglobe.ne.jp

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned long

//---------------------------------------------------------------------
//   ÇhÅ^ÇnÉsÉìíËã`
//---------------------------------------------------------------------
struct PB{
	char RDATA:1;		// PB0
	char RACK:1;		// PB1
	char :1;			// PB2
	char :1;			// PB3
	char :1;			// PB4
	char :1;			// PB5
	char :1;			// PB6
	char :1;			// PB7
};
#define pib (*(volatile struct PB*)&PINB)
#define pdb (*(volatile struct PB*)&DDRB)
#define pob (*(volatile struct PB*)&PORTB)

struct PD{
	char :1;			// PD0
	char TxD:1;			// PD1
	char :1;			// PD2
	char :1;			// PD3
	char TSEL:1;		// PD4
	char TCOMM:1;		// PD5
	char TCLK:1;		// PD6
};
#define pid (*(volatile struct PD*)&PIND)
#define pdd (*(volatile struct PD*)&DDRD)
#define pod (*(volatile struct PD*)&PORTD)


