/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = logf: single precision log function;                      */
/*   FUNC = Computes single precision logarithm of its argument;      */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7F800000             /* Mask of float exponent     */

#define LOGE2 ((float)((int)(0.69314f*1024)/1024.0f))
                                        /* FFPLB-010 (C)              */
#define LOGE2ERR 7.64368044e-04f        /* FFPLB-010 (C)              */

static const float log_coeff_l[12]={    /* FFPLB-010 (C)              */
  2.1977669774e+00f,                    /* FFPLB-010 (C)              */
  3.7040148061e+00f,                    /* FFPLB-010 (C)              */
  3.2494540103e+00f,                    /* FFPLB-010 (C)              */
  1.3507528622e+00f,                    /* FFPLB-010 (C)              */
  5.6675172132e-01f,                    /* FFPLB-010 (C)              */
  -9.1629554867e-02f,                   /* FFPLB-010 (C)              */
  2.0788180312e-01f,                    /* FFPLB-010 (C)              */
  -2.4955785709e-01f,                   /* FFPLB-010 (C)              */
  3.3334328173e-01f,                    /* FFPLB-010 (C)              */
  -0.5f,                                /* FFPLB-010 (C)              */
  LOGE2ERR,                             /* FFPLB-010 (C)              */
  LOGE2};                               /* FFPLB-010 (C)              */


static const float log_coeff_r[12]={    /* FFPLB-010 (C)              */
  2.1620234356e-03f,                    /* FFPLB-010 (C)              */
  -1.4105488488e-02f,                   /* FFPLB-010 (C)              */
  4.3064354890e-02f,                    /* FFPLB-010 (C)              */
  -8.4461787148e-02f,                   /* FFPLB-010 (C)              */
  1.2576387820e-01f,                    /* FFPLB-010 (C)              */
  -1.6183768227e-01f,                   /* FFPLB-010 (C)              */
  1.9914936593e-01f,                    /* FFPLB-010 (C)              */
  -2.4991755600e-01f,                   /* FFPLB-010 (C)              */
  3.3333007262e-01f,                    /* FFPLB-010 (C)              */
  -0.5f,                                /* FFPLB-010 (C)              */
  LOGE2ERR,                             /* FFPLB-010 (C)              */
  LOGE2};                               /* FFPLB-010 (C)              */

static float poly_logf(float d1, float d2, float n, float *p){
                                        /* FFPLB-010 (C)              */
  float fr5, fr6, fr7, fr8;             /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr6=*p++;                             /* FFPLB-010 (C)              */
  fr8=*p++;                             /* FFPLB-010 (C)              */
  fr6+=d2*fr5;                          /* FFPLB-010 (C)              */
  fr8+=d2*fr7;                          /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr5+=d2*fr6;                          /* FFPLB-010 (C)              */
  fr7+=d2*fr8;                          /* FFPLB-010 (C)              */
  fr6=*p++;                             /* FFPLB-010 (C)              */
  fr8=*p++;                             /* FFPLB-010 (C)              */
  fr6+=d2*fr5;                          /* FFPLB-010 (C)              */
  fr8+=d2*fr7;                          /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr5+=d2*fr6;                          /* FFPLB-010 (C)              */
  fr7+=d2*fr8;                          /* FFPLB-010 (C)              */
  fr5*=d2;                              /* FFPLB-010 (C)              */
  fr5+=d1*fr7;                          /* FFPLB-010 (C)              */
  d1+=d1*fr5;                           /* FFPLB-010 (C)              */
  d1+=n* *p++;                          /* FFPLB-010 (C)              */
  d1+=n* *p++;                          /* FFPLB-010 (C)              */
  return d1;                            /* FFPLB-010 (C)              */
}

extern float frexpf(float, int *);

static float in_logf(float d0){         /* FFPLB-010 (A)              */
  int n;                                /* FFPLB-010 (A)              */
  unsigned u0;                          /* FFPLB-010 (A)              */
  d0=frexpf(d0, &n);                    /* FFPLB-010 (A)              */
  d0-=1.0f;                             /* FFPLB-010 (A)              */
  return poly_logf(d0, d0*d0, (float)n, log_coeff_l);/* FFPLB-010 (A) */
}                                       /* FFPLB-010 (A)              */

extern float __nanf_value(void);
extern float __neginff_value(void);
extern float __logf_special(unsigned long);

float logf(float d0){
  float d1;
  unsigned long lval;
  int n;
  lval=*(unsigned long *)&d0;
  if ((lval&EXP_MASK)==EXP_MASK)
    goto special;
  if (d0<=0.0f)
    goto negative;
  n=lval>>23;                           /* FFPLB-010 (C)              */
  if (n==0)                             /* FFPLB-010 (C)              */
    return in_logf(d0);                 /* FFPLB-010 (C)              */
  n-=126;                               /* FFPLB-010 (C)              */
  lval=(lval&0x807fffff)|0x3f000000;    /* FFPLB-010 (C)              */
  d0=*(float *)&lval;                   /* FFPLB-010 (C)              */
  if (n>=1){                            /* FFPLB-010 (C)              */
    n--;                                /* FFPLB-010 (C)              */
	d0+=d0;                             /* FFPLB-010 (C)              */
	d0-=1.0f;                           /* FFPLB-010 (C)              */
	return poly_logf(d0, d0*d0, (float)n, log_coeff_r);/* FFPLB-010(C)*/
  }                                     /* FFPLB-010 (C)              */
  d0-=1.0f;                             /* FFPLB-010 (C)              */
  return poly_logf(d0, d0*d0, (float)n, log_coeff_l);/* FFPLB-010 (C) */
special:
  return __logf_special(lval);          /* NaN or infinity            */
negative:
  if (d0<0.0f){                         /* FFPLB-024 (C)              */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nanf_value();              /* Negative                   */
  }                                     /* FFPLB-024 (A)              */
  else{                                 /* FFPLB-024 (C)              */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
    return __neginff_value();           /* Zero                       */
  }                                     /* FFPLB-024 (A)              */
}

#else                                   /* fpu=double                 */
#define log logf                        /* Renames log to logf        */
#include "log.c"                        /* Includes double log        */
#endif
