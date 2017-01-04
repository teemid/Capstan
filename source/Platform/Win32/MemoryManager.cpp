#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Memory.h"
#include "Capstan/Platform/Win32/Debug.h"

#include "Capstan/MemoryManager.h"


namespace Capstan
{
    MemoryManager::MemoryManager () { };
    MemoryManager::~MemoryManager () { };

    void MemoryManager::StartUp (UInt64 reserveSize)
    {
        start = Memory::Allocate(reserveSize);

        Assert(start, "Failed to allocate memory in MemoryManager.\n");

        current = start;
        top = start;
        end = (Byte *)start + reserveSize;
    }

    void MemoryManager::ShutDown (void)
    {
        Assert(start, "Trying to free nullptr in MemoryManager.\n");

        if (!Memory::Free(start))
        {
            Debug::Win32HandleError();
        }
    }

    void * MemoryManager::Allocate (UInt64 size)
    {
        // NOTE (Emil): More memory than we have
        Assert(!(size > (Byte *)this->end - (Byte *)this->start), "Asked for more memory than the manager has.\n");

        // NOTE (Emil): Asked for more memory than is left.
        Assert(!(size > (UInt64)((Byte *)this->end - (Byte *)this->top)), "Asked for more memory than the manager has available.\n");

        void * memory = this->current;
        this->current = this->top;
        this->top = (Byte *)this->top + size;

        return this->current;
    }

    Bool32 MemoryManager::Free (void * memory)
    {
        // NOTE (Emil): If the memory isn't at the top of the stack, we can't free it.
        if (this->current != memory)
        {
            return false;
        }

        return true;
    }
}
