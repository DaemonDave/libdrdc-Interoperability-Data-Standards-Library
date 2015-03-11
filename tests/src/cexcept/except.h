/*
 * Description  : libdrdc - C Exceptions Handling from Adam M. Costello's code
 * Author       : Adam M. Costello <amc@cs.berkeley.edu>, included by Tie Peng
 * Purpose      : To handle exception cases using try / catch method
 * Revision     : $Id: except.h,v 1.4 2008/10/27 20:29:40 cvsuser Exp $
 
 NOTE: the following code is identical in syntax and format to cexcept.h 2.0.0 (2001-Jul-12-Thu), except where 
 comments have been moved and formatted for doxygen  DRE 2008
 */
 
#ifndef EXCEPT_H
#define EXCEPT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#ifndef CEXCEPT_H
#include "cexcept.h"
#endif

/*!
	\brief Exception handling functions 
	
	\details These C Exceptions Handling defines are from Adam M. Costello's (<amc@cs.berkeley.edu>) code. This code is
	utilized for wrapping exception code in other parts of the library. 
	
	Exception handling defines:
	- exception types
	- try
	- catch 
	- throw 
	
*/


/**
 * @addtogroup Exceptions  C Exception Handling API
 */

/** @{ */

/*!
		define_exception_type(type_name);

    This macro is used like an external declaration.  It specifies
    the type of object that gets copied from the exception thrower to
    the exception catcher.  The type_name can be any type that can be
    assigned to, that is, a non-constant arithmetic type, struct, union,
    or pointer.  Examples:

        define_exception_type(int);

        enum exception { out_of_memory, bad_arguments, disk_full };
        define_exception_type(enum exception);

        struct exception { int code; const char *msg; };
        define_exception_type(struct exception);

    Because throwing an exception causes the object to be copied (not
    just once, but twice), programmers may wish to consider size when
    choosing the exception type.
		
 etmp must be volatile because the application might use automatic 
 storage for the_exception_context, and etmp is modified between   
 the calls to setjmp() and longjmp().  A wrapper struct is used to 
 avoid warnings about a duplicate volatile qualifier in case etype 
 already includes it.                                              
*/		
#define define_exception_type(etype) \
struct exception_context { \
  jmp_buf *penv; \
  int caught; \
  volatile struct { etype etmp; } v; \
}

/** @} */

#endif /* EXCEPT_H */
