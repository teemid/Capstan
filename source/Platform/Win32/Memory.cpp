#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Capstan/Platform/Win32/Debug.h"

#include "Capstan/Platform/Memory.h"


namespace Capstan
{
namespace Memory
{
    void * Allocate (Size size)
    {
        if (size == 0)
        {
            return 0;
        }

        return VirtualAlloc(0, (SIZE_T)size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    }


    void * Reallocate (void * memory, Size prevSize, Size newSize)
    {
        void * newMemory = Allocate((SIZE_T)newSize);

        if (newMemory)
        {
            CopyMemory(newMemory, memory, (SIZE_T)prevSize);
        }

        VirtualFree(memory, 0, MEM_RELEASE);

        return newMemory;
    }


    void Copy (void * source, void * destination, Size size)
    {
        CopyMemory(destination, source, (SIZE_T)size);
    }


    void Zero (void * memory, Size size)
    {
        ZeroMemory(memory, (SIZE_T)size);
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

