#include <Lumeda/Node/CameraNode.h>
#include <imgui.h>
#include "CameraNode.h"

using namespace Lumeda;

CameraNode::CameraNode()
{
    LUMEDA_PROFILE;
    m_Camera = std::make_shared<Camera>(&m_Transform);
    SetName("CameraNode");
}

CameraNode::~CameraNode()
{
    LUMEDA_PROFILE;
}


std::shared_ptr<Camera> Lumeda::CameraNode::GetCamera()
{
    LUMEDA_PROFILE;
    return m_Camera;
}

void CameraNode::OnUpdate()
{
    LUMEDA_PROFILE;
    m_Camera->SetDirty(); // For now, force rebuild each frames, a callback on transform will be needed
}

void CameraNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();
    ImGui::SeparatorText("CameraNode");
    if (ImGui::Checkbox("IsMain", &m_IsMain))
    {
        m_Camera->SetCurrent();
    }
}