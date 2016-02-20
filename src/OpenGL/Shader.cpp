#include "OpenGL/Shader.h"

#include "AssetManager.h"
#include "assert.h"
#include "debug.h"
#include "memory.h"
#include "SystemManager.h"


namespace Capstan
{
    Shader::Shader (void)
    {
        this->program = 0;
    }

    Shader::Shader (GLchar * vertexShader, GLchar * fragmentShader)
    {
        AssetManager * gAssetManager = (AssetManager *)System::Get(System::Type::Asset);

        ShaderAsset vertexShaderAsset = gAssetManager->LoadShader(vertexShader);
        ShaderAsset fragmentShaderAsset = gAssetManager->LoadShader(fragmentShader);

        this->program = glCreateProgram();

        GLuint vertex = Compile(GL_VERTEX_SHADER, &vertexShaderAsset.source);
        GLuint fragment = Compile(GL_FRAGMENT_SHADER, &fragmentShaderAsset.source);

        glAttachShader(this->program, vertex);
        glAttachShader(this->program, fragment);

        Link();

        glDeleteShader(vertex);
        glDeleteShader(fragment);
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
            GLchar info[512];
            glGetShaderInfoLog(shader, 512, NULL, info);
            Debug::OutputString("Shader failed to compile: %s", info);
            assert(success);
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
            GLchar info[512];
            glGetProgramInfoLog(this->program, 512, NULL, info);
            Debug::OutputString("Shader program failed to link: %s", info);
            assert(success);
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
