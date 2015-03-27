/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = e_fmtin : header file for standard I/O function ;           */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/


extern unsigned char _ctype[];
#ifndef _REENTRANT                              /* A S70003P  */
extern volatile int         _errno;                      /* C S01002SP */
#else
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif
                                                         /* D S01011SP */
extern int    _fmtin(int, int(*)(FILE *), FILE *, const char*, char*);
                                                         /* C S01001SP */
extern float  _stf(INT, CHAR*, INT, CHAR);        /* C S40008SP  C S40013SP */
extern long double _stx(INT, CHAR*, INT, CHAR);
                                      /* C S40001SP  C S40008SP  C S40013SP */
#ifdef _DSPC
extern VOID _stlar(INT, CHAR*, CHAR*, CHAR, CHAR, void*);   /* A V80#4.17 */
#endif /* _DSPC */
extern const float       _FLT_MAX_VAL;
extern const float       _FLT_MIN_VAL;
extern const double      _DBL_MAX_VAL;
extern const double      _DBL_MIN_VAL;
