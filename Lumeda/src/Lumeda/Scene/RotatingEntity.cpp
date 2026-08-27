#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/RotatingEntity.h>

using namespace Lumeda;

void RotatingEntity::Update()
{
  if (m_Parent != nullptr)
  {
    glm::vec3 rotation = m_Rotation * m_Timer.GetDeltaTime();
    m_Parent->RotateEuler(rotation);
  }
}