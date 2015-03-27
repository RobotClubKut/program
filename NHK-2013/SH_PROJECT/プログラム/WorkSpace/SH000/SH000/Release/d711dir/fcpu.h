/**********************************************************************/
/* SH C/C++ Compiler Ver. 9.0                                         */
/* Copyright (c) 2004, Renesas Technology Corporation and             */
/*                     Renesas Solutions Corporation                  */
/* All Rights Reserved.                                               */
/* Licensed material of Renesas Technology Corporation                */
/**********************************************************************/

#define CPU_HAVE_FPU (defined(_SH4) || defined(_SH4A) || \
                      defined(_SH2AFPU) || defined(_SH2E))

#define CPU_NOT_HAVE_FPU (!(CPU_HAVE_FPU))
