#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class Node;

class LeafNode
{
  friend Node;

public:
  LeafNode(const tString& name) :
      m_Name(name),
      m_Parent(nullptr),
      m_Position(0.0f),
      m_Rotation(glm::vec3(0.0f)),
      m_RotationEulerAngles(0.0f),
      m_Scale(1.0f),
      m_TransformDirty(true)
  {
  }
  virtual ~LeafNode() = default;

  ///////////////////////////////////////////
  // Parent
  ///////////////////////////////////////////
  Node* GetParent() { return m_Parent; }

  ///////////////////////////////////////////
  // Name
  ///////////////////////////////////////////
  const tString& GetName() { return m_Name; }
  void SetName(const tString& name) { m_Name = name; }

  ///////////////////////////////////////////
  // Transform
  ///////////////////////////////////////////
  virtual void SetTransformDirty() { m_TransformDirty = true; }

  void SetPosition(const glm::vec3& position)
  {
    m_Position = position;
    SetTransformDirty();
  }
  const glm::vec3& GetPosition() { return m_Position; }

  void SetRotation(const glm::quat& rotation)
  {
    m_Rotation = rotation;
    SetTransformDirty();
  }
  void SetRotationEuler(const glm::vec3& rotation)
  {
    m_Rotation = glm::quat(glm::radians(rotation));
    SetTransformDirty();
  }
  const glm::quat& GetRotation() { return m_Rotation; }

  void SetScale(const glm::vec3& scale)
  {
    m_Scale = scale;
    SetTransformDirty();
  }
  const glm::vec3& GetScale() { return m_Scale; }

  const glm::mat4& GetWorldMatrix()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_WorldMatrix;
  }

  const glm::vec3& GetRight()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_Right;
  }

  const glm::vec3& GetForward()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_Forward;
  }

  const glm::vec3& GetUp()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_Up;
  }

protected:
  void ParentIsChanging(Node* parent) { m_Parent = parent; }
  void BakeTransform();

protected:
  tString m_Name;

  Node* m_Parent;

  glm::vec3 m_Position;
  glm::quat m_Rotation;
  glm::vec3 m_RotationEulerAngles;
  glm::vec3 m_Scale;
  bool m_TransformDirty;

  glm::vec3 m_Forward;
  glm::vec3 m_Right;
  glm::vec3 m_Up;

  glm::mat4 m_WorldMatrix;
};

} // namespace Lumeda