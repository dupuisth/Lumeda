#pragma once

#include <Lumeda/Node/Node.h>

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
    };
}