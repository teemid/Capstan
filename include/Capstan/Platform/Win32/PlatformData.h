#ifndef CAPSTAN_PLATFORM_WIN32_PLATFORM_DATA_H
#define CAPSTAN_PLATFORM_WIN32_PLATFORM_DATA_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <WinGDI.h>


namespace Capstan
{
    namespace Platform
    {
        struct PlatformData
        {
            HWND windowHandle;
            HDC deviceContext;
            HGLRC renderContext;
        };
    }
}

#endif
