#pragma once

#include <queue>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventReceiver.h>

namespace Lumeda
{

class EventManager
{
public:
  EventManager() : m_Events(), m_EventReceivers() {}
  ~EventManager() = default;

  ///////////////////////////////////////////
  // Events
  ///////////////////////////////////////////
  void PushEvent(std::unique_ptr<iEvent> event);
  std::unique_ptr<iEvent> PopEvent();
  bool IsEmpty() { return m_Events.empty(); }
  //---------------------------------------//

  ///////////////////////////////////////////
  // Event receivers
  ///////////////////////////////////////////
  void AddReceiver(iEventReceiver* eventReceiver);
  //---------------------------------------//

  ///////////////////////////////////////////
  // Dispatch
  ///////////////////////////////////////////
  void PollEvents();
  //---------------------------------------//
private:
  std::queue<std::unique_ptr<iEvent>> m_Events;
  std::vector<iEventReceiver*> m_EventReceivers;
};

} // namespace Lumeda