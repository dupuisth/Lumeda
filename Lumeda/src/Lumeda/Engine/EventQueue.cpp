#include <Lumeda/Engine/EventQueue.h>

using namespace Lumeda;

void EventQueue::PushEvent(std::unique_ptr<iEvent> event)
{
  m_Events.push(std::move(event));
}

std::unique_ptr<iEvent> EventQueue::PopEvent()
{
  LUMEDA_ASSERT(!IsEmpty());

  std::unique_ptr<iEvent> event = std::move(m_Events.front());
  m_Events.pop();

  return std::move(event);
}