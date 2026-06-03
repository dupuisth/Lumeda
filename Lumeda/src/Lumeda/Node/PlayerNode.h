#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>

namespace Lumeda
{
class PlayerNode : public Node
{
  public:
    PlayerNode();
    virtual ~PlayerNode();

  protected:
    void OnUpdate() override;
    void OnRender() override;
    void OnRenderImGui() override;
};
} // namespace Lumeda