#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Transform.h>
#include <Lumeda/Implementation/OpenGL/GizmosOpenGL.h>
#include <Lumeda/Renderer/Renderer.h>

using namespace Lumeda;

const char* SHADER_VERT = R"(#version 460 core
layout (location = 0) in vec3 a_Pos;

uniform mat4 u_CameraView;
uniform mat4 u_CameraProjection;
uniform mat4 u_World;

out vec3 f_WorldPosition;
out vec3 f_ViewPosition;

void main()
{
    vec4 worldPos = u_World * vec4(a_Pos, 1.0);
    f_WorldPosition = worldPos.xyz;

    vec4 viewPos = u_CameraView * worldPos;
    f_ViewPosition = viewPos.xyz;

    gl_Position = u_CameraProjection * viewPos;
}
)";

const char* SHADER_FRAG = R"(#version 460 core
out vec4 FragColor;
uniform vec4 u_Color;

void main()
{
    FragColor = u_Color;
}
)";

const char* GRID_SHADER_FRAG = R"(#version 460 core
in vec3 f_WorldPosition;
in vec3 f_ViewPosition;
out vec4 FragColor;

uniform float u_Time;
uniform vec4  u_Color;        // base grid color (rgba)
uniform float u_CellSize;     // minor spacing in world units (e.g. 1.0)
uniform int   u_MajorEvery;   // major line every N minor cells (e.g. 10)
uniform float u_LineWidthPx;  // line width in pixels (e.g. 1.0..2.0)

uniform float u_FadeStart;    // view-depth start (e.g. 10.0)
uniform float u_FadeEnd;      // view-depth end   (e.g. 120.0)

// Anti-aliased grid line mask for repeating pattern at integer boundaries.
float gridAA(vec2 coord, float widthPx)
{
    vec2 f  = fract(coord);
    vec2 d  = min(f, 1.0 - f);      // 0 at line, 0.5 at cell center
    vec2 fw = fwidth(coord);
    vec2 w  = fw * widthPx;

    // AA line: 1 at the line, 0 away from it
    vec2 a = 1.0 - smoothstep(w, w * 2.0, d);
    return max(a.x, a.y);
}

void main()
{
    vec2 xz = f_WorldPosition.xz;

    // Minor + major
    float minor = gridAA(xz / u_CellSize, u_LineWidthPx);
    float major = gridAA(xz / (u_CellSize * float(u_MajorEvery)), u_LineWidthPx * 2.0);

    float line = max(minor * 0.55, major); // major dominates a bit

    // View-space depth fade (plane-friendly & stable)
    float depth = -f_ViewPosition.z; // camera looks down -Z in view space
    float fade = 1.0 - smoothstep(u_FadeStart, u_FadeEnd, depth);

    // Optional axis highlight (comment out if you don�t want it)
    float axisW = u_LineWidthPx * 2.5;
    float zAxis = 1.0 - smoothstep(0.0, fwidth(xz.x) * axisW, abs(xz.x)); // x=0 line
    float xAxis = 1.0 - smoothstep(0.0, fwidth(xz.y) * axisW, abs(xz.y)); // z=0 line

    vec3 col = u_Color.rgb;
    col = mix(col, vec3(1.0, 0.3, 0.3), clamp(zAxis, 0.0, 1.0)); // Z axis (x=0)
    col = mix(col, vec3(0.3, 0.6, 1.0), clamp(xAxis, 0.0, 1.0)); // X axis (z=0)

    float alpha = u_Color.a * line * fade;

    // Optional discard
    // if (alpha < 0.002) discard;

    FragColor = vec4(col, pow(alpha, 2));
}
)";

const float CUBE_OFF = 1.0f;
const float PLANE_OFF = CUBE_OFF;

const std::vector<float> CUBE_VERTS = {
    -CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    -CUBE_OFF,
    -CUBE_OFF,
    CUBE_OFF,
    -CUBE_OFF,

    -CUBE_OFF,
    -CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    -CUBE_OFF,
    CUBE_OFF,
    CUBE_OFF,
    -CUBE_OFF,
    -CUBE_OFF,
    -CUBE_OFF,
    -CUBE_OFF,
    -CUBE_OFF,
};

const std::vector<unsigned int> CUBE_INDICES = {
    // Top Side
    2,
    0,
    1,
    2,
    3,
    0,

    // Bottom side
    4,
    7,
    6,
    4,
    6,
    5,

    // Front Side
    3,
    6,
    7,
    3,
    2,
    6,

    // Right Side
    2,
    1,
    5,
    2,
    5,
    6,

    // Back Side
    0,
    5,
    1,
    0,
    4,
    5,

    // Left Side
    4,
    0,
    3,
    4,
    3,
    7};

const std::vector<float> PLANE_VERTS = {
    -PLANE_OFF,
    0,
    PLANE_OFF,
    PLANE_OFF,
    0,
    PLANE_OFF,
    PLANE_OFF,
    0,
    -PLANE_OFF,
    -PLANE_OFF,
    0,
    -PLANE_OFF,
};
const std::vector<unsigned int> PLANE_INDICES = {3, 0, 1, 3, 1, 2};

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

    Renderer& renderer = LUMEDA_RENDERER;
    m_Shader = renderer.CreateShaderFromSource("GizmosShader", SHADER_VERT, SHADER_FRAG);
    m_Material = renderer.CreateMaterial("GizmosMaterial");
    m_Material->SetShader(m_Shader);

    m_GridShader = renderer.CreateShaderFromSource("GizmosGridShader", SHADER_VERT, GRID_SHADER_FRAG);
    m_GridMaterial = renderer.CreateMaterial("GizmosGridMaterial");
    m_GridMaterial->SetTransparent(true);
    m_GridMaterial->SetShader(m_GridShader);

    m_Cube = renderer.CreateMesh("GizmosCube", CUBE_VERTS, CUBE_INDICES, {{0, 3, Lumeda::MeshAttribType::FLOAT}});
    m_Plane = renderer.CreateMesh("GizmosPlane", PLANE_VERTS, PLANE_INDICES, {{0, 3, Lumeda::MeshAttribType::FLOAT}});
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
    LUMEDA_RENDERER.Submit(m_Cube, m_Material, uniforms);
}

void GizmosOpenGL::DrawGrid()
{
    LUMEDA_PROFILE;
    Transform dummy;
    dummy.SetLocalPosition({0.0f, 0.0f, 0.0f});
    dummy.SetLocalRotationEulerAngles({0.0f, 0.0f, 0.0f});
    dummy.SetLocalScale({500.0f, 1.0f, 500.0f});

    sUniformsMap uniforms;
    uniforms.Set("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    uniforms.Set("u_World", dummy.GetWorld());
    uniforms.Set("u_CellSize", 1.0f);
    uniforms.Set("u_MajorEvery", 10);
    uniforms.Set("u_LineWidthPx", 1.0f);
    uniforms.Set("u_FadeStart", 25.0f);
    uniforms.Set("u_FadeEnd", 50.0f);

    LUMEDA_RENDERER.Submit(m_Plane, m_GridMaterial, uniforms);
}

void GizmosOpenGL::SetColor(const glm::vec4& color)
{
    LUMEDA_PROFILE;
    m_CurrentColor = color;
}