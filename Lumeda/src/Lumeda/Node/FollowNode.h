#pragma once

#include <Lumeda/Auto/PID.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Node/Node.h>

namespace Lumeda
{
class FollowNode : public Node
{
  public:
    FollowNode();
    virtual ~FollowNode();

    void SetTarget(Node* node);
    Node* GetTarget();

  protected:
    void OnUpdate() override;
    void OnRenderImGui() override;

  private:
    Node* m_Target;
    PID m_Pid;

    PIDMemory m_Memories[3];
};
} // namespace Lumeda