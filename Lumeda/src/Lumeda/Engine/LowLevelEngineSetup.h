#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Graphics;
class EventManager;

class iLowLevelEngineSetup
{
public:
  virtual std::unique_ptr<Graphics> GetGraphics() = 0;

  // Call last !!!
  virtual std::unique_ptr<EventManager> GetEventManager() = 0;
};
} // namespace Lumeda