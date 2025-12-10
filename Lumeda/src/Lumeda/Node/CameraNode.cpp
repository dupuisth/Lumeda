#include <Lumeda/Node/CameraNode.h>
#include <imgui.h>
#include "CameraNode.h"

using namespace Lumeda;

CameraNode::CameraNode() : m_Camera(&m_Transform)
{
    LUMEDA_PROFILE;
    SetName("CameraNode");
}

CameraNode::~CameraNode()
{
    LUMEDA_PROFILE;
}


Camera& Lumeda::CameraNode::GetCamera()
{
    LUMEDA_PROFILE;
    return m_Camera;
}

void CameraNode::OnUpdate()
{
    LUMEDA_PROFILE;
    m_Camera.SetDirty(); // For now, force rebuild each frames, a callback on transform will be needed
}

void CameraNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();
    ImGui::SeparatorText("CameraNode");
    if (ImGui::Checkbox("IsMain", &m_IsMain))
    {
        Camera::SetCurrent(&m_Camera);
    }
}