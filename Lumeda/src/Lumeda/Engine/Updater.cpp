#include <Lumeda/Engine/Updater.h>

using namespace Lumeda;

void Updater::AddUpdateable(iUpdateable* updateable)
{
  m_Updateables.push_back(updateable);
}

void Lumeda::Updater::AddUpdateableOverlay(iUpdateable* updateable)
{
  m_UpdateablesOverlay.push_back(updateable);
}

#define Broadcast(list)                                                                                                                              \
  for (const auto& u : list)                                                                                                                         \
  u->HandleMessage(message)

void Updater::BroadcastMessage(eUpdateableMessage message)
{
  // For Pre-stuff, call the overlay first
  if (message == eUpdateableMessage_OnPreDraw || message == eUpdateableMessage_PreUpdate)
  {
    Broadcast(m_UpdateablesOverlay);
    Broadcast(m_Updateables);
  }
  else
  {
    Broadcast(m_Updateables);
    Broadcast(m_UpdateablesOverlay);
  }
}
