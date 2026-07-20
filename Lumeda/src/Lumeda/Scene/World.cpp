#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/World.h>

using namespace Lumeda;

World::World() : iUpdateable("World")
{
  m_RootNode = std::make_unique<Node>("RootNode");
  m_RootNode->SetWorld(this);
}

void World::HandleMessage(eUpdateableMessage message)
{
  iUpdateable::HandleMessage(message);

  if (m_RootNode != nullptr)
  {
    m_RootNode->HandleMessage(message);
  }
}