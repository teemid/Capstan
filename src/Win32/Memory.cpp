#include <windows.h>


#include "Win32/Win32Debug.h"
#include "memory.h"


namespace Capstan
{
namespace Core
{
    void * Malloc (size_t size)
    {
        if (size == 0)
        {
            return 0;
        }

        return VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    }


    void * Realloc (void * memory, size_t prevSize, size_t newSize)
    {
        void * newMemory = Malloc(newSize);

        if (newMemory)
        {
            CopyMemory(newMemory, memory, prevSize);
        }

        VirtualFree(memory, 0, MEM_RELEASE);

        return newMemory;
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

