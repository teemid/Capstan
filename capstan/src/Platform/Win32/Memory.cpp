#include <windows.h>

#include "Platform/Win32/Debug.h"
#include "Platform/Memory.h"


namespace Capstan
{
namespace Memory
{
    void * Allocate (size_t size)
    {
        if (size == 0)
        {
            return 0;
        }

        return VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    }


    void * Reallocate (void * memory, size_t prevSize, size_t newSize)
    {
        void * newMemory = Allocate(newSize);

        if (newMemory)
        {
            CopyMemory(newMemory, memory, prevSize);
        }

        VirtualFree(memory, 0, MEM_RELEASE);

        return newMemory;
    }


    void Copy (void * source, void * destination, size_t size)
    {
        CopyMemory(destination, source, size);
    }


    void Zero (void * memory, size_t size)
    {
        ZeroMemory(memory, size);
    }


    Bool32 Free (void * memory)
    {
        if (!VirtualFree(memory, 0, MEM_RELEASE))
        {
            Debug::Win32HandleError();

            return false;
        }

        memory = nullptr;

        return true;
    }
}
}

