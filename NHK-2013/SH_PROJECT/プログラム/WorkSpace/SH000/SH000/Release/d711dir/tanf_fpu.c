/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = tanf: single precision tangent function;                  */
/*   FUNC = Computes single precision tangent of its argument;        */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include <mathf.h>                      /* FFPLB-010 (A)              */

#include "fperror.h"                    /* FFPLB-024 (A)              */

/* Tangent coefficient                                                */
static const float tanf_coeff[10]={     /* FFPLB-010 (C)              */
  2.8786672518e-08f,                    /* FFPLB-010 (C)              */
  2.1781327400e-03f,                    /* FFPLB-010 (C)              */
  -4.5435289044e-03f,                   /* FFPLB-010 (C)              */
  7.6766647601e-03f,                    /* FFPLB-010 (C)              */
  -5.4828660814e-04f,                   /* FFPLB-010 (C)              */
  1.0440148874e-02f,                    /* FFPLB-010 (C)              */
  2.1535777314e-02f,                    /* FFPLB-010 (C)              */
  5.4003575120e-02f,                    /* FFPLB-010 (C)              */
  1.3333188519e-01f,                    /* FFPLB-010 (C)              */
  0.3333333433f};                       /* FFPLB-010 (C)              */

/* Compute tan(d1)                                                    */
static float poly_tanf(float d1, float d2, float *p){/* FFPLB-010 (C) */
  float fr5, fr6, fr7, fr8, d4;         /* FFPLB-010 (C)              */
  d4=d2*d2;                             /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr6=*p++;                             /* FFPLB-010 (C)              */
  fr8=*p++;                             /* FFPLB-010 (C)              */
  fr6+=d4*fr5;                          /* FFPLB-010 (C)              */
  fr8+=d4*fr7;                          /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr5+=d4*fr6;                          /* FFPLB-010 (C)              */
  fr7+=d4*fr8;                          /* FFPLB-010 (C)              */
  fr6=*p++;                             /* FFPLB-010 (C)              */
  fr8=*p++;                             /* FFPLB-010 (C)              */
  fr6+=d4*fr5;                          /* FFPLB-010 (C)              */
  fr8+=d4*fr7;                          /* FFPLB-010 (C)              */
  fr5=*p++;                             /* FFPLB-010 (C)              */
  fr7=*p++;                             /* FFPLB-010 (C)              */
  fr5+=d4*fr6;                          /* FFPLB-010 (C)              */
  fr7+=d4*fr8;                          /* FFPLB-010 (C)              */
  fr5*=d4;                              /* FFPLB-010 (C)              */
  fr5+=d2*fr7;                          /* FFPLB-010 (C)              */
  d1+=d1*fr5;                           /* FFPLB-010 (C)              */
  return d1;                            /* FFPLB-010 (C)              */
}

/* Compute cot(d1)                                                    */
static float poly_cotf(float d1, float d2, float *p){/* FFPLB-010 (A) */
  float fr5, fr6, fr7, fr8, d4;         /* FFPLB-010 (A)              */
  d4=d2*d2;                             /* FFPLB-010 (A)              */
  fr5=*p++;                             /* FFPLB-010 (A)              */
  fr7=*p++;                             /* FFPLB-010 (A)              */
  fr6=*p++;                             /* FFPLB-010 (A)              */
  fr8=*p++;                             /* FFPLB-010 (A)              */
  fr6+=d4*fr5;                          /* FFPLB-010 (A)              */
  fr8+=d4*fr7;                          /* FFPLB-010 (A)              */
  fr5=*p++;                             /* FFPLB-010 (A)              */
  fr7=*p++;                             /* FFPLB-010 (A)              */
  fr5+=d4*fr6;                          /* FFPLB-010 (A)              */
  fr7+=d4*fr8;                          /* FFPLB-010 (A)              */
  fr6=*p++;                             /* FFPLB-010 (A)              */
  fr8=*p++;                             /* FFPLB-010 (A)              */
  fr6+=d4*fr5;                          /* FFPLB-010 (A)              */
  fr8+=d4*fr7;                          /* FFPLB-010 (A)              */
  fr5=*p++;                             /* FFPLB-010 (A)              */
  fr7=*p++;                             /* FFPLB-010 (A)              */
  fr5+=d4*fr6;                          /* FFPLB-010 (A)              */
  fr7+=d4*fr8;                          /* FFPLB-010 (A)              */
  fr5*=d4;                              /* FFPLB-010 (A)              */
  fr5+=d2*fr7;                          /* FFPLB-010 (A)              */
  d1+=d1*fr5;                           /* FFPLB-010 (A)              */
  if (d1==0.0f)                         /* FFPLB-024 (A)              */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
  return 1.0f/d1;                       /* FFPLB-010 (A)              */
}                                       /* FFPLB-010 (A)              */

