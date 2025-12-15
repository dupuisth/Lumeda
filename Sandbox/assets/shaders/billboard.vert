#version 460 core
layout (location = 0) in vec3 aPos;

out vec2 f_Uv;

uniform vec3 u_Position;
uniform mat4 u_CameraView;
uniform mat4 u_CameraProjection;
uniform vec2 u_Size;

mat3 RotationMatrix(float angle) {
    mat3 rot;
    rot[0] = vec3(cos(angle), -sin(angle), 0.0);
    rot[1] = vec3(sin(angle), cos(angle), 0.0);
    rot[2] = vec3(0.0, 0.0, 1.0);
    return rot;
}

void main() 
{
    uv = vec2(aPos.x + 0.5, aPos.y + 0.5);
    
    vec3 localPos = aPos;

    vec3 right = vec3(CameraView[0][0], CameraView[1][0], CameraView[2][0]);
    vec3 up = vec3(CameraView[0][1], CameraView[1][1], CameraView[2][1]);

    vec3 worldPos = Position 
                  + right * localPos.x * Size.x
                  + up * localPos.y * Size.y;
    
    gl_Position = CameraProjection * CameraView * vec4(worldPos, 1.0);
}