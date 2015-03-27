/********************************************************************************/
/* Copyright (C) 1992,2006 Renesas Technology Corp. and Renesas Solutions Corp. */
/* All rights reserved.                                                         */
/********************************************************************************/
/*****************************************************************/
/* SPEC ;                                                        */
/*   NAME = stdarg :                                             */
/*   FUNC = this module do the following finctions ;             */
/*                                                               */
/*         (1) initialize parameter pointer                      */
/*         (2) set parameter pointer to next parameter           */
/*                                                               */
/*                                                               */
/*   END ;                                                       */
/*****************************************************************/

typedef char *va_list ;

#if (defined _SH5M) || (defined _SH5C)            /* A S70004 P  */
					    /* SH5 ABI 5.3  + x  */ 		      
#define _VA_SIZE 8
#define _VA_DELTA (_VA_SIZE - 1)
#define _VA_MASK (~_VA_DELTA)
#define __va_pad(x) (((x) + _VA_DELTA) & _VA_MASK)
#define __va_promote(type) (__va_pad((int)sizeof(type)))
#if (defined _BIG)		 /* endian = big     A S70004 P */
#define va_start(ap,last) (ap = \
(char*)__va_pad((int)((char*)&(last)+sizeof(last))))
#define va_arg(ap,type) (*(type*)((sizeof(type)<8)\
?((ap+=__va_promote(type))-sizeof(type))\
:((ap+=__va_promote(type))-__va_promote(type))))
#define va_end(ap) (void)0
#else                               /* endian = little  A S70004 P */
#define va_start(ap,last) (ap = 		     /* A S70004 P */\
(char*)__va_pad((int)((char*)&(last)+sizeof(last)))) /* A S70004 P */
#define va_arg(ap,type) (*(type*)((sizeof(type)<8) /* A S70004 P   */\
?((ap+=__va_promote(type))-__va_promote(type))	     /* C S70004 P */\
:((ap+=__va_promote(type))-__va_promote(type))))     /* A S70004 P */
#define va_end(ap) (void)0                           /* A S70004 P */
#endif						     /* A S70004 P */
                                                     /* A S70004 P */
#else						     /* A S70004 P */
				        /* not SH5      A S70004 P */
#define va_start(ap,param) (void)((ap)=(int)\
((char *) &(param)+sizeof(param))%4u?\
(char *) &(param)+sizeof(param)+(4u-(sizeof(param)%4u)):\
(char *) &(param)+sizeof(param))
					       /* C T20066V	      */
#define va_arg(ap,type) (*((ap)=((int)((ap)+sizeof(type))%4u?	/*C T20029S*/\
(ap)+sizeof(type)+(4u-(sizeof(type)%4u)):\
(ap)+sizeof(type)),\
(type *)((int)((ap)-sizeof(type))%4u?\
(ap)-sizeof(type)-(4u-(sizeof(type)%4u)):\
(ap)-sizeof(type))))						/* C T20029S */
					       /* C T20066V	      */
#define va_end(ap)
#endif							     /* A S700004 P */
