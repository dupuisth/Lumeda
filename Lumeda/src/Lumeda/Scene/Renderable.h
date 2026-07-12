#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Graphics/VertexBuffer.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{

class iRenderable : public Entity
{
public:
  iRenderable(const tString& name) : Entity(name) {}
  virtual ~iRenderable() = default;

  virtual iVertexBuffer* GetVertexBuffer() = 0;
  virtual Material* GetMaterial() = 0;
  virtual UniformMap GetAdditionalUniforms();
};

} // namespace Lumeda