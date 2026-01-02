#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace Lumeda
{
    class RootNode;

    class Node
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
        void SetParent(Node* newParent);
        void AddChild(Node* node, bool immediate = false);
        void RemoveChild(Node* node);

        // Enable/Disable
        void SetEnabled(bool enabled);
        bool IsSelfEnabled() const { LUMEDA_PROFILE; return m_IsSelfEnabled; }
        bool IsEnabled() const { LUMEDA_PROFILE; return m_isEnabled; }

        // Accessors
        Node* GetParent() const { LUMEDA_PROFILE; return m_Parent; }
        const std::vector<Node*>& GetChildren() const { LUMEDA_PROFILE; return m_Children; }
        const std::string& GetName() const { LUMEDA_PROFILE; return m_Name; }
        void SetName(const std::string& name) { LUMEDA_PROFILE; m_Name = name; }
        Transform& GetTransform() { LUMEDA_PROFILE; return m_Transform; }
        RootNode* GetRootNode();

    protected:
        // Virtual methods for derived classes to override
        virtual void OnUpdate();
        virtual void OnRender();
        virtual void OnRenderImGui();
        virtual void OnEnable();
        virtual void OnDisable();
        virtual void OnParentChanged(Node* oldParent, Node* newParent);

    protected:
        std::string m_Name;
        bool m_IsSelfEnabled;
        bool m_isEnabled;
        Transform m_Transform;

        Node* m_Parent;
        std::vector<Node*> m_Children;
    private:
        void ApplyPendingHierarchyChanges();
        void ApplyPendingEnableChanges();

        // Pending operations (deferred until ProcessLifecycle)
        std::vector<Node*> m_PendingAdd;
        std::vector<Node*> m_PendingRemove;
        Node* m_PendingParent;
        bool m_HasPendingParentChange;
        bool m_PendingEnabledState;
        bool m_HasPendingEnabledChange;

        bool m_HasStarted;
    };

}