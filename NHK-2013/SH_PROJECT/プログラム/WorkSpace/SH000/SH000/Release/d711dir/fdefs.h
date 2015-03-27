/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
typedef float IN_SINGLE;                                      /* A S40012SP */
#else
typedef struct {                          /* inner format float  definition */
    unsigned long s_e;                    /*  sign bit(MSB)|exp(lower2bite) */
    unsigned long m;                      /*  mantisa(highter 32bit)        */
} IN_SINGLE;				
#endif

#ifndef _REENTRANT                              /* A S70003P */
extern volatile int _errno;
#else                                              /* A S70003P */
extern  int *errno_addr(void);                     /* C S70001SP */
#define _errno (*errno_addr())                     /* A S70001SP */
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

#define EXMASKF   0x7f800000
#define MMASKF    0x007fffff
#define FLTMAX    0x7f7fffff                                  /* A S90R400P */

#define isEMAXf(p) (((*(long*)&p)&EXMASKF)==EXMASKF)

#define isMANTf(p)  ((*(long*)&p)&MMASKF)

/* exp const define (outer format) */
#define SBIAS 127
#define DBIAS 1023

/* exp const define (inner format) */
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define EMAX 255                                              /* A S40012SP */
#define EMIN 1                                                /* A S40012SP */
#else
#define EMAX 32767
#define EMIN (-32767)
#endif
#define SIGNMASK 0x80000000
#define ABSMASK  0x7fffffff
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define EXPMASK  0x7f800000                                   /* A S40012SP */
#else
#define EXPMASK  0x0000ffff
#endif
#if defined(_SH2E)|defined(_SH3E)|defined(_SH4)|defined(_SH4A)|defined(_SH2AFPU)
#define f_EXP(p)  ((((*(long *)&(p))&EXPMASK)>>23)-SBIAS)     /* A S40012SP */
#endif

