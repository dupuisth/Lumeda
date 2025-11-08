#include <Lumeda/Node/Node.h>

using namespace Lumeda;

Node::Node()
    : m_Name("Node")
    , m_IsSelfEnabled(true)
    , m_isEnabled(true)
    , m_Parent(nullptr)
    , m_PendingParent(nullptr)
    , m_HasPendingParentChange(false)
    , m_PendingEnabledState(true)
    , m_HasPendingEnabledChange(false)
    , m_Transform(this)
{
    LUMEDA_PROFILE;
}

Node::~Node()
{
    LUMEDA_PROFILE;

    // Clear parent reference
    m_Parent = nullptr;

    // Clear children
    m_Children.clear();
    m_PendingAdd.clear();
    m_PendingRemove.clear();
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
            // Clear parent reference
            nodeToRemove->m_Parent = nullptr;

            // Remove from children list
            m_Children.erase(it);

            // The child will recalculate its enabled state in its own ApplyPendingEnableChanges
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
        }
    }
    m_PendingAdd.clear();

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
    if (!m_isEnabled)
        return;

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

    // Render ImGui for all children
    for (auto& child : m_Children)
    {
        if (child)
        {
            child->RenderImGui();
        }
    }
}

void Node::SetParent(std::shared_ptr<Node> newParent)
{
    LUMEDA_PROFILE;

    // Check if already has this parent
    if (m_Parent == newParent.get())
        return;

    // Prevent setting self as parent
    if (newParent.get() == this)
        return;

    // Queue removal from old parent
    if (m_Parent)
    {
        m_Parent->RemoveChild(shared_from_this());
    }

    // Queue parent change (will be applied in ProcessLifecycle)
    m_PendingParent = newParent.get();
    m_HasPendingParentChange = true;

    // Queue addition to new parent
    if (newParent)
    {
        newParent->AddChild(shared_from_this());
    }
}

void Node::AddChild(std::shared_ptr<Node> node)
{
    LUMEDA_PROFILE;

    if (!node)
        return;

    // Prevent adding self as child
    if (node.get() == this)
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
    m_PendingAdd.push_back(node);
}

void Node::RemoveChild(std::shared_ptr<Node> node)
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
}

void Node::SetEnabled(bool enabled)
{
    LUMEDA_PROFILE;

    // Check if already in this state
    if (m_IsSelfEnabled == enabled)
        return;

    // Queue enabled state change (will be applied in ProcessLifecycle)
    m_PendingEnabledState = enabled;
    m_HasPendingEnabledChange = true;
}