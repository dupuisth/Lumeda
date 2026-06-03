#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>
#include <Lumeda/Renderer/Light.h>

namespace Lumeda
{
class LightNode : public Node
{
  public:
    LightNode();
    virtual ~LightNode();

    sLight& GetLight();

  protected:
    void OnRender() override;
    void OnRenderImGui() override;

    void OnEnable() override;
    void OnDisable() override;

  private:
    sLight m_Light;
};
} // namespace Lumeda