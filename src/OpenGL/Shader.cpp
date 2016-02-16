#include "OpenGL/Shader.h"

#include "AssetManager.h"
#include "assets.h"
#include "assert.h"
#include "debug.h"
#include "memory.h"
#include "SystemManager.h"


namespace Capstan
{
    Shader::Shader (char * filename, ShaderStage stage)
    {
        AssetManager * gAssetManager = (AssetManager *)System::Get(System::Type::Asset);

        GLenum shaderStage;

        switch (stage)
        {
            case ShaderStage::Vertex:
            {
                shaderStage = GL_VERTEX_SHADER;
            } break;
            case ShaderStage::Fragment:
            {
                shaderStage = GL_FRAGMENT_SHADER;
            } break;
            default:
            {
                Debug::OutputString("Illegal OpenGL Shader type.");
            } break;
        }

        this->id = glCreateShader(shaderStage);
        ShaderAsset asset = gAssetManager->LoadShader(filename);
        glShaderSource(this->id, 1, &asset.source, NULL);

        glCompileShader(this->id);

        GLint success;
        glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(this->id, 512, NULL, infoLog);
            Debug::OutputString("VertexShader failed to compile: %s", infoLog);

            assert(success);
        }

        Core::Free(asset.source);
    }

    Shader::~Shader (void)
    {
        glDeleteShader(this->id);
    }

    GLuint Shader::GetId (void)
    {
        return this->id;
    }
}
