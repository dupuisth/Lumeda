#include <Lumeda/Implementation/OpenGL/GizmosOpenGL.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Core/Transform.h>

using namespace Lumeda;

const char* SHADER_VERT = "#version 460 core \n \
layout (location = 0) in vec3 a_Pos; \n\
uniform mat4 u_CameraMatrix;\n\
uniform mat4 u_World;\n\
out vec3 f_WorldPosition;\n\
out vec4 f_ScreenPosition;\n\
void main()\n\
{\n\
    f_WorldPosition = (u_World * vec4(a_Pos, 1.0)).xyz;\n\
    f_ScreenPosition = u_CameraMatrix * vec4(f_WorldPosition, 1.0);\n\
    gl_Position = f_ScreenPosition;\n\
}";

const char* SHADER_FRAG = "#version 460 core\n\
out vec4 FragColor;\n\
uniform vec4 u_Color;\n\
void main()\n\
{\n\
FragColor = u_Color;\n\
}";

const char* GRID_SHADER_FRAG = "#version 460 core\n\
in vec3 f_WorldPosition;\n\
const float TRESHOLD = 0.05;\n\
out vec4 FragColor;\n\
uniform vec4 u_Color;\n\
void main()\n\
{\n\
    vec3 absModPos = vec3(mod(abs(f_WorldPosition.x), 1.0), 0.0, mod(abs(f_WorldPosition.z), 1.0));\n\
    if (absModPos.x + TRESHOLD / 2 < TRESHOLD) {}\n\
    else if (absModPos.z + TRESHOLD / 2 < TRESHOLD) {}\n\
    else discard;\n\
    FragColor = vec4(length(absModPos) / (TRESHOLD * 2)); \
}";

const float CUBE_OFF = 1.0f;
const float PLANE_OFF = CUBE_OFF;

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


const std::vector<float> PLANE_VERTS = {
    -PLANE_OFF, 0, PLANE_OFF,
    PLANE_OFF, 0, PLANE_OFF,
    PLANE_OFF, 0, -PLANE_OFF,
    -PLANE_OFF, 0, -PLANE_OFF,
};
const std::vector<unsigned int> PLANE_INDICES = {
    3, 0, 1,
    3, 1, 2
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

    m_GridShader = renderer.CreateShaderFromSource("GizmosGridShader", SHADER_VERT, GRID_SHADER_FRAG);
    m_GridMaterial = renderer.CreateMaterial("GizmosGridMaterial");
    m_GridMaterial->SetShader(m_GridShader);

    m_Cube = renderer.CreateMesh("GizmosCube", CUBE_VERTS, CUBE_INDICES, { { 0, 3, Lumeda::MeshAttribType::FLOAT } });
    m_Plane = renderer.CreateMesh("GizmosPlane", PLANE_VERTS, PLANE_INDICES, { { 0, 3, Lumeda::MeshAttribType::FLOAT } });
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

void GizmosOpenGL::DrawGrid()
{
    LUMEDA_PROFILE;
    Transform dummy;
    dummy.SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    dummy.SetLocalRotationEulerAngles({ 0.0f, 0.0f, 0.0f });
    dummy.SetLocalScale({ 5.0f, 1.0f, 5.0f });

    sUniformsMap uniforms;
    uniforms.Set("u_Color", m_CurrentColor);
    uniforms.Set("u_World", dummy.GetWorld());
    Engine::Get().GetRenderer().Submit(m_Plane, m_GridMaterial, uniforms);
}

void GizmosOpenGL::SetColor(const glm::vec4& color)
{
    LUMEDA_PROFILE;
    m_CurrentColor = color;
}