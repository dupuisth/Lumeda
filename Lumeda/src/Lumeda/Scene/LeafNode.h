#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class Node;
class iUpdateable;
class World;

class LeafNode : public iUpdateable
{
  friend Node;
  friend World;

public:
  LeafNode(const tString& name) :
      iUpdateable(""),
      m_Name(name),
      m_Parent(nullptr),
      m_LocalPosition(0.0f),
      m_LocalRotation(glm::vec3(0.0f)),
      m_LocalRotationEulerAngles(0.0f),
      m_LocalScale(1.0f),
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

  void SetLocalPosition(const glm::vec3& position)
  {
    m_LocalPosition = position;
    SetTransformDirty();
  }
  void Translate(const glm::vec3 movement) { SetLocalPosition(m_LocalPosition + movement); }
  const glm::vec3& GetLocalPosition() { return m_LocalPosition; }

  void SetLocalRotation(const glm::quat& rotation)
  {
    m_LocalRotation = rotation;
    SetTransformDirty();
  }
  void SetLocalRotationEuler(const glm::vec3& rotation)
  {
    m_LocalRotation = glm::quat(glm::radians(rotation));
    SetTransformDirty();
  }
  const glm::quat& GetLocalRotation() { return m_LocalRotation; }

  void SetLocalScale(const glm::vec3& scale)
  {
    m_LocalScale = scale;
    SetTransformDirty();
  }
  const glm::vec3& GetLocalScale() { return m_LocalScale; }

  const glm::mat4& GetWorldMatrix()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_WorldMatrix;
  }

  const glm::vec3& GetPosition()
  {
    if (m_TransformDirty)
    {
      BakeTransform();
    }
    return m_Position;
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
  virtual void ParentIsChanging(Node* parent) { m_Parent = parent; }
  void BakeTransform();
  virtual void SetWorld(World* world) { m_World = world; }

protected:
  tString m_Name;

  World* m_World;

  Node* m_Parent;

  bool m_TransformDirty;

  ///////////////////////////////////////////
  // Local
  ///////////////////////////////////////////
  glm::vec3 m_LocalPosition;
  glm::quat m_LocalRotation;
  glm::vec3 m_LocalRotationEulerAngles;
  glm::vec3 m_LocalScale;

  ///////////////////////////////////////////
  // World
  ///////////////////////////////////////////
  glm::vec3 m_Position;
  glm::vec3 m_Forward;
  glm::vec3 m_Right;
  glm::vec3 m_Up;

  glm::mat4 m_WorldMatrix;
};

} // namespace Lumeda