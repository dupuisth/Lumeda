#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventQueue.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class iTexture;
class iLowLevelGraphics;

class Graphics : public iUpdateable
{
public:
  Graphics(iLowLevelGraphics& lowLevelGraphics, EventQueue& eventQueue);

  iLowLevelGraphics& GetLowLevelGraphics() { return m_LowLevelGraphics; }

  void HandleMessage(eUpdateableMessage message) override;

private:
  iLowLevelGraphics& m_LowLevelGraphics;
  EventQueue& m_EventQueue;
};
} // namespace Lumeda