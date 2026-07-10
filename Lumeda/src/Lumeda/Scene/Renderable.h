#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{

class Renderable : public Entity
{
public:
  Renderable(const tString& name) : Entity(name) {}
  virtual ~Renderable() = default;
};

} // namespace Lumeda