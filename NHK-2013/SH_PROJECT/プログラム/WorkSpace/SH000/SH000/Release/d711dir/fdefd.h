/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/**/
#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
typedef double IN_DOUBLE;				       /* A S50001SP */
#else							       /* A S50001SP */
typedef struct {                          /* inner format float  definition */
    unsigned long s_e;                     /*  sign bit(MSB)|exp(lower2bite) */
    unsigned long m_h;                    /*  mantisa(highter 32bit)        */
    unsigned long m_l;                    /*  mantisa(lower   32bit)        */
} IN_DOUBLE;				
#endif							       /* A S50001SP */

#ifndef _REENTRANT                              /* A S70003P */
extern volatile int _errno;
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* C S70001SP C */
#define _errno (*errno_addr())                     /* A S70001SP A */
extern const    double _HUGE_VAL;
#endif                                             /* A S70003P */

/* for exception error number */
#define ERANGE    1100
#define EDOM      1101
#define HUGE_VAL _HUGEVAL 

/* function '_istype' return value */ 
#define NEG  8
#define ZERO 4
#define INF  2
#define NAN  1 

#define EXMASKD   0x7ff00000
#define MHMASKD   0x000fffff
#define MLMASKD   0xffffffff

#define DBLMAX_HI 0x7fefffff                               /* A S90R400P */
#define DBLMAX_LO 0xffffffff                               /* A S90R400P */

#ifdef _LIT                                                /* A S30019SP */
#define isEMAXd(p) (((*((long*)&p+1))&EXMASKD)==EXMASKD)

#define isMANTd(p)  (((*((long*)&p+1))&MHMASKD) || \
                    ((*(long*)&p)&MLMASKD))
#else                                                          /* A S30019SP */
#define isEMAXd(p) (((*(long*)&p)&EXMASKD)==EXMASKD)

#define isMANTd(p)  (((*(long*)&p)&MHMASKD) || \
                    ((*((long*)&p+1))&MLMASKD))
#endif                                                         /* A S30019SP */

#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#ifdef _LIT					      /* C S50011SP vvv  C ^ */
#define d_EXP(p)  ((((*((long *)&p+1))&EXPMASK)>>20)-DBIAS)/* DBIAS:1023 C | */
#else								      /* C | */
#define d_EXP(p)  ((((*(long *)&p)&EXPMASK)>>20)-DBIAS)    /* DBIAS:1023 C | */
#endif								      /* C v */
#endif							       /* A S50001SP */

/* exp const define (outer format) */
#define SBIAS 127
#define DBIAS 1023

/* exp const define (inner format) */
#if defined(_SH4) | defined(_SH4A) | defined(_SH2AFPU)
#define EMAX 2047					       /* A S50001SP */
#define EMIN 1						       /* A S50001SP */
#define EXPMASK  0x7ff00000				       /* A S50001SP */
#else							       /* A S50001SP */
#define EMAX 32767
#define EMIN (-32767)
#define EXPMASK  0x0000ffff
#endif							       /* A S50001SP */
#define SIGNMASK 0x80000000
#define ABSMASK  0x7fffffff

