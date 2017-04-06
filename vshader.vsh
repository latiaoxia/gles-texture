#version 300 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fColor;
out vec2 fTexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    fColor = color;
    fTexCoord = texCoord;
}
