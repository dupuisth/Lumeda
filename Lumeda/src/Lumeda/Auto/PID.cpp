#include <Lumeda/Auto/PID.h>
#include <Lumeda/Core/Engine.h>

using namespace Lumeda;

PID::PID() : m_memory()
{
    LUMEDA_PROFILE;
    m_pidConfiguration.Kp = 1.0f;
    m_pidConfiguration.Ki = 1.0f;
    m_pidConfiguration.Kd = 1.0f;
}

PID::PID(PIDConfiguration configuration) : m_pidConfiguration(configuration), m_memory()
{
    LUMEDA_PROFILE;
}

PIDOutput PID::Run(const PIDInput& input)
{
    LUMEDA_PROFILE;
    return Run(input, m_memory);
}

PIDOutput PID::Run(const PIDInput& input, PIDMemory& memory)
{
    LUMEDA_PROFILE;
    float currentTime = LUMEDA_TIME.GetElapsedTime();
    float deltaTime = currentTime - memory.previousTime;

    if (!memory.ready)
    {
        memory.previousTime = currentTime;
        memory.ready = true;
        memory.integral = 0.0f;
        memory.previousError = input.baseline - input.measure;
        PIDOutput output = {.command = 0.0f};
        LUMEDA_CORE_WARN("[PID] Not initialized");
        return output;
    }

    if (deltaTime <= 0.0f)
    {
        PIDOutput output = {.command = 0.0f};
        return output;
    }

    // Calculate the error
    float error = input.baseline - input.measure;

    // Proportional correction
    float Cp = error * m_pidConfiguration.Kp;

    // Derivative correction
    float Cd = ((error - memory.previousError) / deltaTime) * m_pidConfiguration.Kd;

    // Integrative correction
    memory.integral += error * deltaTime;
    float Ci = memory.integral * m_pidConfiguration.Ki;

    memory.previousError = error;
    memory.previousTime = currentTime;

    PIDOutput output;
    output.command = Cp + Cd + Ci;
    output.cp = Cp;
    output.cd = Cd;
    output.ci = Ci;
    output.integralError = memory.integral;
    output.error = error;
    return output;
}

PIDConfiguration& PID::GetConfiguration()
{
    return m_pidConfiguration;
}