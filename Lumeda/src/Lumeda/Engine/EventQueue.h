#pragma once

#include <queue>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>

namespace Lumeda
{

class EventQueue
{
public:
  EventQueue() {}
  ~EventQueue() = default;

  void PushEvent(std::unique_ptr<iEvent> event);
  std::unique_ptr<iEvent> PopEvent();

  bool IsEmpty() { return m_Events.empty(); }

private:
  std::queue<std::unique_ptr<iEvent>> m_Events;
};

} // namespace Lumeda