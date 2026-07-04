#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>

namespace Lumeda
{
class Camera
{
public:
  Camera() {}
  virtual ~Camera() = default;

  const glm::mat4& GetProjectionView();
  const glm::mat4& GetProjection();
  const glm::mat4& GetView();

  float GetAspectRatio() { return m_AspectRatio; }
  float GetFOV() { return m_FOV; }
  float GetZNear() { return m_ZNear; }
  float GetZFar() { return m_ZFar; }

  void SetTransform(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
  {
    m_Position = position;
    m_Forward = forward;
    m_Up = up;
    m_IsDirty = true;
  }
  void SetAspectRatio(float aspectRatio)
  {
    m_AspectRatio = aspectRatio;
    m_IsDirty = true;
  }
  void SetFOV(float fov)
  {
    m_FOV = fov;
    m_IsDirty = true;
  }
  void SetZNear(float zNear)
  {
    m_ZNear = zNear;
    m_IsDirty = true;
  }
  void SetZFar(float zFar)
  {
    m_ZFar = zFar;
    m_IsDirty = true;
  }

protected:
  void Rebuild();

private:
  glm::vec3 m_Position;
  glm::vec3 m_Forward;
  glm::vec3 m_Up;

  float m_AspectRatio;
  float m_FOV;
  float m_ZNear;
  float m_ZFar;

  glm::mat4 m_ProjectionView;
  glm::mat4 m_Projection;
  glm::mat4 m_View;

  bool m_IsDirty;
};
} // namespace Lumeda