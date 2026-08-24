#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Graphics/VertexBuffer.h>

namespace Lumeda
{
struct sRenderCommand
{
public:
  iVertexBuffer* vertexBuffer;
  Material* material;
  UniformMap additionalUniforms;
};

class iRenderCommandSink
{
public:
  virtual void Submit(const sRenderCommand& renderCommand) = 0;
};
} // namespace Lumeda
