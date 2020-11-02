#version 330 core
in vec4 color;
out vec4 FragColor;
uniform float time;

void main()
{
    FragColor = color;//vec4(mod(time, 1.0), mod(time + 0.333, 1.0), mod(time + 0.666, 1.0), 1.0);
}
