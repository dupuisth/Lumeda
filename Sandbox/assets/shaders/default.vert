#version 460 core

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4
#define MAX_DIRECTIONNAL_LIGHTS 2

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Uv;
layout (location = 2) in vec3 a_Norm;

struct PointLight
{
	vec3 position;
	vec3 color;
	float polynomial;
	float linear;
	float constant;
	float intensity;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float polynomial;
	float linear;
	float constant;
	float intensity;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform mat4 u_CameraMatrix;
uniform mat4 u_World;
uniform PointLight u_PointLight[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLight[MAX_SPOT_LIGHTS];
uniform DirectionalLight u_DirectionalLight[MAX_DIRECTIONNAL_LIGHTS];
uniform int u_PointLightsCount;
uniform int u_SpotLightsCount;
uniform int u_DirectionnalLightsCount;

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