#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Inputs/Inputs.h>
#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/PlayerControllerEntity.h>

using namespace Lumeda;

void PlayerControllerEntity::Update()
{
  glm::vec3 movement(0.0f);
  float speed = m_Speed;
  if (m_Inputs.IsKeyDown(eKeyboardKey_LeftShift))
  {
    speed *= 2.0f;
  }

  if (m_Inputs.IsKeyDown(eKeyboardKey_W))
  {
    movement += GetForward() * speed;
  }
  if (m_Inputs.IsKeyDown(eKeyboardKey_S))
  {
    movement += -GetForward() * speed;
  }
  if (m_Inputs.IsKeyDown(eKeyboardKey_A))
  {
    movement += -GetRight() * speed;
  }
  if (m_Inputs.IsKeyDown(eKeyboardKey_D))
  {
    movement += GetRight() * speed;
  }

  if (m_Parent != nullptr)
  {
    m_Parent->Translate(movement * m_Timer.GetDeltaTime());
  }

  if (m_Inputs.IsMouseButtonPress(eMouseButton_Middle))
  {
    m_Parent->SetLocalPosition(glm::vec3(0.0f));
  }

  if (m_Inputs.IsMouseButtonDown(eMouseButton_Right))
  {
    m_Inputs.SetCursorMode(eCursorMode_Gameplay);
    glm::vec2 mouseDelta = m_Inputs.GetMouseDelta();
    glm::vec3 mouseMovement = glm::vec3(mouseDelta.y, -mouseDelta.x, 0.0f) * m_Sensitivity;
    m_Parent->RotateEuler(mouseMovement);
  }
  else
  {
    m_Inputs.SetCursorMode(eCursorMode_Normal);
  }
}