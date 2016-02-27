#include "OpenGL/OpenGL.h"


#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/FileSystem.h"
#include "Platform/Memory.h"
#include "Platform/OpenGLContext.h"
#include "Platform/Win32/Debug.h"
#include "Platform/Win32/WGLExtensions.h"

#include "strings.h"
#include "types.h"
#include "utils.h"


// NOTE (Emil): This brings in the OpenGL function declarations used in LoadFunctions (void).
#include "OpenGL/Functions.inl"


namespace Capstan
{
    #define GetFunction(type, name) name = (type)Platform::GetFunctionAddress(#name)

    void LoadFunctions (void)
    {
        GetFunction(PFNGLGENBUFFERSPROC,              glGenBuffers             );
        GetFunction(PFNGLBINDBUFFERPROC,              glBindBuffer             );
        GetFunction(PFNGLBUFFERDATAPROC,              glBufferData             );

        GetFunction(PFNGLCREATESHADERPROC,            glCreateShader           );
        GetFunction(PFNGLDELETESHADERPROC,            glDeleteShader           );
        GetFunction(PFNGLSHADERSOURCEPROC,            glShaderSource           );
        GetFunction(PFNGLCOMPILESHADERPROC,           glCompileShader          );
        GetFunction(PFNGLGETSHADERIVPROC,             glGetShaderiv            );
        GetFunction(PFNGLGETSHADERINFOLOGPROC,        glGetShaderInfoLog       );

        GetFunction(PFNGLCREATEPROGRAMPROC,           glCreateProgram          );
        GetFunction(PFNGLATTACHSHADERPROC,            glAttachShader           );
        GetFunction(PFNGLLINKPROGRAMPROC,             glLinkProgram            );
        GetFunction(PFNGLUSEPROGRAMPROC,              glUseProgram             );
        GetFunction(PFNGLGETPROGRAMIVPROC,            glGetProgramiv           );
        GetFunction(PFNGLGETPROGRAMINFOLOGPROC,       glGetProgramInfoLog      );

        GetFunction(PFNGLVERTEXATTRIBPOINTERPROC,     glVertexAttribPointer    );
        GetFunction(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);

        GetFunction(PFNGLGENVERTEXARRAYSPROC,         glGenVertexArrays        );
        GetFunction(PFNGLBINDVERTEXARRAYPROC,         glBindVertexArray        );
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


    internal void Setup (void)
    {
        glViewport(0, 0, 800, 600);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        GLint attributeCount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeCount);
        Debug::OutputString("Vertex Attributes: %d", attributeCount);
    }


    OpenGL::OpenGL (void) : shader(nullptr) { }


    OpenGL::~OpenGL (void)
    {
        delete this->shader;
    }

    // NOTE (Emil): These are for the tutorial, void Tutorial (void).
    internal GLuint vertexArrayObject = 0;

    void OpenGL::StartUp (void)
    {
        Platform::CreateContext();
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
        Platform::DeleteContext();
    }


    void OpenGL::Render (void)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        this->shader->Use();

        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        Platform::SwapBuffers();
    }

}
