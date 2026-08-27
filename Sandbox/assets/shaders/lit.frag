#version 460

///////////////////////////////////////////
// Datatypes
///////////////////////////////////////////
struct sDirectionalLight
{
    vec3 Direction;
    vec3 Color;
};
//---------------------------------------//


///////////////////////////////////////////
// UNIFORMS
///////////////////////////////////////////
uniform sampler2D u_DiffuseTexture0;
uniform sDirectionalLight u_DirectionalLight;
uniform vec3 u_CameraForward;
uniform vec3 u_CameraPosition;
//---------------------------------------//


///////////////////////////////////////////
// IN
///////////////////////////////////////////
in vec2 f_Uv;
in vec3 f_Normal;
in vec3 f_LocalPosition;
in vec3 f_WorldPosition;
in vec2 f_ScreenPosition;
//---------------------------------------//


///////////////////////////////////////////
// OUT
///////////////////////////////////////////
out vec4 FragColor;
//---------------------------------------//

///////////////////////////////////////////
// Shader
///////////////////////////////////////////

vec3 calculateDirectionalLight(sDirectionalLight light)
{
    float dotProduct = dot(f_Normal, -light.Direction);
    vec3 diffuse = light.Color * dotProduct;

    vec3 reflected = reflect(light.Direction, f_Normal);
    vec3 objToCamera = normalize(u_CameraPosition - f_WorldPosition);
    dotProduct = max(0.0, pow(dot(reflected, objToCamera), 32));
    vec3 spec = light.Color * dotProduct;

    return diffuse + spec;
}

void main() {
    vec4 diffuse = texture(u_DiffuseTexture0, f_Uv);
    vec3 sunLight = calculateDirectionalLight(u_DirectionalLight);

    vec3 final = diffuse.xyz * sunLight;

    FragColor = vec4(final.xyz, 1.0);
}