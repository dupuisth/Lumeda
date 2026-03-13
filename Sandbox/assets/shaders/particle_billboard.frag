#version 460 core

in vec2 f_Uv;

out vec4 FragColor;

uniform sampler2D u_Diffuse;

void main() 
{
    vec4 color = texture(u_Diffuse, f_Uv);
    FragColor = color;
}