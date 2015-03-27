/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = sinhf: single precision hyperbolic sine function;         */
/*   FUNC = Computes single precision hyperbolic sine of its argument;*/
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include <mathf.h>

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7f800000             /* FFPLB-024 (A)              */
#define MANT_MASK 0x007fffff            /* FFPLB-024 (A)              */

static const float sinh_coeff[5]={      /* FFPLB-010 (C)              */
  2.697160195186e-08f,                  /* FFPLB-010 (C)              */
  2.747435008221e-06f,                  /* FFPLB-010 (C)              */
  1.984287826098e-04f,                  /* FFPLB-010 (C)              */
  8.333319870210e-03f,                  /* FFPLB-010 (C)              */
  1.666666702842e-01f};                 /* FFPLB-010 (C)              */

static float poly_sinhf(float d1)
{
  float *p=sinh_coeff;
  float d2;
  float ans;
  d2=d1*d1;
  ans=*p++;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=*p++ +ans*d2;
  ans=     +ans*d2;                     /* FFPLB-010 (C)              */
  ans=d1+ans*d1;                        /* FFPLB-010 (C)              */
  return ans;
}

float expf(float);

float sinhf(float d0){
  float d1=fabsf(d0);
  float result;                         /* FFPLB-024 (A)              */
  if (d0==0.0f)                         /* Handle +-0 case            */
    return d0;
  if (d1<2.0f)                          /* FFPBL-029 (C)              */
    return poly_sinhf(d0); 
  d1=expf(d0);
  result=0.5f*(d1-1.0f/d1);             /* FFPLB-024 (C)              */
  if ((*(unsigned long *)&result&EXP_MASK)==EXP_MASK) /* FFPLB-024 (A)*/
    if ((*(unsigned long *)&result&MANT_MASK)==0) /* FFPLB-024 (A)    */
	  _errno=ERANGE;                    /* FFPLB-024 (A)              */
    else                                /* FFPLB-024 (A)              */
	  _errno=EDOM;                      /* FFPLB-024 (A)              */
  return result;                        /* FFPLB-024 (A)              */
}

#else                                   /* fpu=double                 */
#define sinh sinhf                      /* Renames sinh to sinhf      */
#include "sinh.c"                       /* Includes double sinh       */
#endif
