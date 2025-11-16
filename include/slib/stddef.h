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
 * C99 标准只定义了它是一个 (voic*)0 的值，此处用宏实现。
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
 * In here, x64 is used for the definition.
 *
 * 对于 long ：
 * 在 x32 ，它也许是 int 。
 * 在 x64 ，它也许是 long 。
 * 此处使用 x64 定义。
 * */
typedef unsigned long size_t
typedef long ptrdiff_t
#endif

#define offsetof(type, member) (size_t)(&((type*)0)->member)
/*                                     ^^^^^^^^^^^^^^^^^^^^ 
 * Force 0 to be converted into a structure pointer and take the address of a member.
 * 将 0 强制转化为 type* ，取 member 地址即可。
 */
#endif
