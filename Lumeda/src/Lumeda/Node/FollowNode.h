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
    PID& GetPid();

  protected:
    void OnUpdate() override;
    void OnRender() override;
    void OnRenderImGui() override;

  private:
    Node* m_Target;
    PID m_Pid;

    PIDMemory m_Memories[3];
    PIDOutput m_Outputs[3];

    glm::vec3 m_ConstantPerturbation;
    float m_PerturbationIntensity;

    static const int POSITION_MEMORY_SAMPLES = 64;
    const float POSITION_SAMPLE_TIME = 0.05f;
    glm::vec3 m_PositionsMemory[POSITION_MEMORY_SAMPLES];
    int m_CurrentPositionMemory;
    float m_PositionLastSampleTime;
};
} // namespace Lumeda