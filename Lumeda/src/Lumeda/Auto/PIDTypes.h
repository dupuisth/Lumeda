#pragma once

namespace Lumeda
{
/**
 * Configuration of the PID
 */
struct PIDConfiguration
{
  public:
    // Proportional action
    float Kp = 0.0f;

    // Integral action
    float Ki = 0.0f;

    // Derivative action
    float Kd = 0.0f;
};

/**
 * Input of the PID
 */
struct PIDInput
{
  public:
    // Order
    float baseline = 0.0f;

    // Mesured
    float measure = 0.0f;
};

/**
 * Memory of the PID
 */
struct PIDMemory
{
  public:
    // Previous execution time
    float previousTime = 0.0f;

    // If this is not the first iteration
    bool ready = false;

    // Previous error
    float previousError = 0.0f;

    // Integral
    float integral = 0.0f;
};

/**
 * Output of the PID
 */
struct PIDOutput
{
  public:
    // Output command
    float command = 0.0f;

    /// Keep track of intermediate values
    float error = 0.0f;
    float ci = 0.0f;
    float cp = 0.0f;
    float cd = 0.0f;
    float integralError = 0.0f;
};
} // namespace Lumeda