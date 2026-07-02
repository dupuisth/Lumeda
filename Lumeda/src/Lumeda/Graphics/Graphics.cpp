#include <Lumeda/Graphics/Graphics.h>

using namespace Lumeda;

#include <Lumeda/Graphics/LowLevelGraphics.h>

Graphics::Graphics(iLowLevelGraphics& lowLevelGraphics, EventQueue& eventQueue) :
    iUpdateable("Graphics"), m_LowLevelGraphics(lowLevelGraphics), m_EventQueue(eventQueue)
{
}

void Graphics::HandleMessage(eUpdateableMessage message)
{
  iUpdateable::HandleMessage(message);

  // Propagate
  m_LowLevelGraphics.HandleMessage(message);
}