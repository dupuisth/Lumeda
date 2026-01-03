#include <Lumeda/Node/Node.h>

#include <Lumeda/Node/RootNode.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Lumeda;

Node::Node()
    : m_Name("Node"), m_IsSelfEnabled(true), m_isEnabled(true), m_Parent(nullptr), m_PendingParent(nullptr), m_HasPendingParentChange(false), m_PendingEnabledState(true), m_HasPendingEnabledChange(false), m_Transform(this), m_HasStarted(false), m_isDestroyPending(false)
{
    LUMEDA_PROFILE;
    LUMEDA_CORE_TRACE("[Node] Created {0}", m_Name);
}

Node::~Node()
{
    LUMEDA_PROFILE;
    
    // All of the lifecycle should be processed, we don't want to remove a node that is no longer a child
    ProcessLifecycle();
    
    LUMEDA_CORE_ASSERT(m_PendingAdd.size() == 0, "There should be no pending children after ProcessLifecycle");

    // Delete the child nodes
    for (auto child : m_Children)
    {
        Delete(child);
    }

    // Remove the reference to the parent
    if (m_Parent != nullptr)
    {
        SetParent(nullptr);
    }

    LUMEDA_CORE_TRACE("[Node] Deleted {0}", m_Name);
}

void Node::ProcessLifecycle()
{
    LUMEDA_PROFILE;

    // Apply hierarchy changes (parent, add/remove children)
    ApplyPendingHierarchyChanges();

    // Apply enable/disable state changes
    ApplyPendingEnableChanges();

    // Process lifecycle for ALL children (enabled or disabled)
    for (auto& child : m_Children)
    {
        if (child)
        {
            child->ProcessLifecycle();
        }
    }

    ApplyPendingHierarchyChanges();
}

void Node::ApplyPendingHierarchyChanges()
{
    LUMEDA_PROFILE;

    // Remove children first
    for (auto& nodeToRemove : m_PendingRemove)
    {
        auto it = std::find(m_Children.begin(), m_Children.end(), nodeToRemove);
        if (it != m_Children.end())
        {
            std::string name = nodeToRemove->GetName();

            // Clear parent reference
            nodeToRemove->m_Parent = nullptr;

            // Remove from children list
            m_Children.erase(it);

            // The child will recalculate its enabled state in its own ApplyPendingEnableChanges
            LUMEDA_CORE_TRACE("[NODE] ({0}) Removed \"{1}\" as a child", this->GetName(), name);
        }
    }
    m_PendingRemove.clear();

    // Add new children
    for (auto& nodeToAdd : m_PendingAdd)
    {
        // Check if already in children (shouldn't happen, but safety check)
        auto it = std::find(m_Children.begin(), m_Children.end(), nodeToAdd);
        if (it == m_Children.end())
        {
            // Add to children list
            m_Children.push_back(nodeToAdd);

            // Set parent reference
            nodeToAdd->m_Parent = this;

            // The child will recalculate its enabled state in its own ApplyPendingEnableChanges
            LUMEDA_CORE_TRACE("[NODE] ({0}) Added \"{1}\" as a child", this->GetName(), nodeToAdd->GetName());
        }
    }
    m_PendingAdd.clear();

    
    for (size_t i = 0; i < m_Children.size(); i++)
    {
        if (m_Children[i]->m_isDestroyPending)
        {
            Delete(m_Children[i]);
            m_Children.erase(std::begin(m_Children) + i);
            i--;
        }
    }

    // Apply parent change for this node
    if (m_HasPendingParentChange)
    {
        Node* oldParent = m_Parent;
        m_Parent = m_PendingParent;
        m_HasPendingParentChange = false;

        // Notify of parent change
        OnParentChanged(oldParent, m_Parent);

        // Enabled state will be recalculated in ApplyPendingEnableChanges
    }
}

