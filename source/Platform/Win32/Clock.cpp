#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "Capstan/Common.h"

#include "Capstan/Platform/Clock.h"


namespace Capstan
{
namespace Platform
{
    Real64 GetPeriod (void)
    {
        LARGE_INTEGER frequency;

        QueryPerformanceFrequency(&frequency);

        return 1.0 / (Real64)frequency.QuadPart;
    }

    Real64 GetTime (void)
    {
        local_persist Real64 period = GetPeriod();

        LARGE_INTEGER counter;

        QueryPerformanceCounter(&counter);

        return (Real64)counter.QuadPart * period;
    }
}
}
