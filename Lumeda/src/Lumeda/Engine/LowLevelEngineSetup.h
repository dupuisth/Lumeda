#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Graphics;
class EventManager;
class iImGuiLayer;
class iInputs;
class Timer;

// In case of evolution, don't change everything
struct sLowLevelEngineSetupPrepare
{
  EventManager* eventManager = nullptr;
  Timer* timer = nullptr;
};

class iLowLevelEngineSetup
{
public:
  virtual void Prepare(sLowLevelEngineSetupPrepare prepareData) = 0;

  virtual std::unique_ptr<Graphics> GetGraphics() = 0;
  virtual std::unique_ptr<iInputs> GetInputs() = 0;
  virtual std::unique_ptr<iImGuiLayer> GetImGuiLayer() = 0;
};
} // namespace Lumeda