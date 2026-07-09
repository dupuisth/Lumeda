#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>

namespace Lumeda
{
class iEventReceiver
{
public:
  virtual ~iEventReceiver() = default;

  // Returns true if the event was handled.
  virtual bool OnEvent(iEvent& event) = 0;
};

} // namespace Lumeda