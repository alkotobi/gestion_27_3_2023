#include "mnsystem.h"

void mnassert(void* ptr)
{
    assert(ptr);
}

void* mnalloc(size_t size)
{
    void* ret = malloc(size);
    mnassert(ret);
    return ret;
    
}

void mnfree(void* ptr)
{
    free(ptr);
}

void mnfree_v1(mnptrhld ptr_hld)
{
    mnfree(*ptr_hld);
    *ptr_hld=0;
}

void* mnrealloc(void* ptr,size_t new_size)
{
    void* ret = realloc(ptr,new_size);
    mnassert(ret);
    return ret;
}

void* mncalloc(size_t count,size_t size)
{
    void* ret=calloc(count,size);
    mnassert(ret);
    return ret;
}
