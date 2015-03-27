/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = evprint : header file for standard I/O function ;           */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/


extern struct _iobuf   _iob[];                     /* C S70001SP */

extern int    _fmtout(int, int (*)(int, FILE *), FILE*, const char*, char*); /* C S0100 SP */
extern int     vprintf(const char *, char *);
extern int     fputc(int , FILE *);
