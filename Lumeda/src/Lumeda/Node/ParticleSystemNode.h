#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>
#include <Lumeda/Renderer/ParticleSystemDescriptor.h>

namespace Lumeda
{
    class ParticleSystemNode : public Node
    {
    public:
        ParticleSystemNode();
        virtual ~ParticleSystemNode();

        void OnUpdate() override;
        void OnRender() override;
        void OnRenderImGui() override;

        sParticleSystemDescriptor& GetDescriptor();

    private:
        sParticleSystemDescriptor m_Descriptor;
    };
}