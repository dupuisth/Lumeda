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

  const float& GetDeltaTime() { return m_DeltaTime; }

protected:
  void IncrementFramecount() { m_Framecount++; }

private:
  size_t m_Framecount = 0;

  float m_LastFrameTime;
  float m_DeltaTime = 1.0f / 180.0f;
};

} // namespace Lumeda