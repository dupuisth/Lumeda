#version 460

///////////////////////////////////////////
// LAYOUT
///////////////////////////////////////////
layout (location = 0) in vec3 v_Pos;
layout (location = 1) in vec2 v_Uv;
layout (location = 2) in vec3 v_Norm;

///////////////////////////////////////////
// UNIFORMS
///////////////////////////////////////////
uniform mat4 u_World;
uniform vec3 u_Position;
uniform mat4 u_Camera;
uniform float u_UvScale;

///////////////////////////////////////////
// OUT
///////////////////////////////////////////
out vec2 f_Uv;
out vec3 f_Normal;
out vec3 f_LocalPosition;
out vec3 f_WorldPosition;
out vec2 f_ScreenPosition;


///////////////////////////////////////////
// Shader
///////////////////////////////////////////
void main()
{
    f_Uv = v_Uv * u_UvScale;
    // Thanks https://learnopengl.com/Lighting/Basic-Lighting
    f_Normal = mat3(transpose(inverse(u_World))) * v_Norm;
    f_LocalPosition = v_Pos;
    f_WorldPosition = (u_World * vec4(f_LocalPosition, 1.0)).xyz;

    vec4 finalPosition = u_Camera * vec4(f_WorldPosition, 1.0);
    f_ScreenPosition = finalPosition.xy;

    gl_Position = finalPosition;
}