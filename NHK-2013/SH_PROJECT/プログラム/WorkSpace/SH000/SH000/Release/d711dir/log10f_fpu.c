/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = log10f: single precision log10 function;                  */
/*   FUNC = Computes single precision log10 of its argument;          */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7F800000             /* Mask of float exponent     */

#define LOG102 ((float)((int)(0.301029995664f*1024)/1024.0f))
                                        /* FFPLB-010 (C)              */
#define LOG102ERR 2.4874566400e-04f     /* FFPLB-010 (C)              */

static const float log10_coeff_l[13]={  /* FFPLB-010 (C)              */
  9.5447807078e-01f,                    /* FFPLB-010 (C)              */
  1.6086331912e+00f,                    /* FFPLB-010 (C)              */
  1.4112199459e+00f,                    /* FFPLB-010 (C)              */
  5.8662451446e-01f,                    /* FFPLB-010 (C)              */
  2.4613714518e-01f,                    /* FFPLB-010 (C)              */
  -3.9794210058e-02f,                   /* FFPLB-010 (C)              */
  9.0281919981e-02f,                    /* FFPLB-010 (C)              */
  -1.0838160025e-01f,                   /* FFPLB-010 (C)              */
  1.4476914784e-01f,                    /* FFPLB-010 (C)              */
  -2.1714724095e-01f,                   /* FFPLB-010 (C)              */
  0.4342944921f,                        /* FFPLB-010 (C)              */
  LOG102ERR,                            /* FFPLB-010 (C)              */
  LOG102};                              /* FFPLB-010 (C)              */

static const float log10_coeff_r[13]={  /* FFPLB-010 (C)              */
  9.3895484784e-04f,                    /* FFPLB-010 (C)              */
  -6.1259358149e-03f,                   /* FFPLB-010 (C)              */
  1.8702611695e-02f,                    /* FFPLB-010 (C)              */
  -3.6681288090e-02f,                   /* FFPLB-010 (C)              */
  5.4618558327e-02f,                    /* FFPLB-010 (C)              */
  -7.0285212375e-02f,                   /* FFPLB-010 (C)              */
  8.6489470699e-02f,                    /* FFPLB-010 (C)              */
  -1.0853781550e-01f,                   /* FFPLB-010 (C)              */
  1.4476341119e-01f,                    /* FFPLB-010 (C)              */
  -2.1714724095e-01f,                   /* FFPLB-010 (C)              */
  0.4342944921f,                        /* FFPLB-010 (C)              */
  LOG102ERR,                            /* FFPLB-010 (C)              */
  LOG102};                              /* FFPLB-010 (C)              */

static float poly_log10f(float d1, float n, float *p){ /* FFPLB-010(C)*/
  float ans, m;                         /* FFPLB-010 (C)              */
  ans=*p++;                             /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=*p++ +ans*d1;                     /* FFPLB-010 (C)              */
  ans=ans*d1;                           /* FFPLB-010 (C)              */
  m=*p++; ans+=n*m;                     /* FFPLB-010 (C)              */
  m=*p++; ans+=n*m;                     /* FFPLB-010 (C)              */
  return ans;                           /* FFPLB-010 (C)              */
}

extern float frexpf(float, int *);

static float in_log10f(float d0){       /* FFPLB-010 (A)              */
  int n;                                /* FFPLB-010 (A)              */
  d0=frexpf(d0, &n);                    /* FFPLB-010 (A)              */
  return poly_log10f(d0-1.0f, (float)n, log10_coeff_l); /*FFPLB-010(A)*/
}                                       /* FFPLB-010 (A)              */

extern float __nanf_value(void);
extern float __neginff_value(void);
extern float __logf_special(unsigned long);

float log10f(float d0){
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
    return in_log10f(d0);               /* FFPLB-010 (C)              */
  n-=126;
  lval=(lval&0x807fffff)|0x3f000000;    /* FFPLB-010 (C)              */
  d0=*(float *)&lval;                   /* FFPLB-010 (C)              */
  if (n>=1){                            /* FFPLB-010 (C)              */
    n--;                                /* FFPLB-010 (C)              */
	d0+=d0;                             /* FFPLB-010 (C)              */
	return poly_log10f(d0-1.0f, (float)n, log10_coeff_r);
	                                    /* FFPLB-010 (C)              */
  }                                     /* FFPLB-010 (C)              */
  else                                  /* FFPLB-010 (C)              */
    return poly_log10f(d0-1.0f, (float)n, log10_coeff_l);
	                                    /* FFPLB-010 (C)              */
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
#define log10 log10f                    /* Renames log10 to log10f    */
#include "log10.c"                      /* Includes double log10      */
#endif
