#include "slib/stdlib.h"


/*
 * Allocates size bytes of uninitialized storage.
 * Returns a pointer to the allocated memory, or NULL if allocation fails.
 * The returned pointer is suitably aligned for any scalar type.
 */
void *malloc(size_t size)
{

}

/*
 * Allocates space for an array of nmemb elements, each of size bytes.
 * Initializes all bytes in the allocated storage to zero.
 * Returns a pointer to the allocated memory, or NULL if allocation fails.
 */
void *calloc(size_t nmemb, size_t size);

/*
 * Reallocates the memory block pointed to by ptr to size bytes.
 * - If ptr is NULL: equivalent to malloc(size)
 * - If size is 0: equivalent to free(ptr) (returns NULL)
 * - Preserves the contents of the original block up to the minimum of old and new size.
 * Returns a pointer to the new memory block, or NULL if reallocation fails (original block unchanged).
 */
void *realloc(void *ptr, size_t size);

/*
 * Frees the memory block pointed to by ptr (allocated by malloc/calloc/realloc).
 * If ptr is NULL, no operation is performed.
 * Does not change the value of ptr (it remains a dangling pointer after call).
 */
void free(void *ptr);

/*
 * Terminates the program abnormally.
 * Flushes all open output streams, closes all open files, and terminates the process.
 * No return value (does not return to the caller).
 */
void abort(void);

/*
 * Terminates the program normally.
 * Flushes all open output streams, closes all open files, and returns status to the host environment.
 * status == EXIT_SUCCESS indicates successful termination; EXIT_FAILURE indicates failure.
 * No return value (does not return to the caller).
 */
void exit(int status);

/*
 * Converts the initial portion of the string pointed to by nptr to int.
 * Ignores leading whitespace; accepts optional '+' or '-' sign.
 * Stops conversion at the first character not a decimal digit.
 * Returns the converted int value. If no conversion is possible, returns 0.
 */
int atoi(const char *nptr);

/*
 * Converts the initial portion of nptr to long int.
 * Behaves like atoi, but returns long int and handles larger values.
 */
long atol(const char *nptr);

/*
 * Converts the initial portion of nptr to long long int (C99 extension to C89).
 * Behaves like atoi, but returns long long int for 64-bit values.
 */
long long atoll(const char *nptr);

/* Exchanges the value pointed to by a and b */
void swap(void *a, void *b, size_t size)
{
	void* t = a;
	a = b;
	b = t;
}

