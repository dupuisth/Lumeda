#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

namespace Lumeda
{
	class Node;

	class Transform
	{
	public:
		Transform(Node* attachedTo = nullptr);
		virtual ~Transform();

		void Bake();

		const glm::vec3& GetPosition();
		const glm::vec3& GetRotation();
		const glm::vec3& GetScale();

		const glm::vec3& GetLocalPosition();
		const glm::vec3& GetLocalRotation();
		const glm::vec3& GetLocalScale();

		/// @brief Using this is insecure, you must always set the transform dirty after modifications
		glm::vec3& GetLocalPositionRef();
		/// @brief Using this is insecure, you must always set the transform dirty after modifications
		glm::vec3& GetLocalRotationRef();
		/// @brief Using this is insecure, you must always set the transform dirty after modifications
		glm::vec3& GetLocalScaleRef();

		const glm::mat4& GetWorld();
		const glm::vec3& GetRight();
		const glm::vec3& GetUp();
		const glm::vec3& GetForward();

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

		void SetLocalPosition(const glm::vec3& position);
		void SetLocalRotation(const glm::vec3& rotation);
		void SetLocalScale(const glm::vec3& scale);

		void SetDirty(bool dirty = true);

	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_LocalRotation;
		glm::vec3 m_LocalScale;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::vec3 m_Forward;

		glm::mat4 m_World;

		bool m_IsDirty;

		Node* m_AttachedTo;
	};
}