#include "Timer.h"

#include "Platform/Clock.h"


namespace Capstan
{
    Timer::Timer (void) { };

    Timer::~Timer (void) { };

    void Timer::Step (void)
    {
        frames++;

        previous = current;

        current = Platform::GetCurrentTime();

        delta = current - previous;
    };

    Real64 Timer::GetDelta (void)
    {
        return delta;
    };
}
