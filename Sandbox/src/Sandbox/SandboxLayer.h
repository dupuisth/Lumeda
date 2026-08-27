#pragma once

#include <Lumeda/Lumeda.h>

namespace Sandbox
{
class SandboxLayer : public Lumeda::iUpdateable, public Lumeda::iEventReceiver
{
public:
  SandboxLayer() : Lumeda::iUpdateable("SandboxLayer") {}
  ~SandboxLayer() = default;

  void OnStart() override;
  void Update() override;
  void OnDraw() override;

  void OnPostDraw() override;

  void HandleMessage(Lumeda::eUpdateableMessage message) override;

  bool OnEvent(Lumeda::iEvent& event);

private:
  std::unique_ptr<Lumeda::iVertexBuffer> m_GroundVertexBuffer;
  std::unique_ptr<Lumeda::iVertexBuffer> m_QuadBuffer;

  std::unique_ptr<Lumeda::SimpleRenderer> m_Renderer;

  std::unique_ptr<Lumeda::World> m_World;

  Lumeda::CameraEntity* m_CameraEntity;
};

} // namespace Sandbox
