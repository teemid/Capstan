#include <windows.h>

#include "assert.h"
#include "FileSystem.h"
#include "MemoryManager.h"
#include "Win32/Win32Debug.h"


namespace Capstan
{
    #define ASYNC_READ_MAX_COUNT 16;

    Int64 GetFileSize (char * filename)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            Debug::Win32HandleError();
        }

        LARGE_INTEGER fileSize;
        auto result = ::GetFileSizeEx(fileHandle, &fileSize);

        // If the function fails and lpFilSizeHigh is NULL
        // If the function fails and lpFileSizeHigh is non-NULL
        if (!result)
        {
            Debug::Win32HandleError();
        }

        return (Int64)fileSize.QuadPart;
    }

    void Read (char * filename, void * buffer, size_t size, size_t offset)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            // FILE_FLAG_RANDOM_ACCESS
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );

        if (size == 0)
        {
            LARGE_INTEGER fileSize;
            auto result = ::GetFileSizeEx(fileHandle, &fileSize);

            size = fileSize.QuadPart;
        }

        if (offset != 0)
        {
            LARGE_INTEGER li;

            li.QuadPart = offset;

            li.LowPart = SetFilePointer(
                fileHandle,
                li.LowPart,
                &li.HighPart,
                FILE_BEGIN
            );

            if (li.LowPart == INVALID_SET_FILE_POINTER)
            {

            }
        }

        if (fileHandle == INVALID_HANDLE_VALUE) {
            Debug::Win32HandleError();
        }

        DWORD bytesRead;
        BOOL result = ReadFile(
            fileHandle,
            buffer,
            (DWORD)size,
            &bytesRead,
            NULL
        );

        assert(bytesRead == size);

        if (!result) {
            Debug::Win32HandleError();
        }

        // TODO (Emil): Should something more be done here?
        // Should the function return a boolean for success?
    }

    void Write (char * filename, void * buffer, size_t)
    {
        HANDLE fileHandle = CreateFile(
            (LPCSTR)filename,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL
        );
    }
}
