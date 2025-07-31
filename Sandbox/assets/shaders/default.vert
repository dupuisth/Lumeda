#version 460 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Uv;

uniform mat4 u_CameraMatrix;
uniform mat4 u_World;

out vec2 f_Uv;

void main()
{
	f_Uv = a_Uv;
	gl_Position = u_CameraMatrix * u_World * vec4(a_Pos, 1.0);
}