#include <chrono>
#include <Lumeda/Engine/Timer.h>

using namespace Lumeda;

Timer::Timer()
{
  m_PreviousTime = std::chrono::high_resolution_clock::now();
}

void Timer::Tick()
{
  std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();

  const std::chrono::duration<float> diff = now - m_PreviousTime;
  m_DeltaTime = diff.count();

  IncrementFramecount();

  m_PreviousTime = now;
}