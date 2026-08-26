#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Graphics/FrameBuffer.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/Model.h>
#include <Lumeda/Graphics/RenderBuffer.h>
#include <Lumeda/Graphics/RendererTypes.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Graphics/UniformMap.h>

namespace Lumeda
{

class World;

class iRenderer : public iUpdateable, public iRenderItemSink
{
public:
  iRenderer(const tString& name) : iUpdateable(name) {}
  virtual ~iRenderer() = default;

  ///////////////////////////////////////////
  // Submits / Commands
  ///////////////////////////////////////////
  virtual void Submit(const sRenderItem& item) = 0;
  virtual void Submit(World& world) = 0;

  ///////////////////////////////////////////
  // Render
  ///////////////////////////////////////////
  virtual void Flush(const UniformMap& globalUniforms) = 0;

protected:
  std::vector<sRenderCommand> m_RenderCommands;
};
} // namespace Lumeda