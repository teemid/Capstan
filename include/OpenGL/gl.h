#ifndef CAPSTAN_GL_H
#define CAPSTAN_GL_H

#ifdef CAPSTAN_WIN32
#include <windows.h>
#endif
#include <gl/Gl.h>
#include "gl/glext.h"


extern PFNGLGENBUFFERSPROC               glGenBuffers;
extern PFNGLBINDBUFFERPROC               glBindBuffer;
extern PFNGLBUFFERDATAPROC               glBufferData;

extern PFNGLCREATESHADERPROC             glCreateShader;
extern PFNGLDELETESHADERPROC             glDeleteShader;
extern PFNGLSHADERSOURCEPROC             glShaderSource;
extern PFNGLCOMPILESHADERPROC            glCompileShader;
extern PFNGLGETSHADERIVPROC              glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog;

extern PFNGLCREATEPROGRAMPROC            glCreateProgram;
extern PFNGLDELETEPROGRAMPROC            glDeleteProgram;
extern PFNGLATTACHSHADERPROC             glAttachShader;
extern PFNGLLINKPROGRAMPROC              glLinkProgram;
extern PFNGLUSEPROGRAMPROC               glUseProgram;
extern PFNGLGETPROGRAMIVPROC             glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog;

extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribPointer;

extern PFNGLGENVERTEXARRAYSPROC          glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC          glBindVertexArray;


namespace Capstan
{
    void LoadFunctions (void);
}

#endif
