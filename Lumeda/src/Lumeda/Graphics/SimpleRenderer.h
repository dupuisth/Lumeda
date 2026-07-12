#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Renderer.h>

namespace Lumeda
{
class SimpleRenderer : public iRenderer
{
public:
  SimpleRenderer(iLowLevelGraphics& lowLevelGraphics) : iRenderer("SimpleRenderer"), m_LowLevelGraphics(lowLevelGraphics) {}
  ~SimpleRenderer() = default;

  ///////////////////////////////////////////
  // Submits
  ///////////////////////////////////////////
  void Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms) override;
  void Submit(World& world) override;

  ///////////////////////////////////////////
  // Render
  ///////////////////////////////////////////
  void Flush(UniformMap globalUniforms, bool clearCommands) override;

private:
  iLowLevelGraphics& m_LowLevelGraphics;
};
} // namespace Lumeda