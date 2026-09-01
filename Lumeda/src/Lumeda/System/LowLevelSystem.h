#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class iLowLevelSystem
{
public:
  tString ReadFileAsString(const twString& path);

  virtual float GetElapsedTime() = 0;
};
} // namespace Lumeda
