#include <Lumeda/Renderer/ParticleSystemDescriptor.h>

#include <Lumeda/Core/Engine.h>

using namespace Lumeda;


void sParticleSystemDescriptor::Update()
{
    LUMEDA_PROFILE;
    float currentTime = Engine::Get().GetTime().GetElapsedTime();
    float deltaSpawn = currentTime - m_LastSpawnTime;
    int spawnCount = deltaSpawn / ParticleDelay;

    // Spawn the particles
    int lastFreeSlot = 0;
    while (spawnCount > 0)
    {
        // Search for a free particle
        while (lastFreeSlot != m_MaxParticles && Particles[lastFreeSlot].Lifetime > 0.0f)
        {
            lastFreeSlot++;
        }

        if (lastFreeSlot == m_MaxParticles)
        {
            // No more free slot, do not spawn.
            break;
        }

        // Else, there is a free slot, use it
        sParticle part = Particles[lastFreeSlot];
        part.InitialLifetime = LUMEDA_RANDFLOAT(InitialLifetimeRange.x, InitialLifetimeRange.y);
        part.Lifetime = part.InitialLifetime;
        part.Position = glm::vec3(0.0f);
        part.Rotation = 0.0f;
        part.Size = 1.0f;
        part.Color = glm::vec4(1.0f);
        spawnCount--;
    }
    m_LastSpawnTime = currentTime - ParticleDelay * spawnCount;


    // Update the others
    float deltaTime = Engine::Get().GetTime().GetDeltaTime();
    for (int i = 0; i < m_MaxParticles; i++)
    {
        sParticle part = Particles[i];
        if (part.Lifetime <= 0.0f) continue;
        part.Position = part.Velocity * deltaTime;
        part.Rotation = part.AngularVelocity * deltaTime;
        part.Size = part.Lifetime / part.InitialLifetime;
        part.Lifetime -= deltaTime;
    }
}

void sParticleSystemDescriptor::SetMaxParticles(size_t maxParticles)
{
    LUMEDA_PROFILE;
    if (maxParticles > 0)
    {

        if (Particles == nullptr)
        {
            Particles = (sParticle*)LUMEDA_ALLOC_RAW(sizeof(sParticle) * maxParticles);
        }
        else
        {
            Particles = (sParticle*)LUMEDA_REALLOC_RAW(Particles, sizeof(sParticle) * maxParticles);
        }
    }

    if (Particles == nullptr)
    {
        LUMEDA_CORE_ERROR("sParticleSystemDescriptor::SetMaxParticles({0}) Failed to allocate", maxParticles);
        m_MaxParticles = 0;
        return;
    }
    m_MaxParticles = maxParticles;
}

size_t sParticleSystemDescriptor::GetMaxParticles()
{
    LUMEDA_PROFILE;
    return m_MaxParticles;
}