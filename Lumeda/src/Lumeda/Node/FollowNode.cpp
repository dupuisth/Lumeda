#include <Lumeda/Core/Engine.h>
#include <Lumeda/Node/FollowNode.h>
#include <Lumeda/Node/RootNode.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace Lumeda;

FollowNode::FollowNode() :
    m_Target(nullptr),
    m_Pid(),
    m_ConstantPerturbation(0.0f),
    m_PerturbationIntensity(0.0f),
    m_CurrentPositionMemory(0),
    m_PositionLastSampleTime(0.0f),
    m_PositionsMemory()
{
    LUMEDA_PROFILE;
}

FollowNode::~FollowNode()
{
    LUMEDA_PROFILE;
}

void FollowNode::SetTarget(Node* node)
{
    LUMEDA_PROFILE;
    m_Target = node;
}

Node* FollowNode::GetTarget()
{
    LUMEDA_PROFILE;
    return m_Target;
}

PID& FollowNode::GetPid()
{
    LUMEDA_PROFILE;
    return m_Pid;
}

void FollowNode::OnUpdate()
{
    LUMEDA_PROFILE;

    // Save position if the expected time passed
    float currentTime = LUMEDA_TIME.GetElapsedTime();
    if (currentTime - m_PositionLastSampleTime > POSITION_SAMPLE_TIME)
    {
        m_PositionLastSampleTime = currentTime;
        m_PositionsMemory[m_CurrentPositionMemory++] = m_Transform.GetPosition();
        if (m_CurrentPositionMemory >= POSITION_MEMORY_SAMPLES)
        {
            m_CurrentPositionMemory = 0;
        }
    }

    PIDInput input;
    PIDMemory* memory;
    PIDOutput output;

    glm::vec3 movement(0.0f);

    // Run for the X axis
    memory = &m_Memories[0];
    input.baseline = m_Target->GetTransform().GetPosition().x;
    input.measure = m_Transform.GetPosition().x;
    output = m_Pid.Run(input, *memory);
    m_Outputs[0] = output;
    movement.x += output.command;

    // Run for the Y axis
    memory = &m_Memories[1];
    input.baseline = m_Target->GetTransform().GetPosition().y;
    input.measure = m_Transform.GetPosition().y;
    output = m_Pid.Run(input, *memory);
    m_Outputs[1] = output;
    movement.y += output.command;

    // Run for the Z axis
    memory = &m_Memories[2];
    input.baseline = m_Target->GetTransform().GetPosition().z;
    input.measure = m_Transform.GetPosition().z;
    output = m_Pid.Run(input, *memory);
    m_Outputs[2] = output;
    movement.z += output.command;

    // Apply the constant perturbation
    movement += m_ConstantPerturbation * m_PerturbationIntensity;

    // Apply the movement
    m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() + movement * LUMEDA_TIME.GetDeltaTime());
}

void FollowNode::OnRender()
{
    Gizmos& gizmos = LUMEDA_GIZMOS;
    gizmos.SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));
    for (size_t i = 0; i < POSITION_MEMORY_SAMPLES; i++)
    {
        gizmos.DrawCube(m_PositionsMemory[i], glm::vec3(0.0f), glm::vec3(0.2f));
    }
}

void FollowNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();

    ImGui::SeparatorText("PID");
    ImGui::SliderFloat("Kd", &m_Pid.GetConfiguration().Kd, 0.0001f, 5.0f);
    ImGui::SliderFloat("Ki", &m_Pid.GetConfiguration().Ki, 0.0001f, 5.0f);
    ImGui::SliderFloat("Kp", &m_Pid.GetConfiguration().Kp, 0.0001f, 5.0f);

    if (ImGui::CollapsingHeader("Target"))
    {
        RootNode* rootNode = GetRootNode();
        if (rootNode == nullptr)
        {
            ImGui::Text("Root node not found");
        }
    }

    if (ImGui::CollapsingHeader("Values"))
    {
        for (size_t i = 0; i < 3; i++)
        {
            PIDOutput& output = m_Outputs[i];
            ImGui::Spacing();
            ImGui::Text("PID: %i", i);
            ImGui::LabelText("Command", "%.2f", output.command);
            ImGui::LabelText("Error", "%.2f", output.error);
            ImGui::LabelText("Ci", "%.2f", output.ci);
            ImGui::LabelText("Cd", "%.2f", output.cd);
            ImGui::LabelText("Cp", "%.2f", output.cp);
        }
    }

    if (ImGui::CollapsingHeader("Perturbations"))
    {
        ImGui::SliderFloat3("Perturbation", glm::value_ptr(m_ConstantPerturbation), -5.0f, 5.0f);
        ImGui::SliderFloat("Intensity", &m_PerturbationIntensity, 0.0f, 1.0f);
    }
}