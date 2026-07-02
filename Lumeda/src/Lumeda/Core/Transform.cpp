#include <Lumeda/Core/Transform.h>
#include <Lumeda/Renderer/Camera.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Lumeda;

#define BAKE_IF_REQUIRED                                                                                                                             \
  if (m_IsDirty)                                                                                                                                     \
  Bake()

Transform::Transform() :
    m_LocalPosition(0.0f),
    m_LocalRotationEulerAngles(0.0f),
    m_LocalScale(1.0f),
    m_LocalRotation(glm::vec3(0.0f)),
    m_Position(0.0f),
    m_RotationEulerAngles(0.0f),
    m_Scale(1.0f),
    m_Rotation(glm::vec3(0.0f)),
    m_World(1.0f),
    m_Right(0.0f),
    m_Up(0.0f),
    m_Forward(0.0f),
    m_IsDirty(true)
// m_AttachedTo(attachedTo)
{
  LUMEDA_PROFILE;
}

Transform::~Transform()
{
  LUMEDA_PROFILE;
}

void Transform::Bake()
{
  LUMEDA_PROFILE;

  glm::mat4 parentWorld = glm::mat4(1.0f);
  //   if (m_AttachedTo != nullptr && m_AttachedTo->GetParent() != nullptr)
  //   {
  //     parentWorld = m_AttachedTo->GetParent()->GetTransform().GetWorld();
  //   }

  m_LocalRotationEulerAngles = glm::degrees(glm::eulerAngles(m_LocalRotation));

  // Transform Matrix
  glm::mat4 T = glm::mat4(1.0f);
  T = glm::translate(T, m_LocalPosition);

  // Rotation Matrix
  glm::mat4 R = glm::mat4(1.0f);
  // Using Eulers
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
  // Using Quaterions
  R = glm::toMat4(m_LocalRotation);

  // Scale Matrix
  glm::mat4 S = glm::mat4(1.0f);
  S = glm::scale(S, m_LocalScale);

  m_LocalWorld = T * R * S;
  m_World = parentWorld * m_LocalWorld;

  m_Right = glm::normalize(glm::vec3(m_World[0]));
  m_Up = glm::normalize(glm::vec3(m_World[1]));
  m_Forward = glm::normalize(glm::vec3(m_World[2]));

  // Bake global position, rotation and scale
  //   if (m_AttachedTo != nullptr && m_AttachedTo->GetParent() != nullptr)
  //   {
  //     // Attached to a parent so the globals depends on it
  //     m_Position = glm::vec3(m_World[3]);

  //     glm::mat3 rotMat = glm::mat3(m_World);
  //     rotMat[0] = glm::normalize(rotMat[0]);
  //     rotMat[1] = glm::normalize(rotMat[1]);
  //     rotMat[2] = glm::normalize(rotMat[2]);
  //     m_Rotation = glm::quat_cast(rotMat);
  //     m_RotationEulerAngles = glm::degrees(glm::eulerAngles(m_Rotation));

  //     m_Scale.x = glm::length(m_World[0]);
  //     m_Scale.y = glm::length(m_World[1]);
  //     m_Scale.z = glm::length(m_World[2]);
  //   }
  if (false)
  {
  }
  else
  {
    // No parent so the locals are globals
    m_Position = m_LocalPosition;
    m_Rotation = m_LocalRotation;
    m_RotationEulerAngles = m_LocalRotationEulerAngles;
    m_Scale = m_LocalScale;
  }

  SetDirty(false);
}

const glm::vec3& Transform::GetPosition()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;
  return m_Position;
}

const glm::quat& Transform::GetRotation()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;
  return m_Rotation;
}

const glm::vec3& Transform::GetRotationEulerAngles()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;
  return m_RotationEulerAngles;
}

const glm::vec3& Transform::GetScale()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;
  return m_Scale;
}

const glm::vec3& Transform::GetLocalPosition()
{
  LUMEDA_PROFILE;
  return m_LocalPosition;
}

const glm::vec3& Transform::GetLocalRotationEulerAngles()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;
  return m_LocalRotationEulerAngles;
}

const glm::quat& Transform::GetLocalRotation()
{
  LUMEDA_PROFILE;
  return m_LocalRotation;
}

const glm::vec3& Transform::GetLocalScale()
{
  LUMEDA_PROFILE;
  return m_LocalScale;
}

glm::vec3& Transform::GetLocalPositionRef()
{
  LUMEDA_PROFILE;
  return m_LocalPosition;
}

glm::vec3& Transform::GetLocalScaleRef()
{
  LUMEDA_PROFILE;
  return m_LocalScale;
}

const glm::mat4& Transform::GetWorld()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;

  return m_World;
}

const glm::vec3& Transform::GetRight()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;

  return m_Right;
}

const glm::vec3& Transform::GetUp()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;

  return m_Up;
}

const glm::vec3& Transform::GetForward()
{
  LUMEDA_PROFILE;
  BAKE_IF_REQUIRED;

  return m_Forward;
}

void Transform::SetLocalPosition(const glm::vec3& position)
{
  LUMEDA_PROFILE;
  m_LocalPosition = position;
  SetDirty();
}

void Transform::SetLocalRotation(const glm::quat& rotation)
{
  LUMEDA_PROFILE;
  m_LocalRotation = rotation;
  SetDirty();
}

void Transform::SetLocalRotationEulerAngles(const glm::vec3& rotation)
{
  LUMEDA_PROFILE;
  m_LocalRotation = glm::quat(glm::radians((rotation)));
  SetDirty();
}

void Transform::SetLocalScale(const glm::vec3& scale)
{
  LUMEDA_PROFILE;
  m_LocalScale = scale;
  SetDirty();
}

void Transform::SetDirty(bool dirty)
{
  LUMEDA_PROFILE;
  m_IsDirty = dirty;
  //   if (dirty && m_AttachedTo != nullptr)
  //   {
  //     for (auto& child : m_AttachedTo->GetChildren())
  //     {
  //       child->GetTransform().SetDirty(true);
  //     }
  //   }
}

void Transform::Rotate(const glm::quat& quat)
{
  LUMEDA_PROFILE;
  m_LocalRotation *= quat;
  SetDirty();
}

void Transform::Rotate(const glm::vec3& eulerDeg)
{
  LUMEDA_PROFILE;
  glm::quat quat = glm::quat(glm::radians(eulerDeg));
  Rotate(quat);
  SetDirty();
}