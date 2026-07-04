// #pragma once

// #include <glm/glm.hpp>
// #include <glm/gtc/quaternion.hpp>
// #include <Lumeda/Core/Base.h>

// namespace Lumeda
// {

// class Transform
// {
// public:
//   Transform();
//   virtual ~Transform();

//   void Bake();

//   const glm::vec3& GetPosition();
//   const glm::quat& GetRotation();
//   const glm::vec3& GetRotationEulerAngles();
//   const glm::vec3& GetScale();

//   const glm::vec3& GetLocalPosition();
//   const glm::vec3& GetLocalRotationEulerAngles();
//   const glm::quat& GetLocalRotation();
//   const glm::vec3& GetLocalScale();

//   /// @brief Using this is insecure, you must always set the transform dirty after modifications
//   glm::vec3& GetLocalPositionRef();
//   /// @brief Using this is insecure, you must always set the transform dirty after modifications
//   glm::vec3& GetLocalScaleRef();

//   const glm::mat4& GetWorld();
//   const glm::vec3& GetRight();
//   const glm::vec3& GetUp();
//   const glm::vec3& GetForward();

//   void SetLocalPosition(const glm::vec3& position);
//   void SetLocalRotation(const glm::quat& rotation);
//   void SetLocalRotationEulerAngles(const glm::vec3& rotation);
//   void SetLocalScale(const glm::vec3& scale);

//   void Rotate(const glm::quat& quat);
//   void Rotate(const glm::vec3& euler);

//   void SetDirty(bool dirty = true);

// private:
//   glm::vec3 m_LocalPosition;
//   glm::vec3 m_LocalRotationEulerAngles;
//   glm::quat m_LocalRotation;
//   glm::vec3 m_LocalScale;

//   glm::vec3 m_Position;
//   glm::vec3 m_RotationEulerAngles;
//   glm::quat m_Rotation;
//   glm::vec3 m_Scale;

//   glm::vec3 m_Right;
//   glm::vec3 m_Up;
//   glm::vec3 m_Forward;

//   glm::mat4 m_LocalWorld;
//   glm::mat4 m_World;

//   bool m_IsDirty;

//   // Node* m_AttachedTo;
// };
// } // namespace Lumeda