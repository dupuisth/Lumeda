#version 460

in vec2 f_Uv;

out vec4 FragColor;

uniform sampler2D u_Color;

void main() {
    FragColor = texture(u_Color, f_Uv);
}