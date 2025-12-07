#include "slib/stdlib.h"


void swap(void *a, void *b, size_t size)
{
	void* t = a;
	a = b;
	b = t;
}

