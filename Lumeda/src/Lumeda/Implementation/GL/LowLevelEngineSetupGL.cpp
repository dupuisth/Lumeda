#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Implementation/GL/ImGuiLayerGL.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>

using namespace Lumeda;

LowLevelEngineSetupGL::LowLevelEngineSetupGL()
{
  m_EventManager = std::make_unique<EventManager>();

  m_LowLevelSystem = std::make_unique<LowLevelSystemGL>();
  m_LowLevelGraphics = std::make_unique<LowLevelGraphicsGL>(*m_EventManager, *m_LowLevelSystem);
  m_ImGuiLayer = std::make_unique<ImGuiLayerGL>(*m_EventManager, *m_LowLevelGraphics);
}

LowLevelEngineSetupGL::~LowLevelEngineSetupGL() = default;

std::unique_ptr<Graphics> LowLevelEngineSetupGL::GetGraphics()
{
  return std::make_unique<Graphics>(*m_LowLevelGraphics, *m_EventManager);
}

std::unique_ptr<EventManager> LowLevelEngineSetupGL::GetEventManager()
{
  return std::move(m_EventManager);
}

std::unique_ptr<iImGuiLayer> LowLevelEngineSetupGL::GetImGuiLayer()
{
  return std::move(m_ImGuiLayer);
}