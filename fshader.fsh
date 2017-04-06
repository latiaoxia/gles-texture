#version 300 es
#ifdef GL_FRAGMENT_PRECISION_HIGH
  precision highp float;
#else
  precision mediump float;
#endif

in vec3 fColor;
in vec2 fTexCoord;

out vec4 color;

uniform sampler2D fTexture;

void main()
{
    color = texture(fTexture, fTexCoord);
}
