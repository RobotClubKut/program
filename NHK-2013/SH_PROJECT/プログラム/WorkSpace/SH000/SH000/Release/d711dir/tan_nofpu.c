/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/******************************************************************/
/* SPEC;                                                          */
/*   NAME = tan : tan value output ;                              */
/*   FUNC = tan : output IEEE double format ;                     */
/*   CLAS = UNIT ;                                                */
/*   NOTE = SHC floating point library ;                          */
/* END;                                                           */
/******************************************************************/
#if defined(_FLT)|defined(_FPS)			    /* C S50001SP */
#define  tanf  tan				    /* A S50001SP */
#include "tanf.c"				    /* A S50001SP */
#else						    /* A S50001SP */

#include "fdefd.h"
#include "fextd.h"
double tan(p)
double p;
{
    double ret;
    ret=_idtod(_in_tand(_dtoid(p)));
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
