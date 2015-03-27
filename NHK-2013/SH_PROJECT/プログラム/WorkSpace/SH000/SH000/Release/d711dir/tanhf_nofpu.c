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
#ifndef _FPD					    /* A S50001SP */

#include "fdefs.h"
#include "fexts.h"
float tanhf(p)
float p;
{
    float ret;
    ret=_istos(_in_tanhs(_stois(p)));
    if (isEMAXf(ret)){
        if (isMANTf(ret)){
            _errno = EDOM;
        }
        else {
            _errno = ERANGE;
        }
    }
    return ret;
}

#else						    /* A S50001SP */
#define tanh tanhf    				    /* A S50001SP */
#include "tanh.c"				    /* A S50001SP */
#endif					 	    /* A S50001SP */
