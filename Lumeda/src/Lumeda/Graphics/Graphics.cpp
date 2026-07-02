#include <Lumeda/Graphics/Graphics.h>

using namespace Lumeda;

#include <Lumeda/Graphics/LowLevelGraphics.h>

Graphics::Graphics(iLowLevelGraphics& lowLevelGraphics, EventManager& eventManager) :
    iUpdateable("Graphics"), m_LowLevelGraphics(lowLevelGraphics), m_EventManager(eventManager)
{
}

void Graphics::HandleMessage(eUpdateableMessage message)
{
  iUpdateable::HandleMessage(message);

  // Propagate
  m_LowLevelGraphics.HandleMessage(message);
}