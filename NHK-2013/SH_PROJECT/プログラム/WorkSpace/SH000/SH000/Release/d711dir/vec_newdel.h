/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1992 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
/*

Declarations for runtime routines for vector new() and delete() functionality.

*/

#ifndef VEC_NEWDEL_H
#define VEC_NEWDEL_H

#include "runtime.h"

EXTERN_C void *__vec_new_eh(void                         *array_ptr,
                            int                          number_of_elements,
                            size_t                       element_size,
                            a_constructor_ptr	 	 ctor,
                            a_destructor_ptr	         dtor);

EXTERN_C void *__vec_new(void                         *array_ptr,
                         int                          number_of_elements,
                         size_t                       element_size,
                         a_constructor_ptr            ctor);

EXTERN_C void __vec_delete(void                *array_ptr,
                           int                 number_of_elements,
                           size_t              element_size,
                           a_destructor_ptr    dtor,
                           int                 delete_flag,
                           int                 /*unused_arg*/);

EXTERN_C void _array_pointer_not_from_vec_new();

/*
Type name used by the exception handling mechanism to point to the
structure used to maintain information about array new and delete
operations that are in process.
*/
typedef struct an_array_alloc_eh_info *an_array_alloc_eh_info_ptr;

#endif /* ifndef VEC_NEWDEL_H */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1992 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
