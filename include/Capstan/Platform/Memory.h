#ifndef CAPSTAN_PLATFORM_MEMORY_H
#define CAPSTAN_PLATFORM_MEMORY_H


#include "Capstan/Types.h"


namespace Capstan
{
namespace Memory
{
    void * Allocate(Size size);
    void * Reallocate(void * memory, Size prevSize, Size newSize);
    void Copy (void * source, void * destination, Size size);
    void Zero (void * memory, Size size);
    Bool32 Free (void * memory);
}
}

#endif
