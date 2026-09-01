#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/System/LowLevelSystem.h>

namespace Lumeda
{
class LowLevelSystemGL : public iLowLevelSystem
{
public:
  LowLevelSystemGL() = default;
  ~LowLevelSystemGL() = default;

  float GetElapsedTime();
};

} // namespace Lumeda