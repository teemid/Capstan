#version 330 core

// layout (row_major) uniform;
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 textureCoordinates;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoord = textureCoordinates;
}
