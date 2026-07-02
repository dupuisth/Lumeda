#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>

using namespace Lumeda;

LowLevelEngineSetupGL::LowLevelEngineSetupGL()
{
  m_EventManager = std::make_unique<EventManager>();

  m_lowLevelGraphics = std::make_unique<LowLevelGraphicsGL>(*m_EventManager);
}

LowLevelEngineSetupGL::~LowLevelEngineSetupGL() = default;

std::unique_ptr<Graphics> LowLevelEngineSetupGL::GetGraphics()
{
  return std::make_unique<Graphics>(*m_lowLevelGraphics, *m_EventManager);
}

std::unique_ptr<EventManager> LowLevelEngineSetupGL::GetEventManager()
{
  return std::move(m_EventManager);
}