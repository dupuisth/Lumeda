#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>

namespace Lumeda
{
class LowLevelGraphicsGL;
class LowLevelSystemGL;
class ImGuiLayerGL;
class Graphics;
class EventManager;

class LowLevelEngineSetupGL : public iLowLevelEngineSetup
{
public:
  LowLevelEngineSetupGL();
  ~LowLevelEngineSetupGL();

  std::unique_ptr<Graphics> GetGraphics() override;

  // Call last !!!
  std::unique_ptr<EventManager> GetEventManager() override;
  std::unique_ptr<iImGuiLayer> GetImGuiLayer() override;

private:
  std::unique_ptr<LowLevelGraphicsGL> m_LowLevelGraphics;
  std::unique_ptr<LowLevelSystemGL> m_LowLevelSystem;

  std::unique_ptr<EventManager> m_EventManager;
  std::unique_ptr<ImGuiLayerGL> m_ImGuiLayer;
};
} // namespace Lumeda