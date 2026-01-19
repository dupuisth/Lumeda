#include <Lumeda/Implementation/GLFW/TimeGLFW.h>

#include <GLFW/glfw3.h>

using namespace Lumeda;

TimeGLFW::TimeGLFW()
    : m_DeltaTime(0.0f), m_FrameCount(0), m_PreviousTime(0.0f), m_time(0.0f)
{
    LUMEDA_PROFILE;
}

TimeGLFW::~TimeGLFW()
{
    LUMEDA_PROFILE;
}

void TimeGLFW::Tick()
{
    LUMEDA_PROFILE;
    m_PreviousTime = m_time;
    m_time = (float)glfwGetTime();

    m_DeltaTime = m_time - m_PreviousTime;
    m_FrameCount++;
}

float TimeGLFW::GetTime()
{
    LUMEDA_PROFILE;
    return m_time;
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
