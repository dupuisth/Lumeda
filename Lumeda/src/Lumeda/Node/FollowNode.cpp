#include <Lumeda/Core/Engine.h>
#include <Lumeda/Node/FollowNode.h>
#include <imgui.h>

using namespace Lumeda;

FollowNode::FollowNode() : m_Target(nullptr), m_Pid()
{
}

FollowNode::~FollowNode()
{
}

void FollowNode::SetTarget(Node* node)
{
    m_Target = node;
}

Node* FollowNode::GetTarget()
{
    return m_Target;
}

void FollowNode::OnUpdate()
{
    PIDInput input;
    PIDMemory* memory;
    PIDOutput output;

    // Run for the X axis
    memory = &m_Memories[0];
    input.baseline = m_Target->GetTransform().GetPosition().x;
    input.measure = m_Transform.GetPosition().x;
    output = m_Pid.Run(input, *memory);
    // Apply the command
    m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() + glm::vec3(output.command * LUMEDA_TIME.GetDeltaTime(), 0.0f, 0.0f));

    // Run for the Y axis
    memory = &m_Memories[1];
    input.baseline = m_Target->GetTransform().GetPosition().y;
    input.measure = m_Transform.GetPosition().y;
    output = m_Pid.Run(input, *memory);
    // Apply the command
    m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() + glm::vec3(0.0f, output.command * LUMEDA_TIME.GetDeltaTime(), 0.0f));

    // Run for the Z axis
    memory = &m_Memories[2];
    input.baseline = m_Target->GetTransform().GetPosition().z;
    input.measure = m_Transform.GetPosition().z;
    output = m_Pid.Run(input, *memory);
    // Apply the command
    m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() + glm::vec3(0.0f, 0.0f, output.command * LUMEDA_TIME.GetDeltaTime()));
}

void FollowNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();

    ImGui::SeparatorText("PID");
    ImGui::SliderFloat("Kd", &m_Pid.GetConfiguration().Kd, 0.0001f, 5.0f);
    ImGui::SliderFloat("Ki", &m_Pid.GetConfiguration().Ki, 0.0001f, 5.0f);
    ImGui::SliderFloat("Kp", &m_Pid.GetConfiguration().Kp, 0.0001f, 5.0f);
}