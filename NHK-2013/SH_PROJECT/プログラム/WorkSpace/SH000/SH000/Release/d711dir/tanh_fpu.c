/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = tanh: double precision hyperbolic tangent function;       */
/*   FUNC = Computes double precision hyperbolic tangent of its       */
/*          argument;                                                 */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define tanhf tanh                      /* rename tanhf to tanh       */
#include "tanhf.c"                      /* include tanhf              */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

static const double tanh_coeff[9]={-1.7423037008360973e-04,
                                   5.6927834209655422e-04,
                                   -1.4520428860553328e-03,
                                   3.5917036098426056e-03,
                                   -8.8632058894124369e-03,
                                   2.1869487267682207e-02,
                                   -5.3968253936818356e-02,
                                   1.3333333333293168e-01,
                                   -3.3333333333333126e-01};

static double poly_tanh(double d1)      /* FFPLB-046 (C)              */
{
  double d2, d4;
  double *p=tanh_coeff;
  d2=d1*d1;
  d4=*p++;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=d4*d2;                             /* FFPLB-008 (A)              */
  d4=d1+d4*d1;                          /* FFPLB-008 (A)              */
  return d4;
}

extern double __nand_value(void);

#define EXP_MASK 0x7FF00000             /* Mask of double exponent    */
#define SIGN_MASK 0x80000000            /* Mask of double sign        */
#define MANT_MASK 0x000FFFFF            /* Mask of double mantissa    */

static double tanh_special(unsigned long hi, unsigned long lo){
  if (hi&MANT_MASK || lo){              /* Input is NaN               */
    _errno=EDOM;                        /* FFPLB024 (A)               */
    return __nand_value();
  }
  else if (hi&SIGN_MASK){               /* Input is -infinity         */
    return -1.0;                        /* FFPLB-004 (C)              */
  }
  else                                  /* Input is +infinity         */
    return 1.0;                         /* FFPLB-004 (C)              */
}

double exp(double);

double tanh(double d0){
  double d1=d0;
#ifdef _BIG                             /* Big endian                 */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return tanh_special(*(unsigned long *)&d0,
                        *((unsigned long *)&d0+1));
#else                                   /* Little endian              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return tanh_special(*((unsigned long *)&d0+1),
                        *(unsigned long *)&d0);
#endif
  if (d0<0.0)
    d1=-d0;
  if (d0==0.0)                          /* Handle +-0 case            */
    return d0;
  if (d1<=0.4)
    return poly_tanh(d0);
  if (d1<18.72){                        /* FFPLB-016 (C)              */
    d0*=2.0;
    d0=exp(d0);
    return (d0-1.0)/(d0+1.0);
  }                                     /* FFPLB-016 (C)              */
  if (d0>0.0)                           /* FFPLB-016 (C)              */
    return 1.0;                         /* FFPLB-016 (C)              */
  return -1.0;                          /* FFPLB-016 (C)              */
}
#endif
