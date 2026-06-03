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
    float Kp;

    // Integral action
    float Ki;

    // Derivative action
    float Kd;
};

/**
 * Input of the PID
 */
struct PIDInput
{
  public:
    // Order
    float baseline;

    // Mesured
    float measure;
};

/**
 * Memory of the PID
 */
struct PIDMemory
{
  public:
    // Previous execution time
    float previousTime;

    // If this is not the first iteration
    bool ready;

    // Previous error
    float previousError;

    // Integral
    float integral;
};

/**
 * Output of the PID
 */
struct PIDOutput
{
  public:
    // Output command
    float command;
};
} // namespace Lumeda