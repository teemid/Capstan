#ifndef CAPSTAN_PLATFORM_MEMORY_H
#define CAPSTAN_PLATFORM_MEMORY_H


#include "types.h"


namespace Capstan
{
namespace Memory
{
    void * Allocate(size_t size);
    void * Reallocate(void * memory, size_t prevSize, size_t newSize);
    Bool32 Free (void * memory);
}
}

#endif
