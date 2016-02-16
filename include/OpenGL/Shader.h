#ifndef CAPSTAN_OPENGL_SHADER_H
#define CAPSTAN_OPENGL_SHADER_H

#include "OpenGL.h"
#include "types.h"


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
        Shader (char * filename, ShaderStage stage);
        ~Shader (void);

        GLuint GetId (void);
    private:
        GLuint id;
    };
}


#endif
