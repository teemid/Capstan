#ifndef CAPSTAN_GRAPHICS_OPENGL_SHADER_H
#define CAPSTAN_GRAPHICS_OPENGL_SHADER_H

#include "Capstan/Common.h"

#include "Capstan/Graphics/OpenGL/OpenGL.h"


namespace Capstan
{
namespace Graphics
{
    enum class ShaderStage
    {
        Vertex,
        Fragment
    };

    enum class UniformType
    {
        Matrix4fv,
        Float3fv,
        Float4fv,
    };

    class Shader
    {
    public:
        Shader (void);
        Shader (GLchar * vertexShader, GLchar * fragmentShader);
        ~Shader (void);

        void SetUniform(char * name, UniformType type, void * value);

        void Use (void);
    private:
        GLuint Compile (GLenum shaderStage, GLchar ** shaderSource);
        void Link (void);

        GLuint program;
    };
}
}


#endif
