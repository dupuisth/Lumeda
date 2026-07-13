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
  void OnDraw() override;

  void OnPostDraw() override;

  bool OnEvent(Lumeda::iEvent& event);

private:
  std::unique_ptr<Lumeda::iVertexBuffer> m_VertexBuffer;
  std::unique_ptr<Lumeda::iVertexBuffer> m_QuadBuffer;

  std::unique_ptr<Lumeda::iFrameBuffer> m_FrameBuffer;
  std::unique_ptr<Lumeda::iTexture> m_FrameBufferColor;
  std::unique_ptr<Lumeda::iRenderBuffer> m_FrameBufferDepthStencil;

  std::unique_ptr<Lumeda::Material> m_BasicMaterial;
  std::unique_ptr<Lumeda::Material> m_ScreenMaterial;

  std::unique_ptr<Lumeda::SimpleRenderer> m_WorldRenderer;
  std::unique_ptr<Lumeda::SimpleRenderer> m_ScreenRenderer;

  std::unique_ptr<Lumeda::World> m_World;

  Lumeda::CameraEntity* m_CameraEntity;
};

} // namespace Sandbox
