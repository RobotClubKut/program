/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++ Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1995 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
/*

Virtual function table entry layout.

*/

#ifndef _VTBL_H
#define _VTBL_H

struct a_vtbl_entry {
  __EDG_DELTA_TYPE
		delta;
			/* Value to be added to the "this" pointer to adjust
			   it to point to the class for which the virtual
			   function is actually defined. */
  __EDG_VIRTUAL_FUNCTION_INDEX_TYPE
		index;
			/* Index into the virtual function table.  Only
			   used in member function pointers, not present in
			   vtbl entries.  Cfront uses the same structure for
		  	   both member pointers and vtbl entries, so this is
			   present for cfront compatibility. */
  union {
    a_void_function_ptr
		ptr;
			/* Pointer to the function to be called. */
    a_type_info_impl_ptr
		type_info_impl;
			/* Pointer to the type information implementation
			   entry.  This is present in slot zero of the
			   virtual function table. */
  } function;
};
typedef a_vtbl_entry *a_vtbl_entry_ptr;

#endif /* ifndef _VTBL_H */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
*                                                               \   /         *
* Proprietary information of Edison Design Group Inc.         /  | |  \       *
* Copyright 1995 Edison Design Group Inc.                        [_]          *
*                                                                             *
******************************************************************************/
