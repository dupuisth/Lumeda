#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/LeafNode.h>

namespace Lumeda
{
class Entity : public LeafNode
{
public:
  Entity(const tString& name) : LeafNode(name) {}
  virtual ~Entity() = default;
};
} // namespace Lumeda