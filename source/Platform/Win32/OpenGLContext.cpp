#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <Wingdi.h>

#include "Capstan/Common.h"
#include "Capstan/Strings.h"
#include "Capstan/Utils.h"

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Win32/Debug.h"

#include "Capstan/Graphics/OpenGL/OpenGL.h"
#include "Capstan/Platform/OpenGLContext.h"

// NOTE (Emil): wglext.h is dependent on gl.h.
#include "gl/wglext.h"


internal PFNWGLGETEXTENSIONSSTRINGARBPROC  wglGetExtensionsStringARB = nullptr;
internal PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;


namespace Capstan
{
namespace Platform
{
    internal HDC deviceContext = 0;
    internal HGLRC renderContext = 0;


    Bool32 CreateContext (void)
    {
        HWND windowHandle = GetActiveWindow();
        deviceContext = GetDC(windowHandle);

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
        Int32 pixelFormat = ChoosePixelFormat(deviceContext, &desired);
        assert(pixelFormat);

        PIXELFORMATDESCRIPTOR suggested = {};
        assert(DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggested), &suggested));

        assert(SetPixelFormat(deviceContext, pixelFormat, &suggested));

        renderContext = wglCreateContext(deviceContext);
        assert(renderContext);

        wglMakeCurrent(deviceContext, renderContext);

        //--- START GET wglExtensions ---//
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB)
        {
            const char * extensions = wglGetExtensionsStringARB(deviceContext);

            Bool32 HasWglARBCreateContext = String::Find(extensions, "WGL_ARB_create_context");
            Bool32 HasWglARBCreateContextProfile = String::Find(extensions, "WGL_ARB_create_context_profile");

            if (HasWglARBCreateContext && HasWglARBCreateContextProfile)
            {
                wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

                assert(wglCreateContextAttribsARB);
            }
        }
        else
        {
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

            assert(wglCreateContextAttribsARB);
        }



        DeleteContext();
        //--- END GET wglExtensions ---//
        //--- END TEMP RENDER CONTEXT ---//

        //--- START GET EXTENSION RENDER CONTEXT ---//
        pixelFormat = ChoosePixelFormat(deviceContext, &desired);

        if (!pixelFormat)
        {
            Debug::Win32HandleError();

            return false;
        }

        suggested = {};

        if (!DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggested), &suggested))
        {
            Debug::Win32HandleError();

            return false;
        }

        if (!SetPixelFormat(deviceContext, pixelFormat, &suggested))
        {
            Debug::Win32HandleError();

            return false;
        }

        int attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        renderContext = wglCreateContextAttribsARB(deviceContext, 0, attributes);

        if (!renderContext)
        {
            // GLenum code = GL_NO_ERROR;
            // code = glGetError();

            // if (code != GL_NO_ERROR)
            // {
            //     Debug::Print("OpenGL error: %d", code);
            // }

            Debug::Win32HandleError();

            return false;
        }

        if (!wglMakeCurrent(deviceContext, renderContext))
        {
            Debug::Win32HandleError();

            return false;
        }

        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB)
        {
            const char * wglExtensions = wglGetExtensionsStringARB(deviceContext);

            Debug::Print((char *)wglExtensions);
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


    Bool32 SwapBuffers (void)
    {
        assert(deviceContext)

        if (!::SwapBuffers(deviceContext))
        {
            Debug::Win32HandleError();

            return false;
        }

        return true;
    }


    Bool32 DeleteContext (void)
    {
        if (!renderContext)
        {
            Debug::Print("Tried to delete a render context with no current context.");

            return false;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(renderContext);

        renderContext = 0;

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

            if (dll == NULL)
            {
                Debug::Win32HandleError();

                assert(false);
            }

            proc = (void *)GetProcAddress(dll, name);

            if (proc == 0)
            {
                Debug::Win32HandleError();

                assert(false);
            }
        }

        return proc;
    }
}
}
