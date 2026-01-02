#include <Lumeda/Node/RootNode.h>
#include <imgui.h>

#include <Lumeda/Node/LightNode.h>
#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Light.h>

using namespace Lumeda;

RootNode::RootNode()
    : m_LightNodes()
{
    LUMEDA_PROFILE;
    SetName("RootNode");
}

RootNode::~RootNode()
{
    LUMEDA_PROFILE;
}

void RootNode::OnRenderImGui()
{
    LUMEDA_PROFILE;
    Node::OnRenderImGui();

    ImGui::SeparatorText("RootNode");
    ImGui::LabelText("Light count", "%d", m_LightNodes.size());
}

void RootNode::AddLightNode(LightNode* lightNode)
{
    LUMEDA_PROFILE;
    auto it = std::find(m_LightNodes.begin(), m_LightNodes.end(), lightNode);
    if (it == m_LightNodes.end())
    {
        m_LightNodes.push_back(lightNode);
    }
    else
    {
        LUMEDA_CORE_WARN("[RootNode] Trying to add a light that is already registered");
    }
}

void RootNode::RemoveLightNode(LightNode* lightNode)
{
    LUMEDA_PROFILE;

    auto it = std::find(m_LightNodes.begin(), m_LightNodes.end(), lightNode);
    if (it != m_LightNodes.end())
    {
        m_LightNodes.erase(it);
    }
    else
    {
        LUMEDA_CORE_WARN("[RootNode] Trying to remove a light that is not registered");
    }
}

std::vector<LightNode*>& RootNode::GetLightNodes()
{
    LUMEDA_PROFILE;
    return m_LightNodes;
}

void RootNode::OnRender()
{
    LUMEDA_PROFILE;
    // Prepare shaders
    Renderer& renderer = Engine::Get().GetRenderer();


    const std::unordered_map<std::string, Shader*>& shadersMap = renderer.ListShaders();
    for (auto const& [name, shader] : shadersMap)
    {
        shader->Bind();
        sLightPassCounter passCounter;
        for (auto const& lightNode : m_LightNodes)
        {
            lightNode->GetLight().SendToShader(shader, &lightNode->GetTransform(), passCounter);
        }

        shader->SetUniform("u_PointLightsCount", passCounter.Current(eLightType::POINT));
        shader->SetUniform("u_SpotLightsCount", passCounter.Current(eLightType::SPOT));
        shader->SetUniform("u_DirectionnalLightsCount", passCounter.Current(eLightType::DIRECTIONNAL));
    }
}