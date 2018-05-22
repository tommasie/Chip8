#version 330 core
in vec2 TexCoord;

uniform sampler2D display;

void main()
{
    gl_FragColor = texture2D(display, TexCoord);
}