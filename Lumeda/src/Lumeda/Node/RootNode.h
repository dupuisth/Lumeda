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

        void AddLightNode(LightNode* lightNode);
        void RemoveLightNode(LightNode* lightNode);
        std::vector<LightNode*>& GetLightNodes();

    protected:
        void OnRender() override;
        void OnRenderImGui() override;

    private:
        std::vector<LightNode*> m_LightNodes;
    };
}
