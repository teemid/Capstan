#include <windows.h>

#include "Win32/Win32Debug.h"
#include "memory.h"
#include "MemoryManager.h"


namespace Capstan
{
    MemoryManager::MemoryManager () { };
    MemoryManager::~MemoryManager () { };

    void MemoryManager::StartUp (size_t reserveSize)
    {
        start = Core::Malloc(reserveSize);

        if (!start)
        {
            Debug::Win32HandleError();
        }

        current = start;
        top = start;
        end = (Byte *)start + reserveSize;
    }

    void MemoryManager::ShutDown (void)
    {
        if (!Core::Free(start))
        {
            Debug::Win32HandleError();
        }
    }

    Bool32 MemoryManager::Allocate (void * memory, size_t size)
    {
        // NOTE (Emil): More memory than we have.
        if (size > (UInt64)((Byte *)this->end - (Byte *)this->start))
        {
            return false;
        }

        // NOTE (Emil): Asked for more memory than is left.
        if (size > (UInt64)((Byte *)this->end - (Byte *)this->top))
        {
            return false;
        }

        this->current = this->top;
        this->top = (Byte *)this->top + size;

        return true;
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
