#ifndef CAPSTAN_MEMORY_H
#define CAPSTAN_MEMORY_H


#include "types.h"


namespace Capstan
{
namespace Core
{
    void * Malloc(size_t size);
    void * Realloc(void * memory, size_t prevSize, size_t newSize);
    Bool32 Free (void * memory);
}
}

#endif
