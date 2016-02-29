#include "Platform/OpenGLContext.h"

#include <windows.h>
#include <Wingdi.h>
#include <gl/GL.h>

#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/Win32/Debug.h"
#include "Platform/Win32/WGLExtensions.h"

#include "strings.h"


PFNWGLGETEXTENSIONSSTRINGARB      wglGetExtensionsStringARB;
PFNWGLCREATECONTEXTATTRIBSARB     wglCreateContextAttribsARB;


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

        PIXELFORMATDESCRIPTOR desiredPixelFormat = {};
        desiredPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        desiredPixelFormat.nVersion = 1;
        desiredPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        desiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
        desiredPixelFormat.cColorBits = 24;
        desiredPixelFormat.cAlphaBits = 8;
        desiredPixelFormat.cAccumBits = 0;
        desiredPixelFormat.cDepthBits = 24;
        desiredPixelFormat.cStencilBits = 8;

        //--- START TEMP RENDER CONTEXT ---//
        int pixelFormat = ChoosePixelFormat(deviceContext, &desiredPixelFormat);

        assert(pixelFormat);

        PIXELFORMATDESCRIPTOR suggestedPixelFormat = {};
        assert(DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggestedPixelFormat), &suggestedPixelFormat));

        assert(SetPixelFormat(deviceContext, pixelFormat, &suggestedPixelFormat));

        renderContext = wglCreateContext(deviceContext);

        assert(renderContext);

        wglMakeCurrent(deviceContext, renderContext);

        //--- START GET wglExtensions ---//
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

        if (!wglGetExtensionsStringARB)
        {
            Debug::Win32HandleError();
        }

        const char * extensions = wglGetExtensionsStringARB(deviceContext);

        Bool32 HasWglARBCreateContext = String::Find(extensions, "WGL_ARB_create_context");
        Bool32 HasWglARBCreateContextProfile = String::Find(extensions, "WGL_ARB_create_context_profile");

        if (HasWglARBCreateContext && HasWglARBCreateContextProfile)
        {
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARB)wglGetProcAddress("wglCreateContextAttribsARB");

            assert(wglCreateContextAttribsARB);
        }

        DeleteContext();
        //--- END GET wglExtensions ---//
        //--- END TEMP RENDER CONTEXT ---//

        //--- START GET EXTENSION RENDER CONTEXT ---//
        pixelFormat = ChoosePixelFormat(deviceContext, &desiredPixelFormat);

        if (!pixelFormat)
        {
            Debug::Win32HandleError();

            return false;
        }

        suggestedPixelFormat = {};

        if (!DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggestedPixelFormat), &suggestedPixelFormat))
        {
            Debug::Win32HandleError();

            return false;
        }

        if (!SetPixelFormat(deviceContext, pixelFormat, &suggestedPixelFormat))
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
            GLenum code = GL_NO_ERROR;
            code = glGetError();

            if (code != GL_NO_ERROR)
            {
                Debug::OutputString("OpenGL error: %d", code);
            }

            Debug::Win32HandleError();

            return false;
        }

        if (!wglMakeCurrent(deviceContext, renderContext))
        {
            Debug::Win32HandleError();

            return false;
        }

        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

        if (wglGetExtensionsStringARB)
        {
            const char * wglExtensions = wglGetExtensionsStringARB(deviceContext);

            Debug::OutputString((char *)wglExtensions);
        }
        else
        {
            Debug::Win32HandleError();

            return false;
        }

        Debug::OutputString((char *)glGetString(GL_VENDOR));
        Debug::OutputString((char *)glGetString(GL_VERSION));

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
            Debug::OutputString("Tried to delete a render context with no current context.");

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
            Debug::Win32HandleError();
        }

        return proc;
    }
}
}
