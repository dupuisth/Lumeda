#include <Lumeda/Node/LightNode.h>

#include <Lumeda/Node/RootNode.h>

using namespace Lumeda;

LightNode::LightNode() : m_Light()
{
    LUMEDA_PROFILE;
    SetName("LightNode");
}

LightNode::~LightNode()
{
    LUMEDA_PROFILE;
}

sLight& LightNode::GetLight()
{
    LUMEDA_PROFILE;
    return m_Light;
}

void LightNode::OnRender()
{
    LUMEDA_PROFILE;
}

void LightNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();
}

void LightNode::OnEnable()
{
    LUMEDA_PROFILE;
    std::shared_ptr<RootNode> rootNode = GetRootNode();
    if (rootNode == nullptr)
    {
        LUMEDA_CORE_WARN("[LightNode::OnEnable] Root not was not found");
        return;
    }

    rootNode->AddLightNode(std::static_pointer_cast<LightNode>(shared_from_this()));
}

void LightNode::OnDisable()
{
    LUMEDA_PROFILE;
    std::shared_ptr<RootNode> rootNode = GetRootNode();
    if (rootNode == nullptr)
    {
        LUMEDA_CORE_WARN("[LightNode::OnDisable] Root not was not found");
        return;
    }

    rootNode->RemoveLightNode(std::static_pointer_cast<LightNode>(shared_from_this()));
}