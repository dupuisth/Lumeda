#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

class Entity;
class Node;
class LeafNode;

class World
{
public:
  World();
  virtual ~World() = default;

  Node& GetRootNode() { return *m_RootNode; }

private:
  std::unique_ptr<Node> m_RootNode;
};
} // namespace Lumeda