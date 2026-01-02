#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

namespace Lumeda
{
    class Gizmos
    {
    public:
        virtual ~Gizmos() = default;

        virtual void Initialize() = 0;
        virtual void Terminate() = 0;

        virtual void DrawCube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) = 0;
        virtual void DrawGrid() = 0;

        virtual void SetColor(const glm::vec4& color) = 0;

        static std::unique_ptr<Gizmos> Create();
    };
}