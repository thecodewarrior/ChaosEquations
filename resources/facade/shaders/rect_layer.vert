#version 330 core
in vec2 pos;
in vec4 colorIn;

uniform mat4 transform;

out vec4 color;

void main()
{
    gl_Position = transform * vec4(pos, 0.0, 1.0);
    color = colorIn;
}