#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>

namespace Lumeda
{
class LowLevelGraphicsGL;
class Graphics;

class LowLevelEngineSetupGL : public iLowLevelEngineSetup
{
  public:
    LowLevelEngineSetupGL();
    ~LowLevelEngineSetupGL();

    std::unique_ptr<Graphics> GetGraphics() override;

  private:
    std::unique_ptr<LowLevelGraphicsGL> m_lowLevelGraphics;
};
} // namespace Lumeda