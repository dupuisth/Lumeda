#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{
class PlayerEntity : public Entity
{
public:
  PlayerEntity(const tString& name) : Entity(name) {}
  ~PlayerEntity() = default;
};
} // namespace Lumeda