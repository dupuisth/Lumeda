#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Graphics;
class EventManager;
class iImGuiLayer;

class iLowLevelEngineSetup
{
public:
  virtual std::unique_ptr<Graphics> GetGraphics() = 0;

  // Call theses last !!
  virtual std::unique_ptr<EventManager> GetEventManager() = 0;
  virtual std::unique_ptr<iImGuiLayer> GetImGuiLayer() = 0;
};
} // namespace Lumeda