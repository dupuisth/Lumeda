#include <Lumeda/Graphics/ScreenPass.h>

using namespace Lumeda;

void ScreenPass::Submit(const sRenderItem& item)
{
  if (item.featureFlags & eRenderItemFeatureFlag_ScreenSpace)
  {
    // Only accept screen space items.
    m_RenderCommands.push_back({.vertexBuffer = item.vertexBuffer, .material = item.material, .additionalUniforms = item.additionalUniforms});
  }
}

void ScreenPass::Flush(RenderContext& renderContext, const UniformMap& globalUniforms)
{
  renderContext.BeginPass(nullptr, tClearFrameBufferFlag_Color);

  for (sRenderCommand& command : m_RenderCommands)
  {
    renderContext.Draw(command, globalUniforms);
  }
  Clear();

  renderContext.EndPass(nullptr);
}

void ScreenPass::Clear()
{
  m_RenderCommands.clear();
}