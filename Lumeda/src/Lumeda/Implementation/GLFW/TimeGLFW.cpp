#include <GLFW/glfw3.h>
#include <Lumeda/Implementation/GLFW/TimeGLFW.h>

using namespace Lumeda;

TimeGLFW::TimeGLFW() : m_DeltaTime(0.0f), m_FrameCount(0), m_PreviousTime(0.0f)
{
    LUMEDA_PROFILE;
    m_Time = (float)glfwGetTime();
}

TimeGLFW::~TimeGLFW()
{
    LUMEDA_PROFILE;
}

void TimeGLFW::Tick()
{
    LUMEDA_PROFILE;
    m_PreviousTime = m_Time;
    m_Time = (float)glfwGetTime();

    m_DeltaTime = m_Time - m_PreviousTime;
    m_FrameCount++;
}

float TimeGLFW::GetElapsedTime()
{
    LUMEDA_PROFILE;
    return m_Time;
}

float TimeGLFW::GetPreciseTime()
{
    LUMEDA_PROFILE;
    return (float)glfwGetTime();
}

float TimeGLFW::GetDeltaTime()
{
    LUMEDA_PROFILE;
    return m_DeltaTime;
}

size_t TimeGLFW::GetFrameCount()
{
    LUMEDA_PROFILE;
    return m_FrameCount;
}
