#include <Lumeda/Node/LightNode.h>
#include <Lumeda/Node/RootNode.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace Lumeda;

LightNode::LightNode() : m_Light()
{
    LUMEDA_PROFILE;
    SetName("LightNode");
}

LightNode::~LightNode()
{
    LUMEDA_PROFILE;
    OnDisable(); // Explicit call, overidden methods are not called in the destructor
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

    ImGui::SeparatorText("Light");

    const char* lightTypeItems[] = {"POINT", "SPOT", "DIREC"};
    int currentItem = m_Light.LightType;
    if (ImGui::BeginCombo("Type", lightTypeItems[m_Light.LightType]))
    {
        for (int i = 0; i < sizeof(lightTypeItems) / sizeof(char*); i++)
        {
            bool selected = currentItem == i;
            if (ImGui::Selectable(lightTypeItems[i], selected))
            {
                m_Light.LightType = (eLightType)i;
            }
            if (selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (m_Light.LightType == eLightType::POINT)
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Light.Color));
        ImGui::SliderFloat("Intensity", &m_Light.Intensity, 0.0f, 5.0f, "%.3f");
        ImGui::SliderFloat3("Poly/Linear/Constant", &m_Light.LightCharacteristics.Polyonomial, 0.0f, 5.0f, "%.2f");
    }
    else if (m_Light.LightType == eLightType::SPOT)
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Light.Color));
        ImGui::SliderFloat("Intensity", &m_Light.Intensity, 0.0f, 5.0f, "%.3f");
        ImGui::SliderFloat3("Poly/Linear/Constant", &m_Light.LightCharacteristics.Polyonomial, 0.0f, 5.0f, "%.2f");
        ImGui::SliderAngle("Angle", &m_Light.AngleRad, -360.0f, 360.0f, "%.0f");
    }
    else if (m_Light.LightType == eLightType::DIRECTIONNAL)
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Light.Color));
        ImGui::SliderFloat("Intensity", &m_Light.Intensity, 0.0f, 5.0f, "%.3f");
    }
}

void LightNode::OnEnable()
{
    LUMEDA_PROFILE;
    RootNode* rootNode = GetRootNode();
    if (rootNode == nullptr)
    {
        LUMEDA_CORE_WARN("[LightNode::OnEnable] RootNode was not found");
        return;
    }

    rootNode->AddLightNode(this);
}

void LightNode::OnDisable()
{
    LUMEDA_PROFILE;
    RootNode* rootNode = GetRootNode();
    if (rootNode == nullptr)
    {
        LUMEDA_CORE_WARN("[LightNode::OnDisable] RootNode was not found");
        return;
    }

    rootNode->RemoveLightNode(this);
}