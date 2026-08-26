#pragma once

#include <vector>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/RenderPass.h>
#include <Lumeda/Graphics/RendererTypes.h>

namespace Lumeda
{
class OpaquePass : public iRenderPass
{
public:
  OpaquePass(iFrameBuffer* frameBuffer) : m_frameBuffer(frameBuffer) {}
  ~OpaquePass() = default;

  void Submit(const sRenderItem& item);
  void Flush(RenderContext& renderContext, const UniformMap& globalUniforms);
  void Clear();

private:
  iFrameBuffer* m_frameBuffer;
  std::vector<sRenderCommand> m_renderCommands;
};
} // namespace Lumeda