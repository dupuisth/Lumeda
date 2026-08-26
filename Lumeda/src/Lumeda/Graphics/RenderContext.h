#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/RendererTypes.h>

namespace Lumeda
{
/// @brief Share context used inside a renderer for its passes.
class RenderContext
{
public:
  RenderContext(iLowLevelGraphics& lowLevelGraphics) : m_LowLevelGraphics(lowLevelGraphics) {}
  ~RenderContext() = default;

  void BeginPass(iFrameBuffer* target, tClearFrameBufferFlag clearFlags);
  void Draw(sRenderCommand& command, const UniformMap& globalUniforms);
  void EndPass(iFrameBuffer* target);

  iLowLevelGraphics& GetLowLevelGraphics() { return m_LowLevelGraphics; }

private:
  iLowLevelGraphics& m_LowLevelGraphics;

  ePolygonFace m_Face = ePolygonFace_Front;
  ePolygonMode m_Mode = ePolygonMode_Fill;
};
} // namespace Lumeda