#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/UniformMap.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{

class iRenderCommandSink;

class iRenderable : public Entity
{
public:
  iRenderable(const tString& name) : Entity(name) {}
  virtual ~iRenderable() = default;

  virtual void CollectRenderCommands(iRenderCommandSink& sink) = 0;

  virtual UniformMap GetAdditionalUniforms();
};

} // namespace Lumeda
