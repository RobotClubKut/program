/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = efread : header file for standard I/O function ;            */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/

#ifndef _REENTRANT                              /* A S70003P */
extern volatile int         _errno;                      /* C S01002SP */
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* A S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
#endif                                             /* A S70003P */

extern void   _alocbuf(FILE*);
extern void *memcpy(void *, const void *, size_t);
extern int    read(int, char*, unsigned);
extern size_t  fread(void *, size_t, size_t, FILE *);
