#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/World.h>

using namespace Lumeda;

World::World()
{
  m_RootNode = std::make_unique<Node>("RootNode");
}