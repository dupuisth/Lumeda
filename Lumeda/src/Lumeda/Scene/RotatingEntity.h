#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Scene/Camera.h>
#include <Lumeda/Scene/Entity.h>

namespace Lumeda
{
class RotatingEntity : public Entity
{
public:
  RotatingEntity(const tString& name, Timer& timer) : Entity(name), m_Timer(timer) {}
  ~RotatingEntity() = default;

  void Update() override;

  void SetRotating(const glm::vec3& rotation) { m_Rotation = rotation; }
  const glm::vec3& GetRotating() { return m_Rotation; }

  // For ImGui
  glm::vec3& GetRotatingRef() { return m_Rotation; }

  tString GetTypeId() const { return TypeId; }

public:
  inline static const tString TypeId = "RotatingEntity";

private:
  Timer& m_Timer;

  glm::vec3 m_Rotation = glm::vec3(0.0f);
};
} // namespace Lumeda