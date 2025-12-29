#include <Lumeda/Implementation/OpenGL/GizmosOpenGL.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Core/Transform.h>

using namespace Lumeda;

const char* SHADER_VERT = "#version 460 core \n \
layout (location = 0) in vec3 a_Pos; \
uniform mat4 u_CameraMatrix; \
uniform mat4 u_World; \
void main() \
{ \
	gl_Position = u_CameraMatrix * u_World * vec4(a_Pos, 1.0); \
}";

const char* SHADER_FRAG = "#version 460 core \n \
out vec4 FragColor; \
uniform vec4 u_Color; \
void main() \
{ \
FragColor = u_Color; \
}";

const float CUBE_OFF = 1.0f;

const std::vector<float> CUBE_VERTS = {
    -CUBE_OFF, CUBE_OFF, CUBE_OFF,
    CUBE_OFF, CUBE_OFF, CUBE_OFF,
    CUBE_OFF, CUBE_OFF, -CUBE_OFF,
    -CUBE_OFF, CUBE_OFF, -CUBE_OFF,

    -CUBE_OFF, -CUBE_OFF, CUBE_OFF,
    CUBE_OFF, -CUBE_OFF, CUBE_OFF,
    CUBE_OFF, -CUBE_OFF, -CUBE_OFF,
    -CUBE_OFF, -CUBE_OFF, -CUBE_OFF,
};

const std::vector<unsigned int> CUBE_INDICES = {
    // Top Side
    2, 0, 1,
    2, 3, 0,

    // Bottom side
    4, 7, 6,
    4, 6, 5,

    // Front Side
    3, 6, 7,
    3, 2, 6,

    // Right Side
    2, 1, 5,
    2, 5, 6,

    // Back Side
    0, 5, 1,
    0, 4, 5,

    // Left Side
    4, 0, 3,
    4, 3, 7
};

GizmosOpenGL::GizmosOpenGL()
{
    LUMEDA_PROFILE;
}

GizmosOpenGL::~GizmosOpenGL()
{
    LUMEDA_PROFILE;
}

void GizmosOpenGL::Initialize()
{
    LUMEDA_PROFILE;

    Renderer& renderer = Engine::Get().GetRenderer();
    m_Shader = renderer.CreateShaderFromSource("GizmosShader", SHADER_VERT, SHADER_FRAG);
    m_Material = renderer.CreateMaterial("GizmosMaterial");
    m_Material->SetShader(m_Shader);

    m_Cube = renderer.CreateMesh("GizmosCube", CUBE_VERTS, CUBE_INDICES, { { 0, 3, Lumeda::MeshAttribType::FLOAT } });
}

void GizmosOpenGL::Terminate()
{
    LUMEDA_PROFILE;
}

void GizmosOpenGL::DrawCube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    LUMEDA_PROFILE;
    Transform dummy;
    dummy.SetLocalPosition(position);
    dummy.SetLocalRotationEulerAngles(rotation);
    dummy.SetLocalScale(scale);

    sUniformsMap uniforms;
    uniforms.Set("u_Color", m_CurrentColor);
    uniforms.Set("u_World", dummy.GetWorld());
    Engine::Get().GetRenderer().Submit(m_Cube, m_Material, uniforms);
}

void GizmosOpenGL::SetColor(const glm::vec4& color)
{
    LUMEDA_PROFILE;
    m_CurrentColor = color;
}