/********************************************************************************/
/* Copyright (C) 1992,2010 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/***********************************************************************/
/* SPEC;                                                               */
/*  NAME = lstdio : header file for standard I/O function ;             */
/*                                                                     */
/*  FUNC = this header file do the following functions;                */
/*         (1) file entry table define;                                */
/*         (2) I/O macro define;                                       */
/*         (3) symbol define;                                          */
/*  CLAS = UNIT;                                                       */
/*                                                                     */
/* END;                                                                */
/***********************************************************************/
                                                         /* D S01006SP */

#include "lstddef.h"

/*#ifndef _NFILE                                         * D S70001SP */
/*#define _NFILE                                         * D S70001SP */
/*#define SYS_OPEN 20                                    * D S70001SP */
#pragma pack 4
extern struct _iobuf {
       unsigned char *_bufptr;          /* buffer pointer              */
                long  _bufcnt;          /* buffer count                */
       unsigned char *_bufbase;         /* buffer base pointer         */
                long  _buflen;          /* buffer length               */
                char  _ioflag1;         /* I/O control flag 1          */
                char  _ioflag2;         /* I/O control flag 2          */
                char  _iofd;
};
#pragma unpack

/* リエントラント用にファイル数変数を追加	A V94-#1.92	*/
#ifdef _REENTRANT
extern const int _nfiles;                   
#endif

typedef struct _iobuf FILE;             /* define FILE of file-stream    */

#define _IOFBF 1                        /* define _IOFBF of full buffering */
#define _IOLBF 2                        /* define _IOLBF of line buffering */
#define _IONBF 3                        /* define _IONBF of non buffering  */

#define SEEK_SET 0                      /* allocate top position */
#define SEEK_CUR 1                      /* allocate current position */
#define SEEK_END 2                      /* allocate bottom position */

#define BUFSIZ 512                      /* default buffer size */

                                        /* error number define */
#define EBADF  1302                     /* I/O operation error */
#define PTRERR 1106                     /* fp null */
#define ECSPEC 1304                     /* format err */
#define NOTOPN 1300                     /* file not open */

                                        /* I/O flags for _ioflag1      */
#define _IOREAD    1                    /* only read or update read    */
#define _IOWRITE   2                    /* only write or update write  */
#define _IORW      4                    /* update file                 */
#define _IOUNBUF   8                    /* unbffering I/O              */
#define _IOBGBUF  16                    /* automatic buffer allocate   */
#define _IOEOF    32                    /* end of file                 */
#define _IOERR    64                    /* I/O error                   */
#define _IOBIN   128                    /* binaly file                 */
#define _UNGTC     1                    /* ungetc issued (_ioflag2)    */
#define _IOLINBUF  2                    /* line buffering              */

#define EOF     (-1)
#define _EOL    (0X0A)                  /* end of line                 */

#define stdin       (&_iob[0])          /* standard input file */
#define stdout      (&_iob[1])          /* standard output file */
#define stderr      (&_iob[2])          /* standard error output file */

#define getc(fp) ((fp)->_ioflag2&=~_UNGTC,(((fp)->_ioflag1&(_IORW|_IOWRITE))==\
 (_IORW|_IOWRITE))&&(fp)->_bufcnt==(fp)->_buflen?(_fillbuf(fp)):\
 --(fp)->_bufcnt>=0 ?((int)*(fp)->_bufptr++):_fillbuf(fp))
#define putc(x,fp) (((((fp)->_ioflag1&_IORW)!=0&&((fp)->_ioflag1&_IOWRITE)==0)\
 ?_putcsub(fp):(void)0),((((fp)->_bufcnt==0)||((flgck2(fp,_IOLINBUF)!=0)&&\
 ((fp)->_bufbase!=(fp)->_bufptr)&&(*((fp)->_bufptr-1)==_EOL)))\
 ?_flshbuf((int)(x),(fp)):\
 (((fp)->_bufcnt--),((int)(*(fp)->_bufptr++=(unsigned char)(x))))))

/* リエントラント時にマクロ展開をとめる	C V94-#1.92	*/
#ifndef _REENTRANT
#define getchar()   getc(stdin)
#define putchar(x)  putc(x,stdout)
#endif

#define feof(fp)    ((fp)->_ioflag1&_IOEOF)
#define ferror(fp)  ((fp)->_ioflag1&_IOERR)
#define clearerr(fp) ((void)((fp)->_ioflag1&=~(_IOEOF|_IOERR)))
/*#endif                                                 * D S70001SP */
