/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = e_fmtou : header file for standard I/O function ;           */
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
#ifndef _REENTRANT                               /* A S70003P  */
extern volatile int         _errno;                      /* C S01002SP */
#else                                              /* A S70003P  */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P  */

extern size_t strlen(const char *);
#ifdef _FPS                                                    /* A S50005SP */
extern int    _xti(long double, INT, CHAR*, INT*, CHAR*);
#endif                                  /* ^^^  C S01001SP  C S40001SP */
extern VOID   _its(CHAR*, CHAR*, INT);
extern void *memcpy(void *, const void *, size_t);
                                                         /* D S01011SP */
extern int    _fmtout(int, int(*)(int, FILE *), FILE *, const char*, char*); /* C Svv00 SP */
