#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Texture.h>
#include <Lumeda/Renderer/Mesh.h>

#include <glm/glm.hpp>

namespace Lumeda
{
    struct sParticle
    {
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        float Rotation = 0.0f;
        float Lifetime = 0.0f;
        float InitialLifetime = 0.0f;

        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        float Size = 1.0f;
        float InitialSize = 1.0f;

        glm::vec3 Velocity = { 0.0f, 0.0f, 0.0f };
        float AngularVelocity = 0.0f;
    };

    struct sParticleSystemDescriptor
    {
    public:
        ~sParticleSystemDescriptor();
    public:
        sParticle* Particles = nullptr;

        Transform* OriginTransform = nullptr;
        std::string ParticleMesh = "";
        std::string ParticleMaterial = "";

        glm::vec2 InitialVelocityXRange = { 0.0f, 0.0f };
        glm::vec2 InitialVelocityYRange = { 0.0f, 0.0f };
        glm::vec2 InitialVelocityZRange = { 0.0f, 0.0f };

        glm::vec2 InitialLifetimeRange = { 0.0f, 0.0f };
        glm::vec2 InitialAngularVelocityRange = { 0.0f, 0.0f };
        glm::vec2 InitialSizeRange = { 1.0f, 1.0f };

        glm::vec4 ColorMin = { 1.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 ColorMax = { 1.0f, 1.0f, 1.0f, 1.0f };

        float ParticleDelay = 1;

        void Update();

        void SetMaxParticles(size_t value);
        size_t GetMaxParticles();

    private:
        size_t m_MaxParticles = 0;
        float m_LastSpawnTime = 0.0f;
    };
}