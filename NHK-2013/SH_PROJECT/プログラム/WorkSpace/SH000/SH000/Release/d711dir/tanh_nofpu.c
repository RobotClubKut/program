/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = tanh : hyperbolic-tan value output ;                  */
/*   FUNC = tanh : output IEEE double format ;                    */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#if defined(_FLT)|defined(_FPS)			    /* C S50001SP */
#define  tanhf  tanh				    /* A S50001SP */
#include "tanhf.c"				    /* A S50001SP */
#else						    /* A S50001SP */

#include "fdefd.h"
#include "fextd.h"
double tanh(p)
double p;
{
    double ret;
    ret=_idtod(_in_tanhd(_dtoid(p)));
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
