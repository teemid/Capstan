#include "OpenGL/Program.h"

#include "assert.h"
#include "debug.h"


namespace Capstan
{
    Program::Program (void) { };

    Program::~Program (void) { };

    void Program::Attach (Shader shader)
    {
        this->id = glCreateProgram();

        glAttachShader(this->id, shader.GetId());
    }

    void Program::Link (void)
    {
        glLinkProgram(this->id);

        GLint success;
        glGetProgramiv(this->id, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLchar infoLog[512];
            glGetProgramInfoLog(this->id, 512, NULL, infoLog);
            Debug::OutputString("Program linking failed: %s", infoLog);
            assert(success);
        }
    }

    void Program::Use (void)
    {
        glUseProgram(this->id);
    }
}
