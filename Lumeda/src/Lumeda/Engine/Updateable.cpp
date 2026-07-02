#include <Lumeda/Engine/Updater.h>

using namespace Lumeda;

void Updater::AddUpdateable(iUpdateable* updateable)
{
  m_Updateables.push_back(updateable);
}

void Updater::BroadcastMessage(eUpdateableMessage message)
{
  for (const auto& updateable : m_Updateables)
  {
    updateable->HandleMessage(message);
  }
}