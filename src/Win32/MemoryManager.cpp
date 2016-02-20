#include <windows.h>

#include "assert.h"
#include "debug.h"
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

    void * MemoryManager::Allocate (size_t size)
    {
        // NOTE (Emil): More memory than we have.
        if (size > (UInt64)((Byte *)this->end - (Byte *)this->start))
        {
            Debug::OutputString("Asked for more memory than the manager has.");
            assert(0);

            return nullptr;
        }

        // NOTE (Emil): Asked for more memory than is left.
        if (size > (UInt64)((Byte *)this->end - (Byte *)this->top))
        {
            Debug::OutputString("Asked for more memory than the manager has.");
            assert(0);

            return nullptr;
        }

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
