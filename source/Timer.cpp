#include "Capstan/Platform/Clock.h"

#include "Capstan/Timer.h"


namespace Capstan
{
    Timer::Timer (void) { };

    Timer::~Timer (void) { };

    void Timer::Step (void)
    {
        frames++;

        previous = current;

        current = Platform::GetTime();

        delta = current - previous;
    };

    Real64 Timer::GetDelta (void)
    {
        return delta;
    };
}
