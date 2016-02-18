#include "OpenGL/OpenGL.h"
// #include "OpenGL/Shader.h"

#include "assert.h"
#include "debug.h"
#include "FileSystem.h"
#include "types.h"

#include "strings.h"
#include "utils.h"
#include "memory.h"
#include "Win32/Win32Debug.h"
#include "Win32/WGLExtensions.h"

// NOTE (Emil): This brings in the OpenGL function declarations used in LoadFunctions (void).
#include "OpenGL/Functions.inl"

namespace Capstan
{
    internal HDC deviceContext = 0;
    internal HGLRC renderContext = 0;


    // NOTE (Emil): These are for the tutorial, void Tutorial (void).
    internal GLuint vertexArrayObject = 0;


    #define GetFunctionAddress(type, name) name = (type)wglGetProcAddress(#name); \
                    assert(name != 0 || name != (void*)0x1 || name != (void*)0x2 || name != (void*)0x3 || name != (void*)-1)

    void LoadFunctions (void)
    {
        GetFunctionAddress(PFNGLGENBUFFERSPROC,              glGenBuffers);
        GetFunctionAddress(PFNGLBINDBUFFERPROC,              glBindBuffer);
        GetFunctionAddress(PFNGLBUFFERDATAPROC,              glBufferData);

        GetFunctionAddress(PFNGLCREATESHADERPROC,            glCreateShader);
        GetFunctionAddress(PFNGLDELETESHADERPROC,            glDeleteShader);
        GetFunctionAddress(PFNGLSHADERSOURCEPROC,            glShaderSource);
        GetFunctionAddress(PFNGLCOMPILESHADERPROC,           glCompileShader);
        GetFunctionAddress(PFNGLGETSHADERIVPROC,             glGetShaderiv);
        GetFunctionAddress(PFNGLGETSHADERINFOLOGPROC,        glGetShaderInfoLog);

        GetFunctionAddress(PFNGLCREATEPROGRAMPROC,           glCreateProgram);
        GetFunctionAddress(PFNGLATTACHSHADERPROC,            glAttachShader);
        GetFunctionAddress(PFNGLLINKPROGRAMPROC,             glLinkProgram);
        GetFunctionAddress(PFNGLUSEPROGRAMPROC,              glUseProgram);
        GetFunctionAddress(PFNGLGETPROGRAMIVPROC,            glGetProgramiv);
        GetFunctionAddress(PFNGLGETPROGRAMINFOLOGPROC,       glGetProgramInfoLog);

        GetFunctionAddress(PFNGLVERTEXATTRIBPOINTERPROC,     glVertexAttribPointer);
        GetFunctionAddress(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);

        GetFunctionAddress(PFNGLGENVERTEXARRAYSPROC,         glGenVertexArrays);
        GetFunctionAddress(PFNGLBINDVERTEXARRAYPROC,         glBindVertexArray);
    }


    internal void GetError (void)
    {
        GLenum code = GL_NO_ERROR;
        code = glGetError();

        if (code != GL_NO_ERROR)
        {
            Debug::OutputString("OpenGL error: %d", code);
        }
    }


    internal void CreateTemporaryContext(PIXELFORMATDESCRIPTOR * desiredPixelFormat)
    {
        int pixelFormat = ChoosePixelFormat(deviceContext, desiredPixelFormat);

        assert(pixelFormat);

        PIXELFORMATDESCRIPTOR suggestedPixelFormat = {};
        assert(DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggestedPixelFormat), &suggestedPixelFormat));

        assert(SetPixelFormat(deviceContext, pixelFormat, &suggestedPixelFormat));

        renderContext = wglCreateContext(deviceContext);

        assert(renderContext);

        wglMakeCurrent(deviceContext, renderContext);
    }


    internal void DeleteContext (void)
    {
        if (!renderContext)
        {
            Debug::OutputString("Tried to delete a render context with no current context.");
            return;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(renderContext);
        renderContext = 0;
    }


    internal Bool32 GetWglARBFunctions ()
    {
        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

        if (!wglGetExtensionsStringARB)
        {
            Debug::Win32HandleError();
        }

        const char * extensions = wglGetExtensionsStringARB(deviceContext);

        Bool32 HasWglARBCreateContext = Find(extensions, "WGL_ARB_create_context");
        Bool32 HasWglARBCreateContextProfile = Find(extensions, "WGL_ARB_create_context_profile");

        if (HasWglARBCreateContext && HasWglARBCreateContextProfile)
        {
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARB)wglGetProcAddress("wglCreateContextAttribsARB");

            assert(wglCreateContextAttribsARB);
        }

        return (HasWglARBCreateContext && HasWglARBCreateContextProfile && wglCreateContextAttribsARB);
    }


    internal int CreateContext (void)
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

        CreateTemporaryContext(&desiredPixelFormat);
        GetWglARBFunctions();
        DeleteContext();

        int pixelFormat = ChoosePixelFormat(deviceContext, &desiredPixelFormat);

        if (!pixelFormat)
        {
            Debug::Win32HandleError();

            return 1;
        }

        PIXELFORMATDESCRIPTOR suggestedPixelFormat = {};

        if (!DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggestedPixelFormat), &suggestedPixelFormat))
        {
            Debug::Win32HandleError();

            return 2;
        }

        if (!SetPixelFormat(deviceContext, pixelFormat, &suggestedPixelFormat))
        {
            Debug::Win32HandleError();

            return 3;
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
            GetError();
            Debug::Win32HandleError();

            return 4;
        }

        if (!wglMakeCurrent(deviceContext, renderContext))
        {
            Debug::Win32HandleError();

            return 5;
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

            return 6;
        }

        Debug::OutputString((char *)glGetString(GL_VENDOR));
        Debug::OutputString((char *)glGetString(GL_VERSION));

        return 0;
    }


    internal void Setup (void)
    {
        glViewport(0, 0, 800, 600);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        GLint attributeCount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeCount);
        Debug::OutputString("Vertex Attributes: %d", attributeCount);
    }


    internal void SwapBuffers (void)
    {
        assert(deviceContext)

        if (!::SwapBuffers(deviceContext))
        {
            Debug::Win32HandleError();
        }
    }


    OpenGL::OpenGL (void) : shader(nullptr) { }


    OpenGL::~OpenGL (void)
    {
        delete this->shader;
    }


    void OpenGL::StartUp (void)
    {
        CreateContext();
        LoadFunctions();
        Setup();

        // BEGIN Tutorial
        // This code should not be here after this is more fleshed out.

        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);

        GLuint vertexBufferObject;
        glGenBuffers(1, &vertexBufferObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // NOTE (Emil): This is the index specified in the vertex shader, (location = 0).
        GLuint index = 0;
        GLint componentsPerVertexAttribute = 3;
        glVertexAttribPointer(
            index, // attrib index
            componentsPerVertexAttribute, // components per vertex attrib
            GL_FLOAT, // component type
            GL_FALSE, // normalized data?
            3 * sizeof(GLfloat), // stride, 0 is also accepted when the data is tightly packed.
            (GLvoid*)0 // offset to start of data, in this case 0
        );
        glEnableVertexAttribArray(0);

        // NOTE (Emil): Unbind the VAO
        glBindVertexArray(0);

        this->shader = new Shader("shaders/simple.vert", "shaders/simple.frag");

        this->shader->Use();
    }


    void OpenGL::ShutDown (void)
    {
        DeleteContext();
    }


    void OpenGL::Render (void)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        this->shader->Use();

        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SwapBuffers();
    }

}
