#version 330 core
layout (location = 0) in vec3 posIn;
layout (location = 1) in vec4 colorIn;

out vec4 color;

void main()
{
    gl_Position = vec4(posIn.x, posIn.y, posIn.z, 1.0);
    color = colorIn;
}