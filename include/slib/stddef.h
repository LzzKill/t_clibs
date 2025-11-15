/*
 * stddef.h
 * t_clibs
 * Apache License 2.0
 *
 * */

/* ISO C99 Standard */
/* Non-standard incomplete implementation */

#ifndef T_CLIBS_SLIB_STDDEF_H
#define T_CLIBS_SLIB_STDDEF_H

/*
 * The C99 standard only defines it as a value of (void*)0, and here it is defined as a macro.
 */
#define NULL ((void*)0)

#ifdef __GNUC__
/* typeof is GNU extension maybe. */
typedef typeof(sizeof(0)) size_t;
typedef typeof((int*)NULL - (int*)NULL) ptrdiff_t;
#else
/* 
 * For long:
 * In x32, it is int maybe.
 * In x64, it is long maybe.
 *
 * In here, x64 is used for the definition
 * */
typedef unsigned long size_t
typedef long ptrdiff_t
#endif

#define offsetof(type, member) (size_t)(&((type*)0)->member)
/*                                     ^^^^^^^^^^^^^^^^^^^^ 
 * Force 0 to be converted into a structure pointer and take the address of a member.
 */
#endif
