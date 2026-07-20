#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class Entity;
class Node;
class LeafNode;

class World : public iUpdateable
{
public:
  World();
  virtual ~World() = default;

  Node& GetRootNode() { return *m_RootNode; }

  void HandleMessage(eUpdateableMessage message);

private:
  std::unique_ptr<Node> m_RootNode;
};
} // namespace Lumeda