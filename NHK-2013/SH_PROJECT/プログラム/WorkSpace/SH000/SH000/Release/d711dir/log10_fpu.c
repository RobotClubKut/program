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
#define log10f log10                    /* FFPLB-045 (C)              */
#include "log10f.c"                     /* FFPLB-045 (C)              */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7ff00000             /* Exponent mask              */

/* -fpu=doubleópÇÃêîílÇí«â¡	A SH-B094129	*/
#if defined(_FPD)
#define LOG102F (3.0103000998497010e-01)
#else
#define LOG102F ((float)3.01030010e-1)
#endif
#define LOG102R (-1.4320988897547791e-08)

static const double log_coeff[]={
  /* Cofficients                                                      */
  -7.4922685443015130e-02,
  -3.5634787675799015e-02,
  -5.2720890824362649e-02,
  -5.7745460571530600e-02,
  -6.6824649478948258e-02,
  -7.8962223474424845e-02,
  -9.6509895246387305e-02,
  -1.2408413753265196e-01,
  -1.7371779276246389e-01,
  -2.8952965460216475e-01,
  -8.6858896380650366e-01,
  /* Scaling value (adjust value and approximation)                   */
  LOG102R,
  LOG102F
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

double log10(double d0){
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
