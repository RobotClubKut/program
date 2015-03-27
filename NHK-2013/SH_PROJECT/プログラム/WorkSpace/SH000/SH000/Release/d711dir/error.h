/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1999 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
/*

Declarations relating to error.c - runtime error handling.

*/

#ifndef ERROR_H
#define ERROR_H 1

typedef enum /* an_error_code */ {
  ec_none,
  ec_abort_header,
  ec_terminate_called,
  ec_terminate_returned,
  ec_already_marked_for_destruction,
  ec_main_called_more_than_once,
  ec_pure_virtual_called,
  ec_bad_cast,
  ec_bad_typeid,
  ec_array_not_from_vec_new,
  ec_last
} an_error_code;

EXTERN_C void __abort_execution(an_error_code err_code);
EXTERN_C int abort(void);           /* add SHC++. library use abort function */

#endif /* ERROR_H */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1999 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
