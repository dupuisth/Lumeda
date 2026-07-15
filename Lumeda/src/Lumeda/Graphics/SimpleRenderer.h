#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Renderer.h>

namespace Lumeda
{
class SimpleRenderer : public iRenderer, public iRenderCommandSink
{
public:
  SimpleRenderer(iLowLevelGraphics& lowLevelGraphics) : iRenderer("SimpleRenderer"), m_LowLevelGraphics(lowLevelGraphics) {}
  SimpleRenderer(const tString& name, iLowLevelGraphics& lowLevelGraphics) : iRenderer(name), m_LowLevelGraphics(lowLevelGraphics) {}

  virtual ~SimpleRenderer() = default;

  ///////////////////////////////////////////
  // Submits
  ///////////////////////////////////////////
  void Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms) override;
  void Submit(Model& model, UniformMap additionalUniforms) override;
  void Submit(World& world) override;

  ///////////////////////////////////////////
  // Render
  ///////////////////////////////////////////
  void Flush(UniformMap globalUniforms, bool clearCommands, tClearFrameBufferFlag clearFlag) override;

  ///////////////////////////////////////////
  // Additional
  ///////////////////////////////////////////
  void SetMode(ePolygonFace face, ePolygonMode mode)
  {
    m_Face = face;
    m_Mode = mode;
  }

protected:
  iLowLevelGraphics& m_LowLevelGraphics;

  ePolygonFace m_Face = ePolygonFace_Front;
  ePolygonMode m_Mode = ePolygonMode_Fill;
};
} // namespace Lumeda