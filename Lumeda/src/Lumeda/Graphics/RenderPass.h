#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/RenderContext.h>
#include <Lumeda/Graphics/RendererTypes.h>

namespace Lumeda
{
class iRenderPass : public iRenderItemSink
{
public:
  virtual ~iRenderPass() = default;

  virtual void Submit(const sRenderItem& item) = 0;
  virtual void Flush(RenderContext& renderContext, const UniformMap& globalUniforms) = 0;
  virtual void Clear() = 0;
};
} // namespace Lumeda