#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Inputs/Inputs.h>
#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/PlayerControllerEntity.h>

using namespace Lumeda;

void PlayerControllerEntity::Update()
{
  glm::vec3 movement(0.0f);

  if (m_Inputs.isKeyDown(eKeyboardKey_W))
  {
    movement += GetForward() * m_Speed;
  }
  if (m_Inputs.isKeyDown(eKeyboardKey_S))
  {
    movement += -GetForward() * m_Speed;
  }
  if (m_Inputs.isKeyDown(eKeyboardKey_A))
  {
    movement += -GetRight() * m_Speed;
  }
  if (m_Inputs.isKeyDown(eKeyboardKey_D))
  {
    movement += GetRight() * m_Speed;
  }

  if (m_Parent != nullptr)
  {
    m_Parent->Translate(movement * m_Timer.GetDeltaTime());
  }

  if (m_Inputs.isMouseButtonPress(eMouseButton_Middle))
  {
    m_Parent->SetLocalPosition(glm::vec3(0.0f));
  }
}