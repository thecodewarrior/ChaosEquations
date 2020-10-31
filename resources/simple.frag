#version 330 core
out vec4 FragColor;
uniform float time;

void main()
{
//    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(mod(time, 1.0), mod(time + 0.333, 1.0), mod(time + 0.666, 1.0), 1.0);
}