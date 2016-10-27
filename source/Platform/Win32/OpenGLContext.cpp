#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <Wingdi.h>

#include "Capstan/Common.h"
#include "Capstan/Globals.h"
#include "Capstan/Strings.h"
#include "Capstan/Utils.h"

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Win32/Debug.h"
#include "Capstan/Platform/Win32/PlatformData.h"

#include "Capstan/Graphics/OpenGL/OpenGL.h"
#include "Capstan/Platform/OpenGLContext.h"

// NOTE (Emil): wglext.h is dependent on type definitions in gl.h.
#include "gl/wglext.h"


internal PFNWGLGETEXTENSIONSSTRINGARBPROC  wglGetExtensionsStringARB = nullptr;
internal PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;


namespace Capstan
{
namespace Platform
{
namespace OpenGL
{
    Bool32 CreateContext (PlatformData * data, Int32 major_version, Int32 minor_version)
    {
        PIXELFORMATDESCRIPTOR desired = {};
        desired.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        desired.nVersion = 1;
        desired.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        desired.iPixelType = PFD_TYPE_RGBA;
        desired.cColorBits = 24;
        desired.cAlphaBits = 8;
        desired.cAccumBits = 0;
        desired.cDepthBits = 24;
        desired.cStencilBits = 8;

        //--- START TEMP RENDER CONTEXT ---//
        Int32 pixelFormat = ChoosePixelFormat(data->deviceContext, &desired);
        Assert(pixelFormat, "ChoosePixelFormat failed to find a suitable pixel format.\n");

        Assert(SetPixelFormat(data->deviceContext, pixelFormat, &desired), "Failed to set pixel format.\n");

        data->renderContext = wglCreateContext(data->deviceContext);
        Assert(data->renderContext, "Failed to create render context.\n");

        wglMakeCurrent(data->deviceContext, data->renderContext);

        //--- START GET wglExtensions ---//
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB)
        {
            const char * extensions = wglGetExtensionsStringARB(data->deviceContext);

            Bool32 HasWglARBCreateContext = String::Find(extensions, "WGL_ARB_create_context");
            Bool32 HasWglARBCreateContextProfile = String::Find(extensions, "WGL_ARB_create_context_profile");

            if (HasWglARBCreateContext && HasWglARBCreateContextProfile)
            {
                wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
            }
        }
        else
        {
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
        }

        Assert(wglCreateContextAttribsARB, "wglCreateContextAttribsARB not found.\n");

        DeleteContext(data);
        //--- END GET wglExtensions ---//
        //--- END TEMP RENDER CONTEXT ---//

        //--- START GET EXTENSION RENDER CONTEXT ---//
        pixelFormat = ChoosePixelFormat(data->deviceContext, &desired);
        Assert(pixelFormat, "Failed to choose a pixel format.\n");

        Assert(SetPixelFormat(data->deviceContext, pixelFormat, &desired), "Failed to set pixel format.\n");

        int attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, major_version,
            WGL_CONTEXT_MINOR_VERSION_ARB, minor_version,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
            NULL, NULL
        };

        data->renderContext = wglCreateContextAttribsARB(data->deviceContext, 0, attributes);

        Assert(data->renderContext, "wglCreateContextAttribsARB faile to create a render context.\n");

        Assert(wglMakeCurrent(data->deviceContext, data->renderContext), "Failed to make the render context current.\n");

        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB)
        {
            const char * wglExtensions = wglGetExtensionsStringARB(data->deviceContext);

            // Debug::Print((char *)wglExtensions);
            printf(wglExtensions);
        }
        else
        {
            Debug::Win32HandleError();

            return false;
        }

        // Debug::Print((char *)glGetString(GL_VENDOR));
        // Debug::Print((char *)glGetString(GL_VERSION));

        return true;
        //--- END GET EXTENSION RENDER CONTEXT ---//
    }


    Bool32 SwapBuffers (PlatformData * data)
    {
        Assert(data->deviceContext, "gPlatformData.deviceContext error.\n");

        if (!::SwapBuffers(data->deviceContext))
        {
            Debug::Win32HandleError();

            return false;
        }

        return true;
    }


    Bool32 DeleteContext (PlatformData * data)
    {
        if (!data->renderContext)
        {
            Debug::Print("Tried to delete a render context with no current context.");

            return false;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(data->renderContext);

        data->renderContext = NULL;

        return true;
    }


    void * GetFunctionAddress (char * name)
    {
        void * proc = wglGetProcAddress(name);

        /*
            Although the specification says wglGetProcAddress only returns NULL on failure.
            Some implementations also return 1, 2, 3 and -1.

            https://msdn.microsoft.com/en-us/library/windows/desktop/dd374386%28v=vs.85%29.aspx
            https://www.opengl.org/wiki/Load_OpenGL_Functions#Windows
        */
        if( proc == 0 || (proc == (void*)0x1) || (proc == (void*)0x2) ||
           (proc == (void*)0x3) || (proc == (void*)-1)
        )
        {
            // Failed to load from the new context, try loading directly from the opengl32.dll.
            HMODULE dll = LoadLibrary("opengl32.dll");

            Assert(dll, "Failed to load opengl32.dll.\n");

            proc = (void *)GetProcAddress(dll, name);

            Assert(proc, "Failed to load OpenGL procedure: %s.\n", name);
        }

        return proc;
    }
}
}
}
