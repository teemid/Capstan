#ifndef CAPSTAN_PLATFORM_MEMORY_H
#define CAPSTAN_PLATFORM_MEMORY_H


#include "Platform/Types.h"


namespace Capstan
{
namespace Memory
{
    void * Allocate(size_t size);
    void * Reallocate(void * memory, size_t prevSize, size_t newSize);
    void Copy (void * source, void * destination, size_t size);
    void Zero (void * memory, size_t size);
    Bool32 Free (void * memory);
}
}

#endif
