#ifndef CAPSTAN_OPENGL_PROGRAM_H
#define CAPSTAN_OPENGL_PROGRAM_H


#include "OpenGL.h"
#include "Shader.h"


namespace Capstan
{
    class Program
    {
    public:
        Program (void);
        ~Program (void);

        void Attach (Shader shader);
        void Link (void);
        void Use (void);

        GLuint GetId(void);
    private:
        GLuint id;
    };
}

#endif
