#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/ParticleSystemDescriptor.h>

using namespace Lumeda;

sParticleSystemDescriptor::~sParticleSystemDescriptor()
{
    if (Particles != nullptr)
    {
        LUMEDA_FREE(Particles);
        Particles = nullptr;
    }
}

void sParticleSystemDescriptor::Update()
{
    LUMEDA_PROFILE;
    float currentTime = LUMEDA_TIME.GetElapsedTime();
    float deltaSpawn = currentTime - m_LastSpawnTime;
    int spawnCount;
    if (ParticleDelay > 0)
    {
        spawnCount = deltaSpawn / ParticleDelay;
    }
    else
    {
        spawnCount = m_MaxParticles;
    }
    int leftToSpawn = spawnCount;

    // Spawn the particles
    int lastFreeSlot = 0;
    while (leftToSpawn > 0)
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
        sParticle& part = Particles[lastFreeSlot];
        part.InitialLifetime = LUMEDA_RANDFLOAT(InitialLifetimeRange.x, InitialLifetimeRange.y);
        part.Velocity = glm::vec3(LUMEDA_RANDFLOAT(InitialVelocityXRange.x, InitialVelocityXRange.y),
            LUMEDA_RANDFLOAT(InitialVelocityYRange.x, InitialVelocityYRange.y),
            LUMEDA_RANDFLOAT(InitialVelocityZRange.x, InitialVelocityZRange.y));
        part.AngularVelocity = LUMEDA_RANDFLOAT(InitialAngularVelocityRange.x, InitialAngularVelocityRange.y);
        part.Lifetime = part.InitialLifetime;
        part.Position = glm::vec3(0.0f);
        part.Rotation = 0.0f;
        part.InitialSize = LUMEDA_RANDFLOAT(InitialSizeRange.x, InitialSizeRange.y);
        part.Size = part.InitialSize;
        part.Color = glm::vec4(1.0f);
        leftToSpawn--;
    }
    m_LastSpawnTime += (spawnCount - leftToSpawn) * ParticleDelay;

    // Update the others
    float deltaTime = LUMEDA_TIME.GetDeltaTime();
    for (int i = 0; i < m_MaxParticles; i++)
    {
        sParticle& part = Particles[i];
        if (part.Lifetime <= 0.0f)
            continue;
        part.Position += part.Velocity * deltaTime;
        part.Rotation += part.AngularVelocity * deltaTime;
        // part.Size = part.InitialSize * (part.Lifetime / part.InitialLifetime);
        //  Experimental
        part.Size = part.InitialSize * (pow(part.Lifetime, 2) / pow(part.InitialLifetime, 2)) *
                    std::min(1.0f, -1 + (float)exp(-(part.Lifetime - part.InitialLifetime) * 10.0f));

        part.Lifetime -= deltaTime;
    }
}

void sParticleSystemDescriptor::SetMaxParticles(size_t maxParticles)
{
    LUMEDA_PROFILE;

    if (maxParticles == 0)
    {
        if (Particles != nullptr)
        {
            LUMEDA_FREE(Particles);
            Particles = nullptr;
        }
        m_MaxParticles = 0;
        return;
    }

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

    for (size_t i = 0; i < maxParticles; i++)
    {
        Particles[i] = sParticle();
    }
    m_MaxParticles = maxParticles;
}

size_t sParticleSystemDescriptor::GetMaxParticles()
{
    LUMEDA_PROFILE;
    return m_MaxParticles;
}