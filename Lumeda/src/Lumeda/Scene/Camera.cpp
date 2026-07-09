#include <glm/gtc/matrix_transform.hpp>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Scene/Camera.h>

using namespace Lumeda;

const glm::mat4& Camera::GetProjectionView()
{
  LUMEDA_PROFILE;
  if (m_IsDirty)
  {
    Rebuild();
  }

  return m_ProjectionView;
}

const glm::mat4& Camera::GetProjection()
{
  LUMEDA_PROFILE;
  if (m_IsDirty)
  {
    Rebuild();
  }
  return m_Projection;
}

const glm::mat4& Camera::GetView()
{
  LUMEDA_PROFILE;
  if (m_IsDirty)
  {
    Rebuild();
  }
  return m_View;
}

void Camera::Rebuild()
{
  LUMEDA_PROFILE;

  // Build View
  m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

  // Build Projection
  m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_ZNear, m_ZFar);

  // Build ProjView
  m_ProjectionView = m_Projection * m_View;

  m_IsDirty = false;
}