#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

namespace Lumeda
{
    struct sParticleSystemVecMinMax
    {
        glm::vec3 Max;
        glm::vec3 Min;
    };

    struct sParticleSystemFloatMinMax
    {
        float Min;
        float Max;
    };

    struct sParticleSystemDescriptor
    {
        sParticleSystemVecMinMax InitialVelocity;
        sParticleSystemVecMinMax Acceleration;
        sParticleSystemFloatMinMax Scale;
        sParticleSystemVecMinMax Scale;
    };
}