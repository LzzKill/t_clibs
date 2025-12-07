/*
 * stdlib.h
 * t_clibs
 * Apache License 2.0
 *
 * */

/* ISO C99 Standard */
/* Non-standard incomplete implementation */

#include "stddef.h"

#ifndef T_CLIBS_SLIB_STDLIB_H
#define T_CLIBS_SLIB_STDLIB_H

/* exit status */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/* 实际上 ABS 应该是个函数，这里用宏实现 */
/* Acturally, ABS should be a function, which is implemented using macros here.*/
#undef ABS
#define ABS(x) x>0? x : -x

/*
 * Allocates uninitialized memory block
 * @param size: Size of memory block (in bytes)
 * @return: Pointer to allocated memory, or NULL on failure
 */
void *malloc(size_t size);

/*
 * Allocates and initializes memory block to zero
 * @param nmemb: Number of elements
 * @param size: Size of each element (in bytes)
 * @return: Pointer to allocated memory, or NULL on failure
 */
void *calloc(size_t nmemb, size_t size);

/*
 * Resizes existing memory block
 * @param ptr: Pointer to previously allocated memory (or NULL)
 * @param size: New size of memory block (in bytes)
 * @return: Pointer to resized memory, or NULL on failure (original ptr remains valid)
 */
void *realloc(void *ptr, size_t size);

/*
 * Frees allocated memory block
 * @param ptr: Pointer to memory block to free (or NULL)
 * @return: None
 */
void free(void *ptr);

/*
 * Abnormally terminates the program
 * Flushes output streams, closes files, and terminates process
 * @return: None (does not return)
 */
void abort(void);

/*
 * Normally terminates the program
 * Flushes output streams, closes files, returns status to host
 * @param status: Termination status (EXIT_SUCCESS for success, EXIT_FAILURE for failure)
 * @return: None (does not return)
 */
void exit(int status);

/*
 * Converts string initial portion to int
 * Ignores leading whitespace; accepts '+'/'+' sign; stops at non-digit
 * @param nptr: Pointer to input string
 * @return: Converted int value, or 0 if no conversion possible
 */
int atoi(const char *nptr);

/*
 * Converts string initial portion to long int
 * Behaves like atoi, supports larger values
 * @param nptr: Pointer to input string
 * @return: Converted long int value, or 0 if no conversion possible
 */
long atol(const char *nptr);

/*
 * Converts string initial portion to long long int (C99)
 * Behaves like atoi, supports 64-bit values
 * @param nptr: Pointer to input string
 * @return: Converted long long int value, or 0 if no conversion possible
 */
long long atoll(const char *nptr);

/*
 * Exchanges values of two memory blocks
 * @param a: Pointer to first memory block
 * @param b: Pointer to second memory block
 * @param size: Size of each memory block (in bytes)
 * @return: None
 */
void swap(void *a, void *b, size_t size);


#endif
