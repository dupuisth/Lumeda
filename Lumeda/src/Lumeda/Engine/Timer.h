#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/System/LowLevelSystem.h>

namespace Lumeda
{
class Engine;

class Timer
{
  friend Engine;

public:
  Timer(iLowLevelSystem& lowLevelSystem);
  ~Timer() = default;

  const size_t& GetFrameCount() { return m_Framecount; }
  const float& GetDeltaTime() { return m_DeltaTime; }

protected:
  void IncrementFramecount() { m_Framecount++; }
  void Tick();

private:
  iLowLevelSystem& m_LowLevelSystem;

  size_t m_Framecount = 0;

  float m_DeltaTime = 0.0f;

  float m_PreviousTime;
};

} // namespace Lumeda