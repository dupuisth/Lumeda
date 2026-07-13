#pragma once

#include <vector>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class Updater
{
public:
  Updater() : m_Updateables(), m_UpdateablesOverlay() {}
  ~Updater() = default;

  void AddUpdateable(iUpdateable* updateable);
  void AddUpdateableOverlay(iUpdateable* updateable);

  void BroadcastMessage(eUpdateableMessage message);

private:
  std::vector<iUpdateable*> m_Updateables;
  std::vector<iUpdateable*> m_UpdateablesOverlay;
};

} // namespace Lumeda