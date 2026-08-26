#include <Lumeda/Graphics/OpaquePass.h>

using namespace Lumeda;

void OpaquePass::Submit(const sRenderItem& item)
{
  if (item.featureFlags & eRenderItemFeatureFlag_ScreenSpace)
  {
    // We don't want to draw something that is reserved for screen space.
    return;
  }

  ePolygonFace face = ePolygonFace_Front;
  ePolygonMode mode = ePolygonMode_Fill;
  if (item.wireframe)
  {
    face = ePolygonFace_FrontBack;
    mode = ePolygonMode_Line;
  }

  m_renderCommands.push_back(
      {.vertexBuffer = item.vertexBuffer, .material = item.material, .additionalUniforms = item.additionalUniforms, .face = face, .mode = mode});
}

void OpaquePass::Flush(RenderContext& renderContext, const UniformMap& globalUniforms)
{
  renderContext.BeginPass(m_frameBuffer, tClearFrameBufferFlag_Color | tClearFrameBufferFlag_Depth);
  renderContext.GetLowLevelGraphics().EnableDepthTest(true);

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