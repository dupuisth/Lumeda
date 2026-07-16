#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Implementation/GL/ImGuiLayerGL.h>
#include <Lumeda/Implementation/GL/InputsGL.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>

using namespace Lumeda;

LowLevelEngineSetupGL::LowLevelEngineSetupGL() = default;
LowLevelEngineSetupGL::~LowLevelEngineSetupGL() = default;

void LowLevelEngineSetupGL::Prepare(sLowLevelEngineSetupPrepare prepareData)
{
  m_PrepareData = prepareData;

  m_LowLevelSystem = std::make_unique<LowLevelSystemGL>();
  m_LowLevelGraphics = std::make_unique<LowLevelGraphicsGL>(*m_PrepareData.eventManager, *m_LowLevelSystem);
  m_ImGuiLayer = std::make_unique<ImGuiLayerGL>(*m_PrepareData.eventManager, *m_LowLevelGraphics);
}

std::unique_ptr<Graphics> LowLevelEngineSetupGL::GetGraphics()
{
  return std::make_unique<Graphics>(*m_LowLevelGraphics, *m_PrepareData.eventManager);
}

std::unique_ptr<iInputs> Lumeda::LowLevelEngineSetupGL::GetInputs()
{
  return std::make_unique<InputsGL>(*m_LowLevelGraphics, *m_PrepareData.timer);
}

std::unique_ptr<iImGuiLayer> LowLevelEngineSetupGL::GetImGuiLayer()
{
  return std::move(m_ImGuiLayer);
}