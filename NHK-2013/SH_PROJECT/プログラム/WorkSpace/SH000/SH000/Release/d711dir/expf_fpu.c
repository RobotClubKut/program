/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = expf: single precision exponent function;                 */
/*   FUNC = Computes single precision exponent of its argument;       */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7F800000             /* Mask of float exponent     */
#define SIGN_MASK 0x80000000
#define MANT_MASK 0x007FFFFF

extern float ldexpf(float, int);

extern float __nanf_value(void);        /* FFPLB-002 (C)              */
extern float __posinff_value(void);     /* FFPLB-002 (C)              */

/* Coefficient for exp                                                */
static const float expf_coeff[6]={      /* FFPLB-010 (C)              */
  2.68729298e-04f,                      /* FFPLB-010 (C)              */
  1.32036391e-03f,                      /* FFPLB-010 (C)              */
  8.36447889e-03f,                      /* FFPLB-010 (C)              */
  4.16600203e-02f,                      /* FFPLB-010 (C)              */
  1.66667195e-01f,                      /* FFPLB-010 (C)              */
  5.00000000e-01f};                     /* FFPLB-010 (C)              */

static float poly_expf(float d1){       /* Conversion range:          */
                                        /* 0<=d1<=0.5                 */
  float *p=expf_coeff;                  /* FFPLB-010 (C)              */
  float ans;
  ans=*p++;
  ans=*p++ +ans*d1;
  ans=*p++ +ans*d1;
  ans=*p++ +ans*d1;
  ans=*p++ +ans*d1;
  ans=*p++ +ans*d1;
  ans=1.0f+ans*d1;                      /* FFPLB-010 (C)              */
  ans=1.0f+ans*d1;                      /* FFPLB-010 (C)              */
  return ans;                           /* FFPLB-010 (C)              */
}

static float poly_expf_scaled(float d1, float scale){/* FFPLB-010 (A) */
  float *p=expf_coeff;                  /* FFPLB-010 (A)              */
  float ans, d2=d1*scale;               /* FFPLB-010 (A)              */
  ans=*p++;                             /* FFPLB-010 (A)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (A)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (A)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (A)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (A)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (A)              */
  ans=1.0f +ans*d1;                     /* FFPLB-010 (A)              */
  scale=scale+ans*d2;                   /* FFPLB-010 (A)              */
  return scale;                         /* FFPLB-010 (A)              */
}                                       /* FFPLB-010 (A)              */

static float expf_r(float d0){          /* FFPLB-010 (A)              */
  extern float expf(float);             /* FFPLB-010 (A)              */
  return 1.0f/expf(-d0);                                 /* C S91093P */
}                                       /* FFPLB-010 (A)              */

static float expf_large(float d0, int n){ /* FFPLB-010 (A)            */
  float result;                         /* FFPLB-024 (A)              */
  d0=poly_expf(d0);                     /* FFPLB-010 (A)              */
  result=ldexpf(d0, n);                 /* FFPLB-010 (A)              */
  if ((*(unsigned *)&result&EXP_MASK)==EXP_MASK) /* FFPLB-024 (A)     */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
  return result;                        /* FFPLB-024 (A)              */
}                                       /* FFPLB-010 (A)              */

#define LOG2E 1.442695f                 /* FFPLB-010 (A)              */
#define LOGE2 0.69314718f               /* FFPLB-010 (A)              */
#define LOGE2APPROX ((float)((int)(LOGE2*1024)/1024.0f))/*FFPLB-010(A)*/
#define LOGE2ADJUST 7.643699645996e-04f /* FFPLB-010 (A)              */

static const float const_tbl[4]={       /* FFPLB-010 (A)              */
  0.7f,                                 /* FFPLB-010 (A)              */
  LOG2E,                                /* FFPLB-010 (A)              */
  LOGE2APPROX,                          /* FFPLB-010 (A)              */
  LOGE2ADJUST                           /* FFPLB-010 (A)              */
};

static float expf_special(unsigned long l){
  /* It is known that the exponent part is maximum                    */
  if (l&MANT_MASK){                     /* FFPLB-024 (C)              */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nanf_value();
  }                                     /* FFPLB-024 (A)              */
  if (l&SIGN_MASK)
    return 0.0f;
  _errno=ERANGE;                        /* FFPLB-024 (A)              */
  return __posinff_value();
}

float expf(float d0){
  unsigned long lval;
  int n;                                /* FFPLB-010 (A)              */
  float *p=const_tbl;                   /* FFPLB-010 (A)              */
  lval=*(unsigned long *)&d0;
  if ((lval&EXP_MASK)==EXP_MASK)
                                        /* Check NaN or Infinity      */
    return expf_special(lval);          /* Handle special cases       */
  if (d0<0.0f)                          /* FFPLB-010 (C)              */
    return expf_r(d0);                  /* FFPLB-010 (C)              */
  if (d0<=*p++)                         /* FFPLB-010 (C)              */
    return poly_expf(d0);               /* FFPLB-010 (C)              */
  n=d0* *p++;                           /* FFPLB-010 (C)              */
  d0+=-n* *p++;                         /* FFPLB-010 (C)              */
  d0+=-n* *p++;                         /* FFPLB-010 (C)              */
  if (n>=30)                            /* FFPLB-010 (C)              */
    return expf_large(d0, n);           /* FFPLB-010 (C)              */
  return poly_expf_scaled(d0, (float)(1<<n)); /* FFPLB-010 (C)        */
}

#else                                   /* fpu=double                 */
#define exp expf                        /* Renames exp to expf        */
#include "exp.c"                        /* Includes double exp        */
#endif
