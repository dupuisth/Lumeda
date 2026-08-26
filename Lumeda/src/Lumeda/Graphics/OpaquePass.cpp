#include <Lumeda/Graphics/OpaquePass.h>

using namespace Lumeda;

void OpaquePass::Submit(const sRenderItem& item)
{
  if (item.featureFlags & eRenderItemFeatureFlag_ScreenSpace)
  {
    // We don't want to draw something that is reserved for screen space.
    return;
  }

  m_renderCommands.push_back({.vertexBuffer = item.vertexBuffer, .material = item.material, .additionalUniforms = item.additionalUniforms});
}

void OpaquePass::Flush(RenderContext& renderContext, const UniformMap& globalUniforms)
{
  renderContext.BeginPass(m_frameBuffer, tClearFrameBufferFlag_Color | tClearFrameBufferFlag_Depth);

  for (sRenderCommand& renderCommand : m_renderCommands)
  {
    renderContext.Draw(renderCommand, globalUniforms);
  }

  renderContext.EndPass(m_frameBuffer);
}

void OpaquePass::Clear()
{
  m_renderCommands.clear();
}