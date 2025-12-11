#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>

namespace Lumeda
{
    class LightNode;

    class RootNode : public Node
    {
    public:
        RootNode();
        virtual ~RootNode();

        void AddLightNode(std::shared_ptr<LightNode> lightNode);
        void RemoveLightNode(std::shared_ptr<LightNode> lightNode);

    protected:
        void OnRender() override;
        void OnRenderImGui() override;

    private:
        std::vector<std::shared_ptr<LightNode>> m_LightNodes;
    };
}
