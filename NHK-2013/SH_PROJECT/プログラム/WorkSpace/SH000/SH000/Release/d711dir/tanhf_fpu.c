/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = tanhf: single precision hyperbolic tangent function;      */
/*   FUNC = Computes single precision hyperbolic tangent of its       */
/*          argument;                                                 */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include <mathf.h>

#include "fperror.h"                    /* FFPLB-024 (A)              */

static const float tanhf_coeff[8]={1.212534350543e-04f,
                                   -8.402357930208e-04f,
                                   3.077065492107e-03f,
                                   -8.593754561389e-03f,
                                   2.178405480754e-02f,
                                   -5.395291451885e-02f,
                                   1.333319792609e-01f,
                                   -3.333332918749e-01f};
static float poly_tanhf(float d1)       /* FFPLB-047 (C)              */
{
  float ans, d2;
  float *p=tanhf_coeff;
  d2=d1*d1;
  ans=*p++;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=ans*d2;                           /* FFPLB-010 (C)              */
  ans=d1+ans*d1;                        /* FFPLB-010 (C)              */
  return ans;                           /* FFPLB-010 (C)              */
}

extern float __nanf_value(void);

#define EXP_MASK 0x7F800000             /* Mask of float exponent     */
#define SIGN_MASK 0x80000000            /* Mask of float sign         */
#define MANT_MASK 0x007FFFFF            /* Mask of float mantissa     */

static float tanhf_special(unsigned long v){
  if (v&MANT_MASK){                     /* Input is NaN               */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nanf_value();
  }
  else if (v&SIGN_MASK){                /* Input is -infinity         */
    return -1.0f;                       /* FFPLB-004 (C)              */
  }
  else                                  /* Input is +infinity         */
    return 1.0f;                        /* FFPLB-004 (C)              */
}

float expf(float);

float tanhf(float d0){
  float d1;
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return tanhf_special(*(unsigned long *)&d0);
  if (d0==0.0f)                         /* Handle +-0 case            */
    return d0;
  d1=fabsf(d0);
  if (d1<=1.0f)                         /* FFPLB-062 (C)              */
    return poly_tanhf(d0);
  if (d1<8.67f){                        /* FFPLB-016 (A)              */
    d0*=2.0f;
    d0=expf(d0);
    return (d0-1.0f)/(d0+1.0f);
  }                                     /* FFPLB-016 (A)              */
  if (d0>0.0f)                          /* FFPLB-016 (A)              */
    return 1.0f;                        /* FFPLB-016 (A)              */
  return -1.0f;                         /* FFPLB-016 (A)              */
}

#else                                   /* fpu=double                 */
#define tanh tanhf                      /* Renames tanh to tanhf      */
#include "tanh.c"                       /* Includes double tanh       */
#endif
