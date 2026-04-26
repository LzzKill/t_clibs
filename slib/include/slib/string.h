/*
 * string.h
 * t_clibs
 * Apache License 2.0
 *
 * */

/* ISO C99 Standard */
/* Non-standard incomplete implementation */

#include "stddef.h"

#ifndef NULL
#define NULL (void *)0
#endif

void *memchr(const void *str, int c, size_t n);

int memcmp(const void * string1, const void * string2 , size_t n);

void* memcpy(void * dest, const void *source ,size_t n);

void* memmove(void *string, const void *c, size_t);


