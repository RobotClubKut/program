/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = exp : exponential value output ;                      */
/*   FUNC = exp : output IEEE double format ;                     */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#if defined(_FLT)|defined(_FPS)			    /* C S50001SP */
#define  expf exp				    /* A S50001SP */
#include "expf.c"				    /* A S50001SP */
#else						    /* A S50001SP */

#include "fdefd.h"
#include "fextd.h"
double exp(p)
double p;
{
    double ret;
    ret=_idtod(_in_expd(_dtoid(p)));
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
