#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class iLowLevelSystem
{
public:
  tString ReadFileAsString(const twString& path);
};
} // namespace Lumeda
