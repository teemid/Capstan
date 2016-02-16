#ifndef CAPSTAN_WGL_EXTENSIONS_H
#define CAPSTAN_WGL_EXTENSIONS_H


#include <windows.h>


// const char * wglGetExtensionsStringARB(HDC hdc);
typedef const char * (* PFNWGLGETEXTENSIONSSTRINGARB) (HDC hdc);


// HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int *attribList);
typedef HGLRC (* PFNWGLCREATECONTEXTATTRIBSARB) (HDC hdc, HGLRC hShareContext, const int * attribList);

// Accepted as an attribute name in <*attribList>:

#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            0x9126


#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002

// Accepted as bits in the attribute value for WGL_CONTEXT_PROFILE_MASK_ARB in <*attribList>:

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

// New errors returned by GetLastError:

#define ERROR_INVALID_VERSION_ARB               0x2095
#define ERROR_INVALID_PROFILE_ARB               0x2096


#endif
