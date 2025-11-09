#include <Lumeda/Node/PlayerNode.h>
#include <Lumeda/Node/CameraNode.h>

using namespace Lumeda;

PlayerNode::PlayerNode() 
{
    LUMEDA_PROFILE;

    // Directly add a CameraNode
    std::shared_ptr<CameraNode> cameraNode = std::make_shared<CameraNode>();
    AddChild(cameraNode);

    SetName("PlayerNode");
}

PlayerNode::~PlayerNode()
{ 
    LUMEDA_PROFILE;
}

void PlayerNode::OnUpdate()
{
    LUMEDA_PROFILE;
}

void PlayerNode::OnRender()
{
    LUMEDA_PROFILE;
}

void PlayerNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();
}