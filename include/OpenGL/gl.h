#ifndef CAPSTAN_GL_H
#define CAPSTAN_GL_H

#include <windows.h>
#include <gl/Gl.h>
#include "gl/glext.h"
#include "Win32/WGLExtensions.h"


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

extern PFNWGLGETEXTENSIONSSTRINGARB      wglGetExtensionsStringARB;
extern PFNWGLCREATECONTEXTATTRIBSARB     wglCreateContextAttribsARB;


namespace Capstan
{
    void LoadFunctions (void);
}

#endif
