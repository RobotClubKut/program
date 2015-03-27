/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = sin: double precision sine function;                      */
/*   FUNC = Computes double precision sine of its argument;           */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#if defined _FLT || defined _FPS        /* double=float or fpu=single */
#define sinf sin                        /* rename sinf to sin         */
#include "sinf.c"                       /* include sinf               */
#else

#include "fperror.h"                    /* FFPLB-024 (A)              */

extern const double __pi4d_tbl[3];      /* __pi4d_tbl[0]: pi/4        */
                                        /* __pi4d_tbl[1]: 3200/4096   */
                                        /* __pi4d_tbl[2]: pi/4-       */
                                        /*                3200/4096   */

#define EXP_MASK 0x7FF00000             /* Mask of double exponent    */

#define PI 3.1415926535897932           /* FFPLB-017 (A)              */

extern double __poly_sind(double);
extern double __poly_cosd(double);
extern double __poly_cosdn(double);

extern double __nand_value(void);
extern double fmod(double, double);     /* FFPLB-017 (A)              */
extern double sin(double);              /* FFPLB-017 (A)              */

static double sin_special(double d0){   /* FFPLB-017 (A)              */
#ifdef _BIG                             /* FFPLB-017 (A)              */
  if ((*(unsigned long *)&d0&EXP_MASK)==EXP_MASK){/* FFPLB-024 (C)    */
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nand_value();              /* FFPLB-017 (A)              */
  }                                     /* FFPLB-024 (A)              */
#else                                   /* FFPLB-017 (A)              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)==EXP_MASK){/* FFPLB-024 (C)*/
    _errno=EDOM;                        /* FFPLB-024 (A)              */
    return __nand_value();              /* FFPLB-017 (A)              */
  }                                     /* FFPLB-024 (A)              */
#endif                                  /* FFPLB-017 (A)              */
  d0=fmod(d0, 2.0*PI);                  /* FFPLB-017 (A)              */
  return sin(d0);                       /* FFPLB-017 (A)              */
}                                       /* FFPLB-017 (A)              */

double sin(double d0)                   /* d0: Parameter of sine      */
{
  long ipart;                           /* Floor of d0/(pi/4)         */
  double *p;                            /* Pointer to divisor table   */
  double pi4;                           /* pi/4                       */
  double pi4r;                          /* Approximate pi/4           */
                                        /* and error                  */
#ifdef _BIG                             /* Big endian                 */
  if ((*(unsigned long *)&d0&EXP_MASK)>=0x41d00000) /* FFPLB-017 (C)  */
    return sin_special(d0);             /* FFPLB-017 (C)              */
#else                                   /* Little endian              */
  if ((*((unsigned long *)&d0+1)&EXP_MASK)>=0x41d00000) /*FFPLB-017(C)*/
    return sin_special(d0);             /* FFPLB-017 (C)              */
#endif
  if (d0==0.0)                          /* Handle cases of +-0        */
    return d0;
  p=__pi4d_tbl;
  pi4=*p++;
  if (d0<0)                             /* Compute floor(d0/pi4)      */
    ipart=-(long)(-d0/pi4)-1;
  else
    ipart=d0/pi4;
  pi4r=*p++;                            /* pi4r holds approximation   */
                                        /* of pi/4                    */
  if (ipart&1)
    ipart++;
  d0-=pi4r*ipart;                       /* Get remainder by           */
                                        /* approximation value        */
  pi4r=*p;                              /* Now pi4r holds the error   */
                                        /* of approximation value     */
  d0-=pi4r*ipart;                       /* Adjust the remainder       */
  /* Original d0 (mod 2pi) Ipart (mod 8) New d0                       */
  /* 0~pi/4                0             0~pi/4                       */
  /* pi/4~pi/2             2             -pi/4~0                      */
  /* pi/2~3pi/4            2             0~pi/4                       */
  /* 3pi/4~pi              4             -pi/4~0                      */
  /* pi~5pi/4              4             0~pi/4                       */
  /* 5pi/4~3pi/2           6             -pi/4~0                      */
  /* 3pi/2~7pi/4           6             0~pi/4                       */
  /* 7pi/4~2pi             0             -pi/4~0                      */
  switch ((ipart&7)>>1){                /* Dispatch by the remainder  */
  case 0:
    return __poly_sind(d0);
  case 1:
    return __poly_cosd(d0);
  case 2:
    return __poly_sind(-d0);
  case 3:
    return __poly_cosdn(d0);
  }
}
#endif
