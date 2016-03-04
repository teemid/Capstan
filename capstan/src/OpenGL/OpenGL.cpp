#include "OpenGL/OpenGL.h"


#include "Platform/Assert.h"
#include "Platform/Debug.h"
#include "Platform/FileSystem.h"
#include "Platform/Memory.h"
#include "Platform/OpenGLContext.h"
#include "Platform/Types.h"
#include "Platform/Win32/Debug.h"
#include "Platform/Win32/WGLExtensions.h"

#include "AssetManager.h"
#include "strings.h"
#include "SystemManager.h"

#include "Math/Matrix4f.h"
#include "Math/Vector4f.h"

#include "utils.h"


// NOTE (Emil): This brings in the OpenGL function declarations used in LoadFunctions (void).
#include "FunctionDeclarations.inl"


namespace Capstan
{
    #define GetFunction(type, name) name = (type)Platform::GetFunctionAddress(#name)

    void LoadFunctions (void)
    {
        #include "LoadFunctions.inl"
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

    // TODO (Emil): Remove tutorial code.
    internal GLuint vertexArrayObject = 0;
    internal GLuint texture = 0;

    void OpenGL::StartUp (void)
    {
        Platform::CreateContext();
        LoadFunctions();
        Setup();

        this->shader = new Shader("shaders/simple.vert.glsl", "shaders/simple.frag.glsl");

        this->shader->Use();

        // BEGIN Tutorial
        // This code should not be here after this is more fleshed out.

        GLfloat vertices[] = {
            // Positions          // Colors           // Texture Coords
            0.2f * 0.5f, 0.2f * 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
            0.2f * 0.5f, 0.2f *-0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
            0.2f *-0.5f, 0.2f *-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
            0.2f *-0.5f, 0.2f * 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
        };

        GLuint indices[] = { 0, 1, 3, 1, 2, 3 };

        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);

        GLuint vertexBufferObject;
        GLuint elementBufferObject;
        glGenBuffers(1, &vertexBufferObject);
        glGenBuffers(1, &elementBufferObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // NOTE (Emil): This is the index specified in the vertex shader, (location = 0).
        glVertexAttribPointer(
            0, // attrib index
            3, // components per vertex attrib
            GL_FLOAT, // component type
            GL_FALSE, // normalized data?
            8 * sizeof(GLfloat), // stride, 0 is also accepted when the data is tightly packed.
            (GLvoid*)0 // offset to start of data, in this case 0
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(GLfloat),
            (GLvoid*)(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(
            2, // atrib index
            2,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(GLfloat),
            (GLvoid *)(6 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);  // NOTE (Emil): Unbind the VAO

        AssetManager * gAssetManager = (AssetManager *)System::Get(System::Type::Asset);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        ImageAsset image = gAssetManager->LoadTexture("images/heart.bmp");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
        glBindTexture(GL_TEXTURE_2D, 0);

        Vector4f v = { 1.0f, 1.0f, 1.0f, 1.0f };
        Matrix4f m = Translate(Vector3f(1.0f, 1.0f, 0.0f));

        v = m * v;
    }


    void OpenGL::ShutDown (void)
    {
        Platform::DeleteContext();

        delete this->shader;
    }


    void OpenGL::Render (void)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        this->shader->Use();

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        Platform::SwapBuffers();
    }
}
