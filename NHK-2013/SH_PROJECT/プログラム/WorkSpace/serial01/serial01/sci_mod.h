
#ifndef TRUE
  #define		TRUE	1
#endif
#ifndef FALSE
  #define		FALSE	0
#endif
#ifndef NULL
  #define		NULL	0
#endif

extern void SCI_init(void);
extern short SCI_printf(char *str , ...);
extern short SCI_putc(char c);
extern short SCI_puts(char *str);
extern short SCI_putstr(char *str);
extern unsigned char *SCI_gets(unsigned char *str);
extern unsigned char SCI_getc(short wait);
extern short s_getc(unsigned char *c);

