#include "Capstan/Common.h"
#include "Capstan/Globals.h"

#include "Capstan/Graphics/OpenGL/Shader.h"

#include "Capstan/Platform/Assert.h"
#include "Capstan/Platform/Debug.h"
#include "Capstan/Platform/Memory.h"


namespace Capstan
{
namespace Graphics
{
    Shader::Shader (void)
    {
        this->program = 0;
    }

    Shader::Shader (GLchar * vertexShader, GLchar * fragmentShader)
    {
        ShaderAsset vertexShaderAsset = gAssetManager.LoadShader(vertexShader);
        ShaderAsset fragmentShaderAsset = gAssetManager.LoadShader(fragmentShader);

        this->program = glCreateProgram();

        GLuint vertex = Compile(GL_VERTEX_SHADER, &vertexShaderAsset.source);
        GLuint fragment = Compile(GL_FRAGMENT_SHADER, &fragmentShaderAsset.source);

        glAttachShader(this->program, vertex);
        glAttachShader(this->program, fragment);

        Link();

        glDeleteShader(vertex);
        glDeleteShader(fragment);

#if CAPSTAN_DEBUG
        glValidateProgram(program);

        GLchar info[1024];
        glGetProgramInfoLog(program, 1024, NULL, info);
        Debug::Print("Program info log: %s", info);
#endif
    }

    void Shader::SetUniform (char * name, UniformType type, void * uniform)
    {
        GLuint location = glGetUniformLocation(this->program, name);

        switch (type)
        {
            case UniformType::Matrix4fv:
            {
                glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat *)uniform);
            } break;
            case UniformType::Float3fv:
            {
                glUniform3fv(location, 1, (GLfloat *)uniform);
            } break;
            case UniformType::Float4fv:
            {
                glUniform4fv(location, 1, (GLfloat *)uniform);
            } break;
            ILLEGAL_CASE("There is not default uniform type in Shader.SetUniform");
        }
    }

    GLuint Shader::Compile (GLenum shaderStage, GLchar ** shaderSource)
    {

        GLuint shader = glCreateShader(shaderStage);

        glShaderSource(shader, 1, shaderSource, NULL);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLchar info[1024];
            glGetShaderInfoLog(shader, 1024, NULL, info);
            Assert(success, "Shader failed to compile: %s", info);
        }

        return shader;
    }

    void Shader::Link (void)
    {
        glLinkProgram (this->program);

        GLint success;
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLchar info[1024];
            glGetProgramInfoLog(this->program, 1024, NULL, info);
            Assert(success, "Shader program failed to link: %s", info);
        }
    }

    void Shader::Use (void)
    {
        glUseProgram(this->program);
    }

    Shader::~Shader (void)
    {
        glDeleteProgram(this->program);
    }
}
}
