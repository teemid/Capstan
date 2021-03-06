#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinGDI.h>

#include "Capstan/AssetManager.h"
#include "Capstan/InputManager.h"
#include "Capstan/MemoryManager.h"
#include "Capstan/Timer.h"
#include "Capstan/Types.h"
#include "Capstan/Utils.h"

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/FileSystem.h"
#include "Capstan/Platform/Memory.h"
#include "Capstan/Platform/Win32/PlatformData.h"

#include "Capstan/Graphics/RenderManager.h"

#define FRAME_RATE (60)
#define FRAME_MS (FRAME_RATE / 1.0)


using Win32Data = Capstan::Platform::PlatformData;


Bool32 gRunning;

namespace Capstan
{
    AssetManager             gAssetManager;
    FileSystem               gFileSystem;
    InputManager             gInputManager;
    MemoryManager            gMemoryManager;
    Graphics::RenderManager  gRenderManager;
    Timer                    gTimer;
    Platform::PlatformData   gPlatformData;
}


LRESULT CALLBACK Win32WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        case WM_QUIT:
        case WM_CLOSE: {
            PostQuitMessage(0);
            gRunning = false;
        } break;
        default:
        {
            return DefWindowProc(windowHandle, message, wParam, lParam);
        }
    }

    return 0;
}


int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wnd = {};
    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wnd.lpfnWndProc = Win32WindowProc;
    wnd.hInstance = instance;
    wnd.hIcon = NULL;
    wnd.hCursor = NULL;
    wnd.lpszClassName = "Engine Class Name";
    wnd.hIconSm = NULL;

    Assert(RegisterClassEx(&wnd), "Could not register Window Class.\n");

    HWND windowHandle = CreateWindow(
        "Engine Class Name",
        "Engine Window Name",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        0, 0,
        instance,
        0
    );

    Assert(windowHandle, "Failed to create window.\n");

    // DWORD cpuInfoLength;
    // SYSTEM_LOGICAL_PROCESSOR_INFORMATION cpuInfo;
    // BOOL result = GetLogicalProcessorInformation(&cpuInfo, &cpuInfoLength);

    // Capstan::Debug::Print("Cache Line Length: %d", cpuInfo.Cache.LineSize);

#ifdef CAPSTAN_CONSOLE
    BOOL console = AllocConsole();
    if (!console)
    {
        Capstan::Debug::Print("Failed to create a console.");
    }
    else
    {
        AttachConsole(GetCurrentProcessId());
        freopen("CON", "w", stdout);
        SetForegroundWindow(windowHandle);
    }
#endif

    Capstan::gPlatformData.windowHandle = windowHandle;
    Capstan::gPlatformData.deviceContext = GetDC(windowHandle);

    Capstan::gMemoryManager.StartUp(MB(400));
    Capstan::gFileSystem.StartUp();
    Capstan::gAssetManager.StartUp(MB(200));
    Capstan::gRenderManager.StartUp();

    ShowWindow(windowHandle, nCmdShow);

    gRunning = true;

    while (gRunning)
    {
        MSG message;
        while (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE)) {
            switch (message.message)
            {
                case WM_KEYDOWN:
                {
                    if (message.wParam == VK_ESCAPE)
                    {
                        PostQuitMessage(0);
                        gRunning = false;
                    }
                } break;
                default:
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                } break;
            }
        }

        Capstan::gRenderManager.Render();
        Capstan::gTimer.Step();
    }

    Capstan::gRenderManager.ShutDown();
    Capstan::gAssetManager.ShutDown();
    Capstan::gFileSystem.ShutDown();
    Capstan::gMemoryManager.ShutDown();

#ifdef CAPSTAN_CONSOLE
    if (console)
    {
        FreeConsole();
    }
#endif

    return 0;
}
