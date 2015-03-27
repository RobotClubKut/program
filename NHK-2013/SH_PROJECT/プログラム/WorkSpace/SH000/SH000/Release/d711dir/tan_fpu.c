/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = tan: double precision tangent function;                   */
/*   FUNC = Computes double precision tangent of its argument;        */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define tanf tan                        /* rename tanf to tan         */
#include "tanf.c"                       /* include tanf               */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

/* Tangent coefficient                                                */
static const double tand_coeff[9]={     /* FFPLB-008 (C)              */
  3.3291520645622161e-04,               /* FFPLB-008 (C)              */
  5.5633804891445423e-04,               /* FFPLB-008 (C)              */
  1.4623182422118224e-03,               /* FFPLB-008 (C)              */
  3.5913850974346428e-03,               /* FFPLB-008 (C)              */
  8.8632876766702996e-03,               /* FFPLB-008 (C)              */
  2.1869486331432180e-02,               /* FFPLB-008 (C)              */
  5.3968254020954159e-02,               /* FFPLB-008 (C)              */
  1.3333333333271455e-01,               /* FFPLB-008 (C)              */
  3.3333333333333585e-01};              /* FFPLB-008 (C)              */

/* Compute tan(f0)                                                    */
static double poly_tan(double f0)       /* Conversion range:          */
                                        /* -pi/8-eps~pi/8+eps         */
{
  double d2,d4;
  double *p=tand_coeff;
  d2=f0*f0;
  d4=*p++;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=*p++ +d4*d2;
  d4=d4*d2;                             /* FFPLB-008 (C)              */
  f0=f0+d4*f0;                          /* FFPLB-008 (C)              */
  return f0;                            /* FFPLB-008 (C)              */
}

/* Compute 1/tan(-f0)                                                 */
static double poly_tan_r(double f0){
  double tmp=poly_tan(-f0);             /* FFPLB-024 (A)              */
  if (tmp==0.0)                         /* FFPLB-024 (A)              */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
  return 1.0/tmp;                       /* FFPLB-024 (C)              */
}

/* Compute tan(pi/4+f0)=(1+tan(f0))/(1-tan(f0))                       */
static double poly_tan1(double f0){
  double d=poly_tan(f0);
  if (d==1.0)                           /* FFPLB-024 (A)              */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
  return (1+d)/(1-d);
}

/* Compute tan(3pi/4+f0)=(1+tan(f0))/(1-tan(f0))                      */
static double poly_tan2(double f0){
  double d=poly_tan(f0);
  if (d==-1.0)                          /* FFPLB-024 (A)              */
    _errno=ERANGE;                      /* FFPLB-024 (A)              */
  return (d-1)/(d+1);
}

#define PI 3.1415926535897932           /* Value of pi                */

static const double pi8d_tbl[3]={PI/8.0,
                                        /* pi/8                       */
                                 0.3927001953125, /* FFPLB-014 (C)    */
                                 -1.1136137758451922e-6};
								        /* FFPLB-014 (C)              */

extern double __nand_value(void);       /* FFPLB-002 (C)              */

#define EXP_MASK 0x7FF00000             /* Mask of double exponent    */

double tan(double d0){
  long ipart;                           /* Floor of d0/(pi/8)         */
  double *p;                            /* Pointer to divisor table   */
  double pi8;                           /* pi/8                       */
  double pi8r;                          /* Approximate pi/8           */

#ifdef _BIG                             /* Big endian                 */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK){ /* FFPLB-024 (C)   */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
                                        /* Check NaN or Infinity      */
    return __nand_value();
  }                                     /* FFPLB-024 (A)              */
#else                                   /* Little endian              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)==EXP_MASK){ /*FFPLB-024 (C)*/
                                        /* Check NaN or Infinity      */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nand_value();
  }                                     /* FFPLB-024 (A)              */
#endif
  if (d0==0.0)                          /* Handle the cases of +-0    */
    return d0;
  p=pi8d_tbl;
  pi8 =*p++;                            /* pi8=pi/8                   */
  pi8r=*p++;                            /* pi8r=1600.0/4096 (approx   */
                                        /*                   pi/8)    */
  ipart=d0/pi8;                         /* Get floor of d0/(pi/8)     */ 
  if (d0<0)
    ipart--;
  if (ipart&1)
    ipart++;
  d0-=pi8r*ipart;

  pi8r=*p++;                            /* Load approx value error    */
                                        /* to adjust remainder        */
  d0-=pi8r*ipart;                       /* Adjust                     */
  /* Original d0 (mod pi) Ipart (mod 4) New d0                        */
  /* 0~pi/8               0             0~pi/8                        */
  /* pi/8~pi/4            2             -pi/8~0                       */
  /* pi/4~3pi/3           2             0~pi/8                        */
  /* 3pi/8~pi/2           4             -pi/8~0                       */
  /* pi/2~5pi/4           4             0~pi/8                        */
  /* 5pi/4~3pi/2          6             -pi/8~0                       */
  /* 3pi/2~7pi/8          6             0~pi/8                        */
  /* 7pi/8~pi             0             -pi/8~0                       */
  switch ((ipart&7)>>1){                /* Dispatch by the remainder  */
  case 0:
    return poly_tan(d0);
  case 1:
    return poly_tan1(d0);
  case 2:
    return poly_tan_r(d0);
  case 3:
    return poly_tan2(d0);
  }
}
#endif
