/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = h2lfun.h :                                           */
/*   FUNC = define of type  &  check macro ;                     */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

#define VOID               void
#define LONG               long
#define ULONG     unsigned long                                /* A S30011SP */
#define SSHORT     signed short
#define USHORT   unsigned short
#define SHORT             short
#define CHAR               char
#define UCHAR     unsigned char
#define INT                long
#define REG            register
#define LSTAT            static
#define LDBL        long double              /* @@@@@@@@@@@@@@@@@@@@ */

#ifdef  _DSPC
#define FIXED           __fixed              /* A V80#4.17 */
#define LFIXED    long  __fixed              /* A V80#4.17 */
#define ACCUM           __accum              /* A V80#4.17 */
#define LACCUM    long  __accum              /* A V80#4.17 */
#endif  /* _DSPC */

#define flgck1(fp,flg) (fp->_ioflag1&flg)    /* _ioflag1 check macro */
#define flgck2(fp,flg) (fp->_ioflag2&flg)    /* _ioflag2 check macro */

#define _toint(x)
#define _tolng(x)
#define _todbl(x)

#ifdef _APPEND
#ifndef _XYA
#define _XYA
#endif
typedef int _ALIGN;
union _header {
              struct {
                      unsigned long size;
                      union _header _XYA *next;
              } space;
              _ALIGN x;
};
typedef union _header _HEADER;
#endif
#ifdef E_LITTLE                                                /* A S30011SP */
extern void _mvito4b(UCHAR *, ULONG *);                        /* A S30011SP */
extern void _mvsto2b(UCHAR *, USHORT *);                       /* A S30011SP */
#endif                                                         /* A S30011SP */
