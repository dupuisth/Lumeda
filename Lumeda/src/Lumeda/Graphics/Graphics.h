#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class iTexture;
class iLowLevelGraphics;

class Graphics : public iUpdateable, public iEventReceiver
{
public:
  Graphics(iLowLevelGraphics& lowLevelGraphics, EventManager& eventManager);

  iLowLevelGraphics& GetLowLevelGraphics() { return m_LowLevelGraphics; }

  void HandleMessage(eUpdateableMessage message) override;
  bool OnEvent(iEvent& event) override;

private:
  iLowLevelGraphics& m_LowLevelGraphics;
  EventManager& m_EventManager;
};
} // namespace Lumeda