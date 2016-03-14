#include "OpenGL/OpenGL.h"
#include "OpenGL/Camera.h"

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
#include "utils.h"

#include "Math/Matrix4f.h"
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"


// NOTE (Emil): Brings in auto generated OpenGL function declarations.
#include "FunctionDeclarations.inl"


namespace Capstan
{
    #define GetFunction(type, name) name = (type)Platform::GetFunctionAddress(#name)

    void LoadFunctions (void)
    {
        // Asks the driver or OpenGL.dll for the functions declared in "FunctionDeclarations.inl"
        #include "LoadFunctions.inl"
    }


    internal void GetError (void)
    {
        GLenum code = GL_NO_ERROR;
        code = glGetError();

        if (code != GL_NO_ERROR)
        {
            Debug::Print("OpenGL error: %d", code);
        }
    }


    internal void Setup (void)
    {
        glViewport(0, 0, 800, 600);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        GLint attributeCount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeCount);
        Debug::Print("Vertex Attributes: %d", attributeCount);
    }


    OpenGL::OpenGL (void) : shader(nullptr) { }


    OpenGL::~OpenGL (void)
    {
        delete this->shader;
    }

    // TODO (Emil): Remove tutorial code.
    internal GLuint vertexArrayObject = 0;
    internal GLuint texture = 0;
    internal Matrix4f model;
    internal Matrix4f view;
    internal Matrix4f projection;

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
            // Positions        // Texture Coords
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // Top Right
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // Bottom Left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // Top Left
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
            5 * sizeof(GLfloat), // stride, 0 is also accepted when the data is tightly packed.
            (GLvoid*)0 // offset to start of data, in this case 0
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            2, // attrib index
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GLfloat),
            (GLvoid *)(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);  // Unbind the VAO

        AssetManager * gAssetManager = (AssetManager *)System::Get(System::Type::Asset);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        ImageAsset image = gAssetManager->LoadTexture("images/heart.bmp");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image.data);
        // glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);


        view = Translate(Vector3f(0.0f, 0.0f, 0.0f));
        projection = Projection::Perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        this->shader->SetUniform("view", UniformType::Matrix4fv, (void *)view.data);
        this->shader->SetUniform("projection", UniformType::Matrix4fv, (void *)projection.data);
    }


    void OpenGL::ShutDown (void)
    {
        Platform::DeleteContext();

        delete this->shader;
    }

    void OpenGL::Render (void)
    {
        static Real32 angle = 0.0f;
        static Vector3f translation = Vector3f(0.0f, 0.0f, 0.0f);

        angle += 0.0002f;
        translation.z -= 0.00001f;

        model = Rotate(angle, Vector3f(1.0f, 0.0f, 0.0f));
        view = Translate(translation);

        this->shader->SetUniform("model", UniformType::Matrix4fv, (void *)model.data);
        this->shader->SetUniform("view", UniformType::Matrix4fv, (void *)view.data);

        glClear(GL_COLOR_BUFFER_BIT);

        this->shader->Use();

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(vertexArrayObject);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        Platform::SwapBuffers();
    }
}
