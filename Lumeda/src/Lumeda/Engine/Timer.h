#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Engine;

class Timer
{
  friend Engine;

public:
  Timer() {}
  ~Timer() = default;

  const size_t& GetFrameCount() { return m_Framecount; }

protected:
  void IncrementFramecount() { m_Framecount++; }

private:
  size_t m_Framecount = 0;
};

} // namespace Lumeda