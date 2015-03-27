/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1993-1997 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/
/*

Miscellaneous declarations for all runtime routines.

*/

#ifndef RUNTIME_H
#define RUNTIME_H 1

#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <new_edg.h>         /* EDG orignal <new.h> -> SHC/C++ <new_edg.h> */
#include "error.h"

#ifdef __linux__
/* Linux improperly defined NULL as "(void*)0".  Undefine it if it has
   already been defined, and define it to the proper value. */
#ifdef NULL
#undef NULL
#endif /* ifdef NULL */
#define NULL 0
#endif /* ifdef __linux__ */

#ifndef DEBUG
/* Include debugging code. */
#define DEBUG 0
#endif /* ifndef DEBUG */
#if DEBUG
EXTERN int	__debug_level /* = 0 */;
			/* Debug level.  0 means no debug output, 1 - 5
                            means increasing amounts. */
#endif /* DEBUG */
#if DEBUG || CHECKING
#define __f_debug stderr
			/* Debug output file.  This is a macro and not a
			   variable because the initialization of a variable
			   with the value "stderr" cannot be done as a static
			   initialization on some systems. */
#endif /* DEBUG || CHECKING */

/*
Error routines.
*/
#if CHECKING
/* Macro to test an assertion and generate an internal error if
   the condition is not TRUE.  The macro expands to nothing when checking
   code is not being used. */
#define assert_msg() \
  {									\
    (void)fprintf(__f_debug, "Assertion failed in file \"%s\", line %d\n", \
                  __FILE__, __LINE__);				\
    abort();								\
  }

#define check_assertion(test)						\
  if (!(test)) {							\
    assert_msg()							\
  }
#define unexpected_condition()						\
  assert_msg()
#else /* !CHECKING */
#define check_assertion(test) /* Nothing */
#define unexpected_condition()    /* Nothing */
#endif /* CHECKING */

/*
Define the qualifier that should be used to access something defined
in the namespace of the runtime.  This is "std" if the runtime
uses namespaces or "" otherwise.
*/
#ifdef __EDG_RUNTIME_USES_NAMESPACES
#define STD_NAMESPACE std
#else /* ifndef __EDG_RUNTIME_USES_NAMESPACES */
#define STD_NAMESPACE /* nothing */
#endif /* ifdef __EDG_RUNTIME_USES_NAMESPACES */

/*
a_size_of_t is used as a synonym for size_t by the runtime.
*/
#if 0
This should probably use some other kind of test.
#endif /* 0 */
#if __cplusplus
typedef size_t a_sizeof_t;
#else /* __cplusplus */
typedef unsigned int a_sizeof_t;
#endif /* __cplusplus */

typedef void (*a_void_function_ptr)();
			/* Type used to store a generic function pointer. */

typedef void (*a_destructor_ptr)(void*, int);
			/* Type used to store a pointer a destructor. */

typedef void* (*a_new_ptr)(size_t);
			/* Type used to store a pointer to an operator new
			   routine. */

typedef void (*a_delete_ptr)(void*);
			/* Type used to store a pointer to an operator delete
			   routine. */

typedef void (*a_two_operand_delete_ptr)(void *, a_sizeof_t);
			/* Type used to store a pointer to a two operand
			   operator delete routine. */

#if CFRONT_COMPATIBILITY_MODE
typedef void (*a_cfront_constructor_ptr)(void*, void* b1, void* b2, void*b3,
                                         void* b4, void* b5, void* b6,
					 void* b7, void* b8);
			/* Type of a constructor called from vec_new in
			   cfront mode. */
#endif /* CFRONT_COMPATIBILITY_MODE */

typedef void (*a_constructor_ptr)(void*);
			/* Type of a default constructor called from
			   vec_new. */
typedef void (*a_copy_constructor_ptr)(void*, void*);
			/* Type of a copy constructor called from
			   vec_cctor. */

extern void __default_new_handler(void);
			/* The default new handler routine. */

EXTERN_C STD_NAMESPACE::new_handler
		_new_handler
		  initial_value((a_void_function_ptr)__default_new_handler);
			/* Pointer to the new handler routine to be called. */

#endif /* RUNTIME_H */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1993-1997 Edison Design Group Inc.                   [_]          *
*                                                                             *
******************************************************************************/
