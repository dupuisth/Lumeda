#pragma once

#include <Lumeda/Auto/PIDTypes.h>
#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class PID
{
  public:
    PID();
    PID(PIDConfiguration configuration);

    PIDOutput Run(const PIDInput& input);
    PIDOutput Run(const PIDInput& input, PIDMemory& memory);

    PIDConfiguration& GetConfiguration();

  private:
    PIDConfiguration m_pidConfiguration;
    PIDMemory m_memory;
};

} // namespace Lumeda