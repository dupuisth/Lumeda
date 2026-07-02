#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Graphics;
class EventQueue;

class iLowLevelEngineSetup
{
public:
  virtual std::unique_ptr<Graphics> GetGraphics() = 0;

  // Call last !!!
  virtual std::unique_ptr<EventQueue> GetEventQueue() = 0;
};
} // namespace Lumeda