#include <Lumeda/Core/Engine.h>
#include <Lumeda/Node/SpinNode.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace Lumeda;

SpinNode::SpinNode(glm::vec3 rotationDelta, float rotationMultiplier) : m_RotationDelta(rotationDelta), m_RotationMultiplier(rotationMultiplier)
{
    LUMEDA_PROFILE;
    SetName("SpinNode");
}

SpinNode::~SpinNode()
{
    LUMEDA_PROFILE;
}

void SpinNode::OnUpdate()
{
    LUMEDA_PROFILE;
    m_Transform.Rotate(m_RotationDelta * m_RotationMultiplier * LUMEDA_TIME.GetDeltaTime());
}

void SpinNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();
    ImGui::SeparatorText("SpinNode");
    ImGui::DragFloat3("Rotation Delta", glm::value_ptr(m_RotationDelta), 0.1f, -10.0f, 10.0f);
    ImGui::InputFloat("Multiplier", &m_RotationMultiplier);
}
