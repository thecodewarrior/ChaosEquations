#version 330 core
in vec2 pos;
in vec4 colorIn;

uniform mat3 transform;

out vec4 color;

void main()
{
    gl_Position = vec4(transform * vec3(pos, 1.0), 1.0);
    color = colorIn;
}