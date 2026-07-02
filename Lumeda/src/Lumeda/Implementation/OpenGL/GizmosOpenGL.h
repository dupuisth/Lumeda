// #pragma once

// #include <Lumeda/Core/Base.h>
// #include <Lumeda/Gizmos/Gizmos.h>
// #include <Lumeda/Renderer/Material.h>
// #include <Lumeda/Renderer/Mesh.h>
// #include <Lumeda/Renderer/Shader.h>
// #include <memory>
// #include <unordered_map>

// namespace Lumeda
// {
// class GizmosOpenGL : public Gizmos
// {
//   public:
//     GizmosOpenGL();
//     virtual ~GizmosOpenGL();

//     void Initialize() override;
//     void Terminate() override;

//     void DrawCube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) override;
//     void DrawGrid() override;

//     void SetColor(const glm::vec4& color) override;

//   private:
//     Mesh* m_Cube;
//     Mesh* m_Plane;

//     Shader* m_Shader;
//     Material* m_Material;

//     Shader* m_GridShader;
//     Material* m_GridMaterial;

//     glm::vec4 m_CurrentColor;
// };
// } // namespace Lumeda