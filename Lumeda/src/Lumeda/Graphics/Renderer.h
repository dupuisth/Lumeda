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
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Graphics/UniformMap.h>

namespace Lumeda
{
struct RenderCommand
{
public:
  iVertexBuffer* vertexBuffer;
  Material* material;
  UniformMap additionalUniforms;
};

class iRenderCommandSink
{
public:
  virtual void Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms) = 0;
};

class World;

class iRenderer : public iUpdateable
{
public:
  iRenderer(const tString& name) : iUpdateable(name), m_TargetFramebuffer(nullptr) {}
  virtual ~iRenderer() = default;

  ///////////////////////////////////////////
  // Submits / Commands
  ///////////////////////////////////////////
  virtual void Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms) = 0;
  virtual void Submit(Model& model, UniformMap additionalUniforms) = 0;
  virtual void Submit(World& world) = 0;

  virtual void ClearCommands() { m_RenderCommands.clear(); }

  ///////////////////////////////////////////
  // Render
  ///////////////////////////////////////////
  virtual void Flush(UniformMap globalUniforms, bool clearCommands) = 0;

  ///////////////////////////////////////////
  // Config
  ///////////////////////////////////////////
  void SetFrameBuffer(iFrameBuffer* framebuffer) { m_TargetFramebuffer = framebuffer; }
  iFrameBuffer* GetFrameBuffer() { return m_TargetFramebuffer; }

  ///////////////////////////////////////////
  // Debugging
  ///////////////////////////////////////////
  const std::vector<RenderCommand>& GetRenderCommands() { return m_RenderCommands; }

protected:
  std::vector<RenderCommand> m_RenderCommands;

  iFrameBuffer* m_TargetFramebuffer;
};
} // namespace Lumeda