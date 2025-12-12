#version 460

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4
#define MAX_DIRECTIONNAL_LIGHTS 2

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
	float angle;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float intensity;
};

in vec2 f_Uv;
in vec3 f_LocalPosition;
in vec3 f_WorldPosition;
in vec3 f_Normal;

out vec4 FragColor;

uniform sampler2D u_Color;
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
uniform DirectionalLight u_DirectionalLights[MAX_DIRECTIONNAL_LIGHTS];
uniform int u_PointLightsCount;
uniform int u_SpotLightsCount;
uniform int u_DirectionnalLightsCount;

vec4 calculatePoint(PointLight light)
{
	float d = distance(light.position, f_WorldPosition);
	float intensity = 1 / (light.polynomial * pow(d, 2) + light.linear * d + light.constant);
	intensity *= light.intensity;

	return vec4(light.color * intensity, 1.0);
}

vec4 calculateSpot(SpotLight light)
{
	return vec4(0.0);
}

vec4 calculateDirectionnal(DirectionalLight light)
{
	return vec4(0.0);
}

vec4 calculateLights()
{
	vec4 sumLights = vec4(0.0);

	for (int i = 0; i < min(MAX_POINT_LIGHTS, u_PointLightsCount); i++)
	{
		sumLights += calculatePoint(u_PointLights[i]);
	}

	for (int i = 0; i < min(MAX_SPOT_LIGHTS, u_SpotLightsCount); i++)
	{
		sumLights += calculateSpot(u_SpotLights[i]);
	}

	for (int i = 0; i < min(MAX_DIRECTIONNAL_LIGHTS, u_DirectionnalLightsCount); i++)
	{
		sumLights += calculateDirectionnal(u_DirectionalLights[i]);
	}

	return sumLights;
}

void main() {
    vec4 diffuse = texture(u_Color, f_Uv);

    FragColor = diffuse * calculateLights();
}