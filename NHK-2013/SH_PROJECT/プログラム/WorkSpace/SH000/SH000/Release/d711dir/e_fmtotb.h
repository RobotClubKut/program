/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = e_fmtotb : header file for _fmtout.c and _xtostr.c ;        */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) _fmtout and subroutines in _fmtout.c                    */
/*         (2) _xtostr in _xtostr.c                                    */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/

typedef struct fmtoutbl1{       /*                          C S40011SP */
    long _outkind;              /*                           ^         */
    char *_str;                 /*                           |         */
    long _outch;                /* output character count    |         */
    int (*_sofun)(int, FILE *); /*                           v         */
}_FMTOTBL1;                     /*                          C S40011SP */

typedef struct fmtoutbl2{       /*                          C S40011SP */
    char _fmtflg;               /* format analize flag       ^         */
    char _padchar;              /* pad character             |         */
    short _dummy;               /*                           |         */
    long _width;                /* field width               |         */
    long _prec;                 /*                           |         */
    long _parasize;             /* type of parameter         |         */
    char *_prec_addr0;          /* prec '0' insert address   |         */
    char *_prec_addr1;          /* prec '0' insert address   |         */
    char *_prec_addr2;          /* prec '0' insert address   |         */
    long _prec_ins0;            /* prec '0' char count       |         */
    long _prec_ins1;            /* prec '0' char count       |         */
    long _prec_ins2;            /* prec '0' char count       |         */
    long _parasize1;            /* long long type frag      A S70004 P */
    long _with_ins;             /* remain width char count   v         */
}_FMTOTBL2;                     /*                          C S40011SP */
