#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

namespace Lumeda
{
	class Transform
	{
	public:
		Transform();
		virtual ~Transform();

		void BuildWord();

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotation() { return m_Rotation; }
		const glm::vec3& GetScale() { return m_Scale; }
		const glm::mat4& GetWorld();
		const glm::vec3& GetRight();
		const glm::vec3& GetUp();
		const glm::vec3& GetForward();

		glm::vec3& GetPositionRef() { return m_Position; }
		glm::vec3& GetRotationRef() { return m_Rotation; }
		glm::vec3& GetScaleRef() { return m_Scale; }

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);
		void SetDirty(bool dirty = false) { m_IsDirty = dirty; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::vec3 m_Forward;

		glm::mat4 m_World;

		bool m_IsDirty;
	};
}