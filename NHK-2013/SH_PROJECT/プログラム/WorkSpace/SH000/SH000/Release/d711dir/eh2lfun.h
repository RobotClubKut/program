/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = eh2lfun :                                            */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

extern _HEADER *_freeptr;

extern int    open(char*, int,int);
extern int    read(int, char*, unsigned);
extern int    write(int, char*, unsigned);
extern int    close(int);
extern long   lseek(int, long, int);
extern int    _flopen(const char*, const char*, char*);
extern int    _flclose(FILE*);
extern int    _fillbuf(FILE*);
extern int    _flshbuf(int, FILE*);
extern void   _alocbuf(FILE*);
extern int    _fmtin(int,int (*)(FILE *), FILE*, const char*, char*); /* C S0100 SP */
extern int    _fmtout(int,int (*)(int, FILE *), FILE*, const char*, char*); /* C S0100 SP */ 
#endif

extern VOID   _its(CHAR*, CHAR*, INT);
extern int    _xti(long double, INT, CHAR*, INT*, CHAR*);
extern long double *_stx(INT, CHAR*, INT);                     /* C S40001SP */
extern VOID   _mult(UCHAR*, UCHAR*, UCHAR*);
extern VOID   _mult64(SHORT*, UCHAR*, SHORT, UCHAR*);
extern VOID   _divi(CHAR*, CHAR*, CHAR*);
extern int    _sub(INT, UCHAR*, UCHAR*, INT);
extern VOID   _add(UCHAR*, UCHAR*, INT);
extern VOID   _power(INT, SHORT*, UCHAR*);
extern VOID   _pow5(INT, CHAR*);
extern VOID   _pow10(INT, SHORT*, UCHAR*);
extern int    _log10(long double);                             /* C S40001SP */
extern INT    _lsft(UCHAR*, INT);
extern int    _rsft(UCHAR*, INT);
extern INT    _lsfts(UCHAR*, INT, SHORT);
extern INT    _rsfts(UCHAR*, INT, SHORT);
extern long double _packx(SHORT, UCHAR*);                      /* C S40001SP */
extern VOID   _unpack(long double, CHAR*, SHORT*, UCHAR*);
extern VOID   _calcnpw(SHORT, UCHAR*, INT, UCHAR*);
extern VOID   _calcint(UCHAR*, INT, INT);
extern long double _calcxpow(UCHAR*, INT, CHAR);   /* C S40001SP  C S40008SP */
extern int    _duchek(long double);                            /* C S40001SP */
extern int    _allzero(UCHAR*, INT);
extern VOID   _setsbit(UCHAR*, INT, INT);
extern int    _rnd(UCHAR*, INT);
extern INT    _strchek(CHAR*, CHAR*);
extern CHAR  *sbrk(int);
