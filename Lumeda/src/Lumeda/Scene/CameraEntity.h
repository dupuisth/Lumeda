#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Scene/Camera.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{
class CameraEntity : public Entity
{
public:
  CameraEntity(const tString& name) : Entity(name) {}
  ~CameraEntity() = default;

  Camera& GetCamera() { return m_Camera; }

  void SetTransformDirty()
  {
    Entity::SetTransformDirty();
    BakeTransform();
    m_Camera.SetTransform(m_Position, m_Forward, m_Up);
  }

private:
  Camera m_Camera;
};
} // namespace Lumeda