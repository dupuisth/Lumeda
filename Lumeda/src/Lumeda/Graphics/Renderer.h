#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/FrameBuffer.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/Material.h>
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

class Renderer
{

public:
  Renderer();
  ~Renderer();

  void Submit(iVertexBuffer* vertexBuffer, Material* material, UniformMap additionalUniforms);

private:
  std::vector<RenderCommand> m_RenderCommands;
};
} // namespace Lumeda