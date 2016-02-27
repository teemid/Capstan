#include <windows.h>
#include <XInput.h>

#include "Platform/GamePad.h"
#include "Platform/Memory.h"

#include "MyMath.h"
#include "types.h"


typedef DWORD (* XInputGetStatePtr) (DWORD dwUserIndex, XINPUT_STATE * pState);
XInputGetStatePtr XIGetState;
#define XInputGetState(index, state) XIGetState(index, state)

typedef DWORD (* XInputSetStatePtr) (DWORD dwUserIndex, XINPUT_VIBRATION * pVibration);
XInputSetStatePtr XISetState;
#define XInputSetState(index, vibration) XISetState(index, vibration)

namespace Capstan
{
    struct GamePad::PlatformData
    {
        HMODULE xinput;
    };

    GamePad::GamePad (void) { };
    GamePad::~GamePad (void) { };

    void GamePad::Initialize (void)
    {
        platform = (PlatformData *)Memory::Allocate(sizeof(PlatformData));

        platform->xinput = LoadLibrary("Xinput1_4.dll");

        if (!platform->xinput)
        {
            platform->xinput = LoadLibrary("Xinput9_1_0.dll");
        }

        if (!platform->xinput)
        {
            platform->xinput = LoadLibrary("Xinput1_3.dll");
        }

        if (platform->xinput)
        {
            XIGetState = (XInputGetStatePtr)GetProcAddress(platform->xinput, "XInputGetState");
            XISetState = (XInputSetStatePtr)GetProcAddress(platform->xinput, "XInputSetState");
        }
    }

    void GamePad::Destroy (void)
    {
        FreeLibrary(platform->xinput);
    }

    void GamePad::GetState (Int32 index, GamePadState * state)
    {
        XINPUT_STATE XState;
        if (XInputGetState(index, &XState) == ERROR_SUCCESS)
        {
            state->DPadUp       = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
            state->DPadDown     = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
            state->DPadLeft     = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
            state->DPadRight    = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
            state->start        = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
            state->back         = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
            state->leftBumper   = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
            state->rightBumper  = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
            state->BLeftStick   = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
            state->BRightStick  = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
            state->A            = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
            state->B            = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_B);
            state->X            = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_X);
            state->Y            = (XState.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
            state->leftTrigger  = (XState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
            state->rightTrigger = (XState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

            if (Math::Abs(XState.Gamepad.sThumbLX) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                state->leftStick.x = 1.0f * (XState.Gamepad.sThumbLX - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / 255;
            }

            if (Math::Abs(XState.Gamepad.sThumbLY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                state->leftStick.y = 1.0f * (XState.Gamepad.sThumbLX - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / 255;
            }

            if (Math::Abs(XState.Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                state->rightStick.x = 1.0f * (XState.Gamepad.sThumbLX - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / 255;
            }

            if (Math::Abs(XState.Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                state->rightStick.x = 1.0f * (XState.Gamepad.sThumbLX - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / 255;
            }
        }
    }

    void GamePad::SetState (Int32 index, Vibration * vibration)
    {
        XINPUT_VIBRATION XVibration;

        XInputSetState(index, &XVibration);
    }
}