void Node::ApplyPendingEnableChanges()
{
    LUMEDA_PROFILE;

    bool wasEnabled = m_isEnabled;

    // Apply pending enabled state change if any
    if (m_HasPendingEnabledChange)
    {
        m_IsSelfEnabled = m_PendingEnabledState;
        m_HasPendingEnabledChange = false;
    }

    // Recalculate actual enabled state based on self and parent
    m_isEnabled = m_IsSelfEnabled && (!m_Parent || m_Parent->m_isEnabled);

    // Trigger callbacks only if state actually changed
    if (wasEnabled != m_isEnabled)
    {
        if (m_isEnabled)
        {
            OnEnable();
        }
        else
        {
            OnDisable();
        }
    }
}

void Node::Update()
{
    LUMEDA_PROFILE;

    // Only process if enabled
    if (!m_isEnabled || m_isDestroyPending)
        return;

    if (!m_HasStarted)
    {
        OnEnable();
        m_HasStarted = true;
    }

    // Call virtual method for derived classes
    OnUpdate();

    // Update all children (they will check their own enabled state)
    for (auto& child : m_Children)
    {
        if (child)
        {
            child->Update();
        }
    }
}

void Node::Render()
{
    LUMEDA_PROFILE;

    // Only render if enabled
    if (!m_isEnabled)
        return;

    // Call virtual method for derived classes
    OnRender();

    // Render all children (they will check their own enabled state)
    for (auto& child : m_Children)
    {
        if (child)
        {
            child->Render();
        }
    }
}

void Node::RenderImGui()
{
    LUMEDA_PROFILE;

    // Renders for all nodes (even disabled ones)
    // This allows debugging and inspection of disabled nodes

    // Call virtual method for derived classes
    OnRenderImGui();
}

void Node::OnRender()
{
    LUMEDA_PROFILE;
}

void Node::OnUpdate()
{
    LUMEDA_PROFILE;
}

void Node::OnEnable()
{
    LUMEDA_PROFILE;
}

void Node::OnDisable()
{
    LUMEDA_PROFILE;
}

void Node::OnParentChanged(Node* oldParent, Node* newParent)
{
    LUMEDA_PROFILE;
}


void Node::SetParent(Node* newParent)
{
    LUMEDA_PROFILE;

    // Check if already has this parent
    if (m_Parent == newParent)
        return;

    // Prevent setting self as parent
    if (newParent == this)
        return;

    // Queue removal from old parent
    if (m_Parent)
    {
        m_Parent->RemoveChild(this);
    }

    // Queue parent change (will be applied in ProcessLifecycle)
    m_PendingParent = newParent;
    m_HasPendingParentChange = true;

    // Queue addition to new parent
    if (newParent)
    {
        newParent->AddChild(this);
    }
}

void Node::AddChild(Node* node, bool immediate)
{
    LUMEDA_PROFILE;

    if (!node)
        return;


    // Prevent adding self as child
    if (node == this)
        return;
    
    // Check if already in pending add list
    auto it = std::find(m_PendingAdd.begin(), m_PendingAdd.end(), node);
    if (it != m_PendingAdd.end())
        return; // Already pending addition

    // Check if already a child
    auto childIt = std::find(m_Children.begin(), m_Children.end(), node);
    if (childIt != m_Children.end())
        return; // Already a child

    // Queue for addition (will be applied in ProcessLifecycle)
    if (immediate)
    {
        m_Children.push_back(node);
        node->m_Parent = this;
        LUMEDA_CORE_TRACE("[NODE] ({0}) Added \"{1}\" as a child (immediate)", this->GetName(), node->GetName());

    }
    else
    {
        m_PendingAdd.push_back(node);
        LUMEDA_CORE_TRACE("[NODE] ({0}) Pending adding \"{1}\" as a child", this->GetName(), node->GetName());
    }
}

