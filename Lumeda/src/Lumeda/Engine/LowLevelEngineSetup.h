#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Graphics;

class iLowLevelEngineSetup
{
  public:
    virtual std::unique_ptr<Graphics> GetGraphics() = 0;
};
} // namespace Lumeda