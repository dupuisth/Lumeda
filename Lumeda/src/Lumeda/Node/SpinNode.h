#pragma once
#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>
#include <Lumeda/Renderer/Model.h>

namespace Lumeda
{
class SpinNode : public Node
{
  public:
    SpinNode(glm::vec3 rotationDelta, float rotationMultiplier);
    virtual ~SpinNode();

    void OnUpdate() override;
    void OnRenderImGui() override;

  public:
    glm::vec3 m_RotationDelta;
    float m_RotationMultiplier;
};
} // namespace Lumeda