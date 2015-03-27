/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = log10 : log10 value output ;                          */
/*   FUNC = log10 : output IEEE double format ;                   */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#if defined(_FLT)|defined(_FPS)			    /* C S50001SP */
#define  log10f  log10				    /* A S50001SP */
#include "log10f.c"				    /* A S50001SP */
#else						    /* A S50001SP */

#include "fdefd.h"
#include "fextd.h"
double log10(p)
double p;
{
    double ret;
    ret=_idtod(_in_log10d(_dtoid(p)));
    if (isEMAXd(ret)){
        if (isMANTd(ret)){
            _errno = EDOM;
        }
        else {
            _errno = ERANGE;
        }
    }
    return ret;
}
#endif
