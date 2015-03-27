/********************************************************************************/
/* Copyright (C) 1992,2010 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*                                                  * A S70001SP */
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = sem.h : header file for exclusive control ;          */
/*   FUNC = this header file do the following functions;         */
/*              semaphore error symbols define ;                 */
/*   CLAS = UNIT ;                                               */
/*   NOTE = (New : S70001SP)                                     */
/*   END ;                                                       */
/*****************************************************************/
                                    /* semaphore ID define       */
#define	_MALLOC_SEM	1
#define	_STRTOK_SEM	2
#define	_FILE_TBL_SEM	3

#ifdef _DSPC
#ifdef _XYA
#define __X 1
#define __Y 2
#if (_XYA+0==1)
#undef  _MALLOC_SEM
#define _MALLOC_SEM     4
#endif
#if (_XYA+0==2)
#undef  _MALLOC_SEM
#define _MALLOC_SEM     5
#endif
#undef __X
#undef __Y
#endif
#endif /* _DSPC */

/* _iob[] —p ID ‚ð’Ç‰Á	A V94-#1.92	*/
#define _IOB_SEM 6
                                    /* error number define       */
#define EMALRESM 2100       /* malloc semaphore reserve error    */
#define ETOKRESM 2110       /* strtok semaphore reserve error    */
#define EIOBRESM 2120       /* _iob   semaphore reserve error    */
#define EMALFRSM 2101       /* malloc semaphore free error       */
#define ETOKFRSM 2111       /* strtok semaphore free error       */
#define EIOBFRSM 2121       /* _iob   semaphore free error       */

extern int  wait_sem(int);              /* get Semaphore         */
extern int  signal_sem(int);            /* free Semaphore        */
