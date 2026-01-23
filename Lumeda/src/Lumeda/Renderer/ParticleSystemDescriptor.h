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
        glm::vec3 Position;
        float Rotation;
        float Lifetime;
        float InitialLifetime;

        glm::vec4 Color;
        float Size;

        glm::vec3 Velocity;
        float AngularVelocity;
    };

    struct sParticleSystemDescriptor
    {
    public:
        sParticle* Particles;

        Transform* OriginTransform;
        Shader* ParticleShader;
        Mesh* ParticleMesh;
        Texture2D* ParticleTexture;

        glm::vec2 InitialVelocityXRange;
        glm::vec2 InitialVelocityYRange;
        glm::vec2 InitialVelocityZRange;

        glm::vec2 InitialLifetimeRange;
        glm::vec2 InitialAngularVelocityRange;

        glm::vec4 ColorMin;
        glm::vec4 ColorMax;

        float ParticleDelay;

        void Update();

    private:
        void SetMaxParticles(size_t value);
        size_t GetMaxParticles();

        size_t m_MaxParticles;
        float m_LastSpawnTime;
    };
}