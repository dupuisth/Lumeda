#version 460 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Uv;
layout (location = 2) in vec3 a_Norm;

uniform mat4 u_CameraMatrix;
uniform mat4 u_World;

out vec2 f_Uv;
out vec3 f_LocalPosition;
out vec3 f_WorldPosition;
out vec3 f_Normal;

void main()
{
	f_Uv = a_Uv;
	f_Normal = a_Norm;
	f_LocalPosition = a_Pos;
	f_WorldPosition = vec3(u_World * vec4(f_LocalPosition, 1.0));
	gl_Position = u_CameraMatrix * vec4(f_WorldPosition, 1.0);
}