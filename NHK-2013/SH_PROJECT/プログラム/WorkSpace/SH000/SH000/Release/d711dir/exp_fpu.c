/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003,2010 Renesas Technology Corporation and         */
/*                         Renesas Solutions Corporation              */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = expf: double precision exponent function;                 */
/*   FUNC = Computes double precision exponent of its argument;       */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define expf exp                        /* rename expf to exp         */
#include "expf.c"                       /* include expf               */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7FF00000             /* Mask of double exponent    */
#define SIGN_MASK 0x80000000
#define MANT_MASK 0x000FFFFF

#define LOG2E 1.4426950408889634        /* log2(e)                    */
/* -fpu=double用の数値を追加	A SH-B094129	*/
#if defined(_FPD)
#define LOGE2F (6.9314718246459961e-01)
#else
#define LOGE2F ((float)6.93147183e-01)  /* Float approximation to     */
#endif									/* log(2)                     */
#define LOGE2R (-1.9046542999463095e-09)/* log(2)-(float)log(2)       */
#define LOGE2DIV2APPROX 0.34765625      /* 89/256, exact value near   */
                                        /* log(2)/2                   */

static const double exp_coeff_1[12]={   /* Coefficient for the range  */
                                        /* 0<=d0<=LOGE2DIV2APPROX     */
  3.2487391705136100E-07,
  2.7168268293695600e-06,
  2.4818340032571600e-05,
  1.9840837918529600e-04,
  1.3888895687529000e-03,
  8.3333332700550400e-03,
  4.1666666669811700e-02,
  1.6666666666660400e-01,
  5.0000000000000000e-01,
  1.0000000000000000e+00,
  /* Last 2 entries are the largest term divided into an              */
  /* approximation and adjusting value                                */
  0.0,
  1.0000000000000000e+00,
};

static const double exp_coeff_2[12]={   /* Coefficient for the range  */
                                        /* LOGE2DIV2APPROX<=d0<=log(2)*/
  4.5993878729213936e-07,
  3.8463353676541280e-06,
  3.5136453307146516e-05,
  2.8089577070189014e-04,
  1.9663141619150649e-03,
  1.1797879106817928e-02,
  5.8989395986472008e-02,
  2.3595758392798907e-01,
  7.0787275178423326e-01,
  1.4157455035684665e+00,
  /* Last 2 entries are the largest term divided into an adjusting    */
  /* value and an approximation                                       */
  6.8185886878142227e-09,
/* -fpu=double用の数値を追加	A SH-B094129	*/
#if defined(_FPD)
  1.4157454967498780e+00
#else
  (float)1.4157455
#endif
};

/*
 * 入力値がexp_underflowより小さい場合に'0'を返す処理を追加	A SH-B094059
 * exp_underflowは演算(d0*log2e)でINT_MIN+1となる値
 */
static const double exp_underflow = -1488522235.2166388;

extern double ldexp(double, int);

extern double __nand_value(void);
extern double __posinfd_value(void);

static const double exp_const_table[]={
  LOG2E,
  LOGE2F,
  LOGE2R,
  LOGE2DIV2APPROX
};

static double poly_exp(double f0, double *p){  /* FFPLB-044 (C)       */

  double d4;
  d4=*p++;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;
  d4=*p++ +d4*f0;                       /* Add adjusting value        */
  d4+=*p++;                             /* Add approximation          */
  return d4;
}

static double expd_special(unsigned long hi, unsigned long lo){
  /* It is known that the exponent part is maximum                    */
  if (hi&MANT_MASK || lo){              /* FFPLB-024 (C)              */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nand_value();
  }                                     /* FFPLB-024 (A)              */
  if (hi&SIGN_MASK)
    return 0.0;
  _errno=ERANGE;                        /* FFPLB-024 (A)              */
  return __posinfd_value();
}

double exp(double d0){
  int n;
  double *p=exp_const_table;
  double *q;
  double result;                        /* FFPLB-024 (A)              */
#ifdef _BIG                             /* Big endian                 */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return expd_special(*(unsigned long *)&d0, *((unsigned long *)&d0+1));
#else                                   /* Little endian              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return expd_special(*((unsigned long *)&d0+1), *(unsigned long *)&d0);
#endif
  /* 入力値がexp_underflowより小さい場合に'0'を返す処理を追加	A SH-B094059	*/
  if (d0 < exp_underflow ) { return(0.0); }
  n=d0* *p++;                           /* Get integer part of        */
                                        /* d0*log2(e)                 */
  if (d0<0.0)                           /* Integer parrt is round     */
    n--;                                /* toward -infinity           */
  d0+=-n* *p++;                         /* Get approximation of the   */
                                        /* remainder modulo ln 2      */
  d0+=-n* *p++;                         /* Adjust the remainder       */
  if (d0<=*p)                           /* Range1 (0<=d0<=89/256)     */
    q=exp_coeff_1;
  else{                                 /* Range2 (89/256<=d0<=log(2))*/
    q=exp_coeff_2;
    d0-=*p;
  }
  d0=poly_exp(d0, q);                   /* Compute exp(x mod log(2))  */
  if (n>0 && n<=30)                     /* Quick scaling              */
    return (1<<n)*d0;
  result=ldexp(d0, n);                  /* FFPLB-024 (C)              */
#ifdef _BIG                             /* FFPLB-024 (A)              */
  if ((*(unsigned long *)&result&EXP_MASK)==EXP_MASK) /* FFPLB-024 (A)*/
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
#else                                   /* FFPLB-024 (A)              */
  if ((*((unsigned long *)&result+1)&EXP_MASK)==EXP_MASK)
                                        /* FFPLB-024 (A)              */
	_errno=ERANGE;                      /* FFPLB-024 (A)              */
#endif                                  /* FFPLB-024 (A)              */
	return result;						/* FFPLB-049 (A)              */
}
#endif
