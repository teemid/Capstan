#include <cstdarg>
#include <cstdio>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Win32/Debug.h"


namespace Capstan
{
namespace Debug
{
#if defined CAPSTAN_DEBUG && CAPSTAN_CONSOLE

    void Print (char * formattedString, ...)
    {
        va_list args;
        va_start(args, formattedString);
        printf(formattedString, args);
        va_end(args);
    }

#else

    void Print (char * formattedString, ...)
    {
        char buffer[250];
        va_list args;
        va_start(args, formattedString);
        sprintf_s(buffer, formattedString, args);
        ::OutputDebugString(buffer);
        va_end(args);
    }

#endif
    void Win32HandleError (void)
    {
        DWORD errorCode = GetLastError();
        LPTSTR errorMessage = nullptr;

        DWORD success = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            errorMessage,
            0,
            nullptr
        );

        if (success)
        {
            OutputDebugString(errorMessage);
            LocalFree(errorMessage);
        }
        else
        {
            char buffer[250];
            sprintf_s(buffer, "Could not get error message for %d", errorCode);
            OutputDebugString(buffer);
        }
    }
}
}
