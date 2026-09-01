#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>
#include <Lumeda/Implementation/GL/ImGuiLayerGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>

namespace Lumeda
{
class LowLevelGraphicsGL;
class LowLevelSystemGL;
class ImGuiLayerGL;
class Graphics;
class EventManager;
class InputsGL;
class Timer;

class LowLevelEngineSetupGL : public iLowLevelEngineSetup
{
public:
  LowLevelEngineSetupGL();
  ~LowLevelEngineSetupGL();

  void Prepare(sLowLevelEngineSetupPrepare prepareData);

  std::unique_ptr<Graphics> GetGraphics() override;
  std::unique_ptr<iInputs> GetInputs() override;
  std::unique_ptr<iImGuiLayer> GetImGuiLayer() override;
  std::unique_ptr<Timer> GetTimer() override;

private:
  std::unique_ptr<LowLevelGraphicsGL> m_LowLevelGraphics = nullptr;
  std::unique_ptr<LowLevelSystemGL> m_LowLevelSystem = nullptr;
  std::unique_ptr<ImGuiLayerGL> m_ImGuiLayer = nullptr;
  std::unique_ptr<Timer> m_Timer = nullptr;

  sLowLevelEngineSetupPrepare m_PrepareData;
};
} // namespace Lumeda