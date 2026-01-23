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

    // Duplicate from Node::~Node(), check the below comment that was copied from the old version
     // If the Scene gets teared down from RootNode (Delete(rootNode))
     // Then this dynamic_cast will fail, since the cascade of deletion is done in Node::~Node(), the RootNode::~RootNode() is already done and the RootNode subobject is already destroyed
     // For now, this cause no real issue, just a warning that some lights counldn't be unregistered but it's ok since the scene is completly destroyed
     // But if later this become criticial, consider moving some of the cascade deletion to the RootNode::~RootNode() so that it still lives long enough to be accessed from child nodes

    // This code allows the use of GetRootNode() until the last moment, since it is RootNode that calls Delete on the childs,
    // the RootNode subobject is not destroyed until all the childrens are.

    // All of the lifecycle should be processed, we don't want to remove a node that is no longer a child
    ProcessLifecycle();

    // Delete the child nodes
    for (auto child : m_Children)
    {
        LUMEDA_FREE(child);
    }
    m_Children.clear();
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
    if (lightNode == nullptr)
    {
        LUMEDA_CORE_WARN("[RootNode] Trying to add a nullptr LightNode");
        return;
    }

    auto it = std::find(m_LightNodes.begin(), m_LightNodes.end(), lightNode);
    if (it == m_LightNodes.end())
    {
        m_LightNodes.push_back(lightNode);
        LUMEDA_CORE_TRACE("[RootNode] Registered a new light to the RootNode (total: {0})", m_LightNodes.size());
    }
    else
    {
        LUMEDA_CORE_WARN("[RootNode] Trying to add a light that is already registered");
    }

}

void RootNode::RemoveLightNode(LightNode* lightNode)
{
    LUMEDA_PROFILE;
    if (lightNode == nullptr)
    {
        LUMEDA_CORE_WARN("[RootNode] Trying to remove a nullptr LightNode");
        return;
    }

    auto it = std::find(m_LightNodes.begin(), m_LightNodes.end(), lightNode);
    if (it != m_LightNodes.end())
    {
        m_LightNodes.erase(it);
        LUMEDA_CORE_TRACE("[RootNode] Removed a light from the RootNode (total: {0})", m_LightNodes.size());
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