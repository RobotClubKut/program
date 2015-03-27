/********************************************************************************/
/* Copyright (C) 1992,2009 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = efflush : header file for standard I/O function ;           */
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

extern int    write(int, char*, unsigned);
extern int     fflush(FILE *);

/* A SH-B094066	*/
extern struct _iobuf _iob[];
extern const int _nfiles;
