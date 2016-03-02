#ifndef CAPSTAN_GAMEPAD_H
#define CAPSTAN_GAMEPAD_H


#include "Platform/Types.h"


namespace Capstan
{
    struct Stick
    {
        Real32 x;
        Real32 y;
    };

    struct GamePadState
    {
        Stick leftStick;
        Stick rightStick;

        union
        {
            struct
            {
                Bool32 A;
                Bool32 B;
                Bool32 X;
                Bool32 Y;

                Bool32 DPadLeft;
                Bool32 DPadUp;
                Bool32 DPadRight;
                Bool32 DPadDown;

                Bool32 leftBumper;
                Bool32 rightBumper;
                Bool32 leftTrigger;
                Bool32 rightTrigger;

                Bool32 BLeftStick;
                Bool32 BRightStick;

                Bool32 start;
                Bool32 back;
            };
            Bool32 Buttons[16];
        };
    };

    // NOTE (Emil): Should this be between 0 and 1?
    struct Vibration
    {
        Real32 left;
        Real32 right;
    };

    class GamePad
    {
    public:
        GamePad (void);
        ~GamePad (void);

        void Initialize (void);
        void Destroy (void);
        void GetState (Int32 index, GamePadState * state);
        void SetState (Int32 index, Vibration * vibration);
    private:
        struct PlatformData;
        PlatformData * platform;
    };
}


#endif
