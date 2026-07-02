#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

class iTexture;
class iLowLevelGraphics;

class Graphics
{
  public:
    Graphics(iLowLevelGraphics& lowLevelGraphics);

    iLowLevelGraphics& GetLowLevelGraphics() { return m_LowLevelGraphics; }

  private:
    iLowLevelGraphics& m_LowLevelGraphics;
};
} // namespace Lumeda