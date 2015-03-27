/*--------------------------------------------------------------------*/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2003, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/*--------------------------------------------------------------------*/
/**********************************************************************/
/* SPEC;                                                              */
/*   NAME = sinf: single precision sine function;                     */
/*   FUNC = Computes single precision sine of its argument;           */
/*   CLAS = UNIT;                                                     */
/*   NOTE = SH C/C++ fast floating point library;                     */
/* END;                                                               */
/**********************************************************************/
#ifndef _FPD                            /* fpu!=double                */

#include <mathf.h>

#include "fperror.h"                    /* FFPLB-024 (A)              */

extern float __internal_sincosf(float, int);
extern float __poly_sinf(float, float); /* FFPLB-010 (C)              */

float sinf(float d2){
  float d1=fabsf(d2);
  if (d1<1.0f)
    return __poly_sinf(d2, d2*d2);      /* FFPLB-010 (C)              */
  if (d2<0.0f)
    return __internal_sincosf(d1, 4);
  return __internal_sincosf(d2, 0);
}

#else                                   /* fpu=double                 */
#define sin sinf                        /* Renames sin to sinf        */
#include "sin.c"                        /* Includes double sine       */
#endif
