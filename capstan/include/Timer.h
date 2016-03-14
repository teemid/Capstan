#ifndef CAPSTAN_TIMER_H
#define CAPSTAN_TIMER_H


#include "Platform/Types.h"


namespace Capstan
{
    class Timer
    {
    public:
        Timer (void);
        ~Timer (void);

        void StartUp (void);
        void ShutDown (void);

        void Step (void);
        Real64 GetDelta (void);
    private:
        Real64 current;
        Real64 previous;
        Real64 delta;

        // Frames
        UInt32 frames;
    };
}


#endif
