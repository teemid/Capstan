#ifndef CAPSTAN_OPENGL_SHADER_H
#define CAPSTAN_OPENGL_SHADER_H


#include "Platform/Types.h"

#include "OpenGL/gl.h"


namespace Capstan
{
    enum class ShaderStage
    {
        Vertex,
        Fragment
    };


    class Shader
    {
    public:
        Shader (void);
        Shader (GLchar * vertexShader, GLchar * fragmentShader);
        ~Shader (void);

        void Use (void);
    private:
        GLuint Compile (GLenum shaderStage, GLchar ** shaderSource);
        void Link (void);

        GLuint program;
    };
}


#endif
