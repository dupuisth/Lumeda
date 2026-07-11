#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Lumeda/Scene/LeafNode.h>
#include <Lumeda/Scene/Node.h>

using namespace Lumeda;

void LeafNode::BakeTransform()
{
  glm::mat4 parentWorld = glm::mat4(1.0f);
  if (m_Parent != nullptr)
  {
    parentWorld = m_Parent->GetWorldMatrix();
  }

  m_RotationEulerAngles = glm::degrees(glm::eulerAngles(m_Rotation));

  // Transform Matrix
  glm::mat4 T = glm::mat4(1.0f);
  T = glm::translate(T, m_Position);

  // Rotation Matrix
  glm::mat4 R = glm::mat4(1.0f);
  // Using Eulers
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
  // R = glm::rotate(R, glm::radians(m_LocalRotationEulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
  // Using Quaterions
  R = glm::toMat4(m_Rotation);

  // Scale Matrix
  glm::mat4 S = glm::mat4(1.0f);
  S = glm::scale(S, m_Scale);

  glm::mat4 localWorld = T * R * S;
  m_WorldMatrix = parentWorld * localWorld;

  m_Right = glm::normalize(glm::vec3(m_WorldMatrix[0]));
  m_Up = glm::normalize(glm::vec3(m_WorldMatrix[1]));
  m_Forward = glm::normalize(glm::vec3(m_WorldMatrix[2]));

  m_TransformDirty = false;
}