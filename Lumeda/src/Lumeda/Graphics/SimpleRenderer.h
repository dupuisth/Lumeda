#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/OpaquePass.h>
#include <Lumeda/Graphics/RenderBuffer.h>
#include <Lumeda/Graphics/RenderPass.h>
#include <Lumeda/Graphics/Renderer.h>
#include <Lumeda/Graphics/ScreenPass.h>
#include <Lumeda/Graphics/Texture.h>

namespace Lumeda
{
class SimpleRenderer : public iRenderer
{
public:
  SimpleRenderer(iLowLevelGraphics& lowLevelGraphics);
  virtual ~SimpleRenderer() = default;

  ///////////////////////////////////////////
  // Submits
  ///////////////////////////////////////////
  void Submit(const sRenderItem& item) override;
  void Submit(World& world) override;

  ///////////////////////////////////////////
  // Render
  ///////////////////////////////////////////
  void Flush(const UniformMap& globalUniforms) override;

  ///////////////////////////////////////////
  // FrameBuffer
  ///////////////////////////////////////////
  iFrameBuffer& GetFrameBuffer() { return *m_FrameBuffer; }
  iTexture& GetFrameBufferDepthStencil() { return *m_FrameBufferDepthStencil; }
  iTexture& GetFrameBufferColor() { return *m_FrameBufferColor; }

protected:
  iLowLevelGraphics& m_LowLevelGraphics;

  std::unique_ptr<iTexture> m_FrameBufferColor;
  std::unique_ptr<iTexture> m_FrameBufferDepthStencil;
  std::unique_ptr<iFrameBuffer> m_FrameBuffer;

  std::unique_ptr<RenderContext> m_RenderContext;
  std::unique_ptr<OpaquePass> m_OpaquePass;
  std::unique_ptr<ScreenPass> m_ScreenPass;
};
} // namespace Lumeda