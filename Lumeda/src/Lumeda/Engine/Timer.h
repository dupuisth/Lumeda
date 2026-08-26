#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Engine;

class Timer
{
  friend Engine;

public:
  Timer();
  ~Timer() = default;

  const size_t& GetFrameCount() { return m_Framecount; }

  const float& GetDeltaTime() { return m_DeltaTime; }

protected:
  void IncrementFramecount() { m_Framecount++; }
  void Tick();

private:
  size_t m_Framecount = 0;

  float m_DeltaTime = 0.0f;

  std::chrono::steady_clock::time_point m_PreviousTime;
};

} // namespace Lumeda