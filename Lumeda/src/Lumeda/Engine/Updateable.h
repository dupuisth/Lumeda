#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

class IUpdateable
{
  public:
    IUpdateable(const std::string& name) : m_Name(name) {}

    virtual void OnStart() {}

    virtual void OnPreDraw() {}
    virtual void OnDraw() {}
    virtual void OnPostDraw() {}

    virtual void PreUpdate() {}
    virtual void Update() {}
    virtual void PostUpdate() {}

    virtual void Reset() {}

    virtual void HandleMessage(eUpdateableMessage message)
    {
        switch (message)
        {
        case eUpdateableMessage_OnStart:
            OnStart();
            break;
        case eUpdateableMessage_OnPreDraw:
            OnPreDraw();
            break;
        case eUpdateableMessage_OnDraw:
            OnDraw();
            break;
        case eUpdateableMessage_OnPostDraw:
            OnPostDraw();
            break;
        case eUpdateableMessage_PreUpdate:
            PreUpdate();
            break;
        case eUpdateableMessage_Update:
            Update();
            break;
        case eUpdateableMessage_PostUpdate:
            PostUpdate();
            break;
        case eUpdateableMessage_Reset:
            Reset();
            break;
        default:
            break;
        }
    }

    const std::string& GetName() { return m_Name; }

  private:
    std::string m_Name;
};

} // namespace Lumeda