Matrix memory layout
====================

OpenGL defaults to column major matrix layout, you can specify the memory layout in a shader.
The function signature of glUniformMatrix4fv is:

    glUniformMatrix4fv(GLint location, Glsizei count, GLboolean transpose, const GLfloat * value);

Atleast for OpenGL ES transpose must always be GL_FALSE according to the docs (https://www.khronos.org/opengles/sdk/docs/man/xhtml/glUniform.xml).

    layout(row_major) uniform;

This will make all uniforms use row_major memory layout. This does not affect how opengl stores matrices.
What it does is determine how OpenGL reads data from the buffer.

See: https://www.opengl.org/wiki/Interface_Block_%28GLSL%29#Matrix_storage_order
