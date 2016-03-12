#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Wingdi.h>

#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/Types.h"

#include "AssetManager.h"
#include "RenderManager.h"
#include "MemoryManager.h"
#include "SystemManager.h"
#include "utils.h"


#define FRAME_RATE (60)
#define FRAME_MS (FRAME_RATE / 1.0)


Bool32 gRunning;


LRESULT CALLBACK Win32WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        case WM_QUIT:
        case WM_CLOSE: {
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
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc = Win32WindowProc;
    wnd.hInstance = instance;
    wnd.hIcon = NULL;
    wnd.hCursor = NULL;
    wnd.lpszClassName = "Engine Class Name";
    wnd.hIconSm = NULL;

    if (!RegisterClassEx(&wnd))
    {
        Capstan::Debug::Print("Could not register Window Class.");

        return 1;
    }

    HWND windowHandle = CreateWindow(
        "Engine Class Name",
        "Engine Window Name",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        0, 0,
        instance,
        0
    );

    if (!windowHandle)
    {
        Capstan::Debug::Print("Could not create window.");

        return 1;
    }

    DWORD cpuInfoLength;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION cpuInfo;
    BOOL result = GetLogicalProcessorInformation(&cpuInfo, &cpuInfoLength);

    Capstan::Debug::Print("Cache Line Length: %d", cpuInfo.Cache.LineSize);

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

    Capstan::System::Start(Capstan::System::Type::Memory, MB(400));
    Capstan::System::Start(Capstan::System::Type::FileSystem);
    Capstan::System::Start(Capstan::System::Type::Asset, MB(200));
    Capstan::System::Start(Capstan::System::Type::Renderer);

    Capstan::RenderManager * gRenderManager = (Capstan::RenderManager *)Capstan::System::Get(Capstan::System::Type::Renderer);

    gRunning = true;

    double delta, interval;
    LARGE_INTEGER frequency, elapsed, current, previous;


    // Returns counts/s
    QueryPerformanceFrequency(&frequency);
    // Counts / milliseconds
    interval = 1.0 / (1000 * frequency.QuadPart);
    QueryPerformanceCounter(&previous);

    while (gRunning)
    {
        QueryPerformanceCounter(&current);
        elapsed.QuadPart = (current.QuadPart - previous.QuadPart);
        delta = (double)(elapsed.QuadPart * interval); // milliseconds

        previous = current;

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

        gRenderManager->Render();

        QueryPerformanceCounter(&previous);
    }

    Capstan::System::ShutDown(Capstan::System::Type::Renderer);
    Capstan::System::ShutDown(Capstan::System::Type::Asset);
    Capstan::System::ShutDown(Capstan::System::Type::FileSystem);
    Capstan::System::ShutDown(Capstan::System::Type::Memory);

#ifdef CAPSTAN_CONSOLE
    if (console)
    {
        FreeConsole();
    }
#endif

    return 0;
}
