#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Gizmos/Gizmos.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Mesh.h>
#include <Lumeda/Renderer/Material.h>

#include <memory>
#include <unordered_map>

namespace Lumeda
{
    class GizmosOpenGL : public Gizmos
    {
    public:
        GizmosOpenGL();
        virtual ~GizmosOpenGL();

        void Initialize() override;
        void Terminate() override;

        void DrawCube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) override;

        void SetColor(const glm::vec4& color) override;

    private:
        std::shared_ptr<Mesh> m_Cube;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Material> m_Material;

        glm::vec4 m_CurrentColor;
    };
}