#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/RenderPass.h>

namespace Lumeda
{
class ScreenPass : public iRenderPass
{
public:
  ScreenPass() {}
  ~ScreenPass() = default;

  void Submit(const sRenderItem& item) override;
  void Flush(RenderContext& renderContext, const UniformMap& globalUniforms) override;
  void Clear() override;

private:
  std::vector<sRenderCommand> m_RenderCommands;
};
} // namespace Lumeda