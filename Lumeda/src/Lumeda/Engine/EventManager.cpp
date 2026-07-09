#include <Lumeda/Engine/EventManager.h>

using namespace Lumeda;

///////////////////////////////////////////
// Events
///////////////////////////////////////////
void EventManager::PushEvent(std::unique_ptr<iEvent> event)
{
  m_Events.push(std::move(event));
}

std::unique_ptr<iEvent> EventManager::PopEvent()
{
  LUMEDA_ASSERT(!IsEmpty());

  std::unique_ptr<iEvent> event = std::move(m_Events.front());
  m_Events.pop();

  return std::move(event);
}

///////////////////////////////////////////
// Event receivers
///////////////////////////////////////////
void EventManager::AddReceiver(iEventReceiver* eventReceiver)
{
  m_EventReceivers.push_back(eventReceiver);
}
//---------------------------------------//

///////////////////////////////////////////
// Dispatch
///////////////////////////////////////////
void EventManager::PollEvents()
{
  while (!IsEmpty())
  {
    std::unique_ptr<iEvent> event = PopEvent();
    LUMEDA_CORE_TRACE("Handling event: {0} {1}", event->GetType(), event->ToString());
    for (const auto& handler : m_EventReceivers)
    {
      if (handler->OnEvent(*event))
      {
        event->Handled = true;
        break;
      }
    }
  }
}

//---------------------------------------//