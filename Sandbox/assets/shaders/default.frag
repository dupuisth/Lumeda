#version 460

in vec2 f_Uv;
in vec3 f_LocalPosition;
in vec3 f_WorldPosition;
in vec3 f_Normal;

out vec4 FragColor;

uniform sampler2D u_Color;

void main() {
    vec4 diffuse = texture(u_Color, f_Uv);

    float d = length(f_WorldPosition);
    float intensity = (1 / ( pow(d, 2) + 2 * d + 1)) * 1.0;

    FragColor = diffuse * intensity;
}