void Node::RemoveChild(Node* node)
{
    LUMEDA_PROFILE;

    if (!node)
        return;


    // Check if already in pending remove list
    auto it = std::find(m_PendingRemove.begin(), m_PendingRemove.end(), node);
    if (it != m_PendingRemove.end())
        return; // Already pending removal

    // Check if actually a child
    auto childIt = std::find(m_Children.begin(), m_Children.end(), node);
    if (childIt == m_Children.end())
        return; // Not a child

    // Queue for removal (will be applied in ProcessLifecycle)
    m_PendingRemove.push_back(node);
    LUMEDA_CORE_TRACE("[NODE] ({0}) Pending removing \"{1}\" as a child", this->GetName(), node->GetName());
}

void Node::Destroy()
{
    LUMEDA_PROFILE;
    m_isDestroyPending = true;
}

RootNode* Node::GetRootNode()
{
    Node* currentNode = this;
    while (currentNode->m_Parent != nullptr)
    {
        currentNode = currentNode->m_Parent;
    }

    RootNode* rootNode = dynamic_cast<RootNode*>(currentNode);
    return rootNode;
}

void Node::SetEnabled(bool enabled)
{
    LUMEDA_PROFILE;

    // Check if already in this state or switching to this state
    if (m_HasPendingEnabledChange)
    {
        if (m_PendingEnabledState == enabled) return;
    }
    else if (m_IsSelfEnabled == enabled)
        return;

    // Queue enabled state change (will be applied in ProcessLifecycle)
    m_PendingEnabledState = enabled;
    m_HasPendingEnabledChange = true;
}

void Node::OnRenderImGui()
{
    char labelBuffer[512];
    strcpy(labelBuffer, m_Name.c_str());
    if (ImGui::InputText("Label", labelBuffer, 512))
    {
        m_Name = labelBuffer;
    }
    ImGui::SameLine();
    if (ImGui::Button("Destroy"))
    {
        Destroy();
    }

    if (ImGui::DragFloat3("Position", glm::value_ptr(m_Transform.GetLocalPositionRef()), 0.05f, -100.0f, 100.0f))
    {
        m_Transform.SetDirty();
    }

    glm::vec3 rotationEuler = m_Transform.GetLocalRotationEulerAngles();
    if (ImGui::DragFloat3("Rotation Euleur", glm::value_ptr(rotationEuler), 0.1f, -360.0f, 360.0f))
    {
        m_Transform.SetLocalRotationEulerAngles(rotationEuler);
        m_Transform.SetDirty();
    }

    glm::quat rotation = m_Transform.GetLocalRotation();
    if (ImGui::DragFloat4("Rotation", glm::value_ptr(rotation)))
    {

    }

    if (ImGui::DragFloat3("Scale", glm::value_ptr(m_Transform.GetLocalScaleRef()), 0.1f, -360.0f, 360.0f))
    {
        m_Transform.SetDirty();
    }

    ImGui::SeparatorText("Global");
    glm::vec3 globalPosition = m_Transform.GetPosition();
    if (ImGui::DragFloat3("Global Position", glm::value_ptr(globalPosition), 0.1f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput))
    {
    }

    glm::vec3 globalRotationEuler = m_Transform.GetRotationEulerAngles();
    if (ImGui::DragFloat3("Global Rotation Euler", glm::value_ptr(globalRotationEuler), 0.1f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput))
    {
    }

    glm::quat globalRotation = m_Transform.GetRotation();
    if (ImGui::DragFloat4("Global Rotation", glm::value_ptr(rotation)))
    {
    }

    glm::vec3 globalScale = m_Transform.GetScale();
    if (ImGui::DragFloat3("Global Scale", glm::value_ptr(globalScale), 0.1f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput))
    {
    }

    ImGui::SeparatorText("Directions");

    glm::vec3 dummy = m_Transform.GetForward();
    ImGui::DragFloat3("Forward", glm::value_ptr(dummy));

    dummy = m_Transform.GetRight();
    ImGui::DragFloat3("Right", glm::value_ptr(dummy));

    dummy = m_Transform.GetUp();
    ImGui::DragFloat3("Up", glm::value_ptr(dummy));
}