extern float __nanf_value(void);        /* FFPLB-002 (C)              */

#define EXP_MASK 0x7F800000             /* Mask of float exponent     */

#define PI4APPROX -7.85398186e-01f		/* FFPLB-010 (A)              */
#define PI4ADJUST 2.185569591973e-08f	/* FFPLB-010 (A)              */

static const float const_tbl[3]={       /* FFPLB-010 (A)              */
  1.2732395f,                           /* FFPLB-010 (A)              */
                                        /* Approx. 4/pi               */
  PI4APPROX,                            /* FFPLB-010 (A)              */
  PI4ADJUST};                           /* FFPLB-010 (A)              */

static float in_tanf(float d0){         /* FFPLB-010 (A)              */
  float d1=fabsf(d0);                   /* FFPLB-010 (A)              */
  float *p=const_tbl;                   /* FFPLB-010 (A)              */
  float tmp=*p++;                       /* FFPLB-010 (A)              */
  long ipart;                           /* FFPLB-010 (A)              */
  ipart=tmp*d1;                         /* FFPLB-016 (C)              */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK){ /* FFPLB-024 (C)   */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
                                        /* Check NaN or Infinity      */
    return __nanf_value();              /* FFPLB-010 (A)              */
  }                                     /* FFPLB-024 (A)              */
  if (ipart&1)                          /* FFPLB-010 (A)              */
    ipart++;                            /* FFPLB-010 (A)              */
  tmp=*p++;                             /* FFPLB-010 (A)              */
  d1+=tmp*ipart;                        /* FFPLB-016 (C)              */
  tmp=*p++;                             /* FFPLB-010 (A)              */
  d1+=tmp*ipart;                        /* FFPLB-016 (C)              */
  if (d0>0.0f)                                           /* C S91093P */
    if (ipart&2)                        /* FFPLB-010 (A)              */
      return poly_cotf(-d1, d1*d1, tanf_coeff); /* FFPLB-016 (C)      */
    else                                /* FFPLB-010 (A)              */
      return poly_tanf(d1, d1*d1, tanf_coeff); /* FFPLB-016 (C)       */
  if (ipart&2)                          /* FFPLB-016 (A)              */
    return poly_cotf(d1, d1*d1, tanf_coeff); /* FFPLB-016 (A)         */
  else                                  /* FFPLB-016 (A)              */
    return poly_tanf(-d1, d1*d1, tanf_coeff); /* FFPLB-016 (A)        */
}                                       /* FFPLB-010 (A)              */

float tanf(float d0){
  float d1=fabsf(d0);                   /* FFPLB-010 (C)              */
  if (d1<1.0f)                          /* FFPLB-027 (C)              */
    return poly_tanf(d0, d0*d0, tanf_coeff); /* FFPLB-010 (C)         */
  else
    return in_tanf(d0);                 /* FFPLB-010 (C)              */
}

#else                                   /* fpu=double                 */
#define tan tanf                        /* Renames tan to tanf        */
#include "tan.c"                        /* Includes double tangent    */
#endif
