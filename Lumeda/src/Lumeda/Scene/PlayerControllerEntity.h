#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{
class iInputs;
class Timer;

class PlayerControllerEntity : public Entity
{
public:
  PlayerControllerEntity(const tString& name, iInputs& inputs, Timer& timer) : Entity(name), m_Inputs(inputs), m_Timer(timer) {}
  ~PlayerControllerEntity() = default;

  void Update() override;

  void SetSpeed(float speed) { m_Speed = speed; }

protected:
  iInputs& m_Inputs;
  Timer& m_Timer;

  float m_Speed = 1.0f;
};
} // namespace Lumeda