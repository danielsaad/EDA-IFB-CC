#ifndef ALLOC_H_INCLUDED
#define ALLOC_H_INCLUDED

#include <stdlib.h>

void* mallocx(size_t n);
void* callocx(size_t n,size_t s);
void* reallocx(void* ptr,size_t n);


#endif // ALLOC_H_INCLUDED
