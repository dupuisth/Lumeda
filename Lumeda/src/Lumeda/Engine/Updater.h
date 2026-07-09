#pragma once

#include <vector>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class Updater
{
public:
  Updater() : m_Updateables() {}
  ~Updater() = default;

  void AddUpdateable(iUpdateable* updateable);

  void BroadcastMessage(eUpdateableMessage message);

private:
  std::vector<iUpdateable*> m_Updateables;
};

} // namespace Lumeda