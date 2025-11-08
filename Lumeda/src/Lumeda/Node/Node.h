#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace Lumeda
{

class Node : public std::enable_shared_from_this<Node>
{
public:
    Node();
    virtual ~Node();

    // Lifecycle management, always executed
    void ProcessLifecycle();

    // Game logicn only runs when enabled
    void Update();
    void Render();
    void RenderImGui();

    // Hierarchy management
    void SetParent(std::shared_ptr<Node> newParent);
    void AddChild(std::shared_ptr<Node> node);
    void RemoveChild(std::shared_ptr<Node> node);

    // Enable/Disable
    void SetEnabled(bool enabled);
    bool IsSelfEnabled() const { return m_IsSelfEnabled; }
    bool IsEnabled() const { return m_isEnabled; }

    // Accessors
    Node* GetParent() const { return m_Parent; }
    const std::vector<std::shared_ptr<Node>>& GetChildren() const { return m_Children; }
    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }
    Transform& GetTransform() { return m_Transform; }

protected:
    // Virtual methods for derived classes to override
    virtual void OnUpdate() {}
    virtual void OnRender() {}
    virtual void OnRenderImGui() {}
    virtual void OnEnable() {}
    virtual void OnDisable() {}
    virtual void OnParentChanged(Node* oldParent, Node* newParent) {}

protected:
    std::string m_Name;
    bool m_IsSelfEnabled;
    bool m_isEnabled;
    Transform m_Transform;
        
    Node* m_Parent;
    std::vector<std::shared_ptr<Node>> m_Children;
private:
    void ApplyPendingHierarchyChanges();
    void ApplyPendingEnableChanges();

    // Pending operations (deferred until ProcessLifecycle)
    std::vector<std::shared_ptr<Node>> m_PendingAdd;
    std::vector<std::shared_ptr<Node>> m_PendingRemove;
    Node* m_PendingParent;
    bool m_HasPendingParentChange;
    bool m_PendingEnabledState;
    bool m_HasPendingEnabledChange;
};

}