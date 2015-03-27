/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = sinh: double precision hyperbolic sine function;          */
/*   FUNC = Computes double precision hyperbolic sine of its argument;*/
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define sinhf sinh                      /* rename sinhf to sinh       */
#include "sinhf.c"                      /* include sinhf              */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

#define EXP_MASK 0x7ff00000             /* FFPLB-024 (A)              */
#define MANT_MASK 0x000fffff            /* FFPLB-024 (A)              */

static const double sinh_coeff[7]={     /* FFPLB-008 (C)              */
  7.7733359952114436e-13,               /* FFPLB-008 (C)              */
  1.6056762054651540e-10,               /* FFPLB-008 (C)              */
  2.5052129776795709e-08,               /* FFPLB-008 (C)              */
  2.7557319113471159e-06,               /* FFPLB-008 (C)              */
  1.9841269841576806e-04,               /* FFPLB-008 (C)              */
  8.3333333333329258e-03,               /* FFPLB-008 (C)              */
  1.6666666666666669e-01};              /* FFPLB-008 (C)              */

static double poly_sinh(double d1)
{
  double d2, d4;
  double *p=sinh_coeff;
  d2=d1*d1;
  d4=*p++;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;                       /* FFPLB-008 (A)              */
  d4=d4*d2;                             /* FFPLB-008 (C)              */
  d1=d1+d4*d1;                          /* FFPLB-008 (C)              */
  return d1;                            /* FFPLB-008 (C)              */
}

double exp(double);

double sinh(double d0){
  double d1;
  double result;                        /* FFPLB-024 (A)              */
  d1=d0;
  if (d0<0.0)
    d1=-d0;
  if (d0==0.0)                          /* Handle +-0 case            */
    return d0;
  if (d1<1.0f)                          /* FFPLB-032 (C)              */
    return poly_sinh(d0); 
  d1=exp(d0);
  result=0.5*(d1-1.0/d1);               /* FFPLB-024 (C)              */
#ifdef _BIG                             /* FFPLB-024 (A)              */
  if ((*(unsigned long *)&result&EXP_MASK)==EXP_MASK) /*FFPLB-024 (A) */
                                        /* FFPLB-024 (A)              */
    if ((*(unsigned long *)&result&MANT_MASK)!=0 || /* FFPLB-024 (A)  */
	    *((unsigned long *)&result+1)!=0)   /* FFPLB-024 (A)          */
	  _errno=EDOM;                      /* FFPLB-024 (A)              */
    else                                /* FFPLB-024 (A)              */
	  _errno=ERANGE;                    /* FFPLB-024 (A)              */
#else                                   /* FFPLB-024 (A)              */
  if ((*((unsigned long *)&result+1)&EXP_MASK)==EXP_MASK)
                                        /* FFPLB-024 (A)              */
    if ((*((unsigned long *)&result+1)&MANT_MASK)!=0 || /*FFPLB-024(A)*/
	    *(unsigned long *)&result!=0)   /* FFPLB-024 (A)              */
      _errno=EDOM;                      /* FFPLB-024 (A)              */
    else                                /* FFPLB-024 (A)              */
	  _errno=ERANGE;                    /* FFPLB-024 (A)              */
#endif                                  /* FFPLB-024 (A)              */
  return result;                        /* FFPLB-024 (A)              */
}
#endif
