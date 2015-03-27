/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003,2010 Renesas Technology Corporation and         */
/*                         Renesas Solutions Corporation              */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = log: double precision log function;                       */
/*   FUNC = Computes double precision logarithm of its argument;      */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define logf log                        /* rename logf to log         */
#include "logf.c"                       /* include logf               */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7ff00000             /* Exponent mask              */

/* -fpu=doubleópÇÃêîílÇí«â¡	A SH-B094129	*/
#if defined(_FPD)
#define LOGE2F (6.9314718246459961e-01)
#else
#define LOGE2F ((float)6.93147183e-01)
#endif
#define LOGE2R (-1.9046542999463095e-09)

static const double log_coeff[]={
  /* Cofficients                                                      */
  -1.7251585862816863e-01,
  -8.2052130894302747e-02,
  -1.2139433730154400e-01,
  -1.3296383670008179e-01,
  -1.5386944173477858e-01,
  -1.8181723868187515e-01,
  -2.2222224612074832e-01,
  -2.8571428535970736e-01,
  -4.0000000000267827e-01,
  -6.6666666666665945e-01,
  -2.0,
  /* Scaling value (adjust value and approximation)                   */
  LOGE2R,
  LOGE2F
};

static double poly_log(double f0, double n)
{
  double d1, d2, d4, a1, a2, c1, c2;
  double *p=log_coeff;
  d1=(1.0-f0)/(1.0+f0);
  d2=d1*d1;
  d4=d2*d2;
  a1=*p++;
  a2=*p++;
  a1=a1*d4;
  a2=a2*d4;
  c1=*p++;
  c2=*p++;
  a1=a1+c1;
  a2=a2+c2;
  a1=a1*d4;
  a2=a2*d4;
  c1=*p++;
  c2=*p++;
  a1=a1+c1;
  a2=a2+c2;
  a1=a1*d4;
  a2=a2*d4;
  c1=*p++;
  c2=*p++;
  a1=a1+c1;
  a2=a2+c2;
  a1=a1*d4;
  a2=a2*d4;
  c1=*p++;
  c2=*p++;
  a1=a1+c1;
  a2=a2+c2;
  a1=*p++ +a1*d4;
  a2=a2*d2;
  a1=(a1+a2)*d1;
  /* Scale the result                                                 */
  a1+=*p++ *n;
  a1+=*p++ *n;
  return a1;
}

extern double frexp(double, int *);

extern double __neginfd_value(void);
extern double __nand_value(void);
extern double __logd_special(unsigned long, unsigned long);

double log(double d0){
  double d1;
  int n;
#ifdef _BIG                             /* Big endian                 */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return __logd_special(*(unsigned long *)&d0,
                          *((unsigned long *)&d0+1));
#else                                   /* Little endian              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return __logd_special(*((unsigned long *)&d0+1),
                          *(unsigned long *)&d0);
#endif
  if (d0<=0.0)
    if (d0<0.0){                        /* FFPLB-024 (C)              */
	  _errno=EDOM;                      /* FFPLB-024 (A)              */
	  return __nand_value();
    }                                   /* FFPLB-024 (A)              */
    else{                               /* FFPLB-024 (C)              */
	  _errno=ERANGE;                    /* FFPLB-024 (A)              */
	  return __neginfd_value();
    }                                   /* FFPLB-024 (A)              */
  d0=frexp(d0, &n);                     /* n is integer part of       */
                                        /* log2(d0)                   */
  if (n>=1){                            /* Adjust to reduce relative  */
    n--;                                /* error near 1.0             */
	d0+=d0;
  }
  return poly_log(d0, n);
}
#endif
