#include <Lumeda/Engine/EventQueue.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>

using namespace Lumeda;

LowLevelEngineSetupGL::LowLevelEngineSetupGL()
{
  m_EventQueue = std::make_unique<EventQueue>();

  m_lowLevelGraphics = std::make_unique<LowLevelGraphicsGL>(*m_EventQueue);
}

LowLevelEngineSetupGL::~LowLevelEngineSetupGL() = default;

std::unique_ptr<Graphics> LowLevelEngineSetupGL::GetGraphics()
{
  return std::make_unique<Graphics>(*m_lowLevelGraphics, *m_EventQueue);
}

std::unique_ptr<EventQueue> LowLevelEngineSetupGL::GetEventQueue()
{
  return std::move(m_EventQueue);
}