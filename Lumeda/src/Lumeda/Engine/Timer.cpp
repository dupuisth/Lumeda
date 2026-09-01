#include <chrono>
#include <Lumeda/Engine/Timer.h>

using namespace Lumeda;

Timer::Timer(iLowLevelSystem& lowLevelSystem) : m_LowLevelSystem(lowLevelSystem)
{
  m_PreviousTime = m_LowLevelSystem.GetElapsedTime();
}

void Timer::Tick()
{
  float now = m_LowLevelSystem.GetElapsedTime();
  m_DeltaTime = now - m_PreviousTime;

  IncrementFramecount();

  m_PreviousTime = now;
}