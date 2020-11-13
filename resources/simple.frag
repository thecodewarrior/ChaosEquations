#version 330 core
in vec4 color;
out vec4 FragColor;
uniform float time;

void main()
{
    FragColor = color * mod(time, 1.0);
}
