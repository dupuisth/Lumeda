#version 460 core

in vec2 f_Uv;

out vec4 FragColor;

uniform sampler2D u_ColorTexture;
uniform sampler2D u_DepthStencilTexture;

void main()
{
    float ds = length(vec4(1.0) - texture(u_DepthStencilTexture, f_Uv));
    vec4 color = texture(u_ColorTexture, f_Uv);
    FragColor = color;
}