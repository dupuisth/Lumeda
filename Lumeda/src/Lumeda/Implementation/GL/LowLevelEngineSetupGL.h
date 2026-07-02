#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>

namespace Lumeda
{
class LowLevelGraphicsGL;
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

private:
  std::unique_ptr<LowLevelGraphicsGL> m_lowLevelGraphics;

  std::unique_ptr<EventManager> m_EventManager;
};
} // namespace Lumeda