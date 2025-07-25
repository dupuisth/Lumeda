#include <Lumeda/Core/Transform.h>

#include <Lumeda/Renderer/Camera.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Lumeda;

Transform::Transform()
	: m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f), m_World(1.0f), m_Right(0.0f), m_Up(0.0f), m_Forward(0.0f), m_IsDirty(true)
{
	LUMEDA_PROFILE;
}

Transform::~Transform()
{
	LUMEDA_PROFILE;
}

void Transform::BuildWorld()
{
	LUMEDA_PROFILE;
	m_World = glm::mat4(1.0f);
	m_World = glm::translate(m_World, m_Position);
	m_World = glm::rotate(m_World, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_World = glm::rotate(m_World, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_World = glm::rotate(m_World, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_World = glm::scale(m_World, m_Scale);

	glm::mat4 inverse = glm::inverse(m_World);
	m_Right = -glm::normalize(glm::vec3(inverse[0]));
	m_Up = glm::normalize(glm::vec3(inverse[1]));
	m_Forward = glm::normalize(glm::vec3(inverse[2]));

	m_IsDirty = false;
}

const glm::mat4& Lumeda::Transform::GetWorld()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		BuildWorld();
	}

	return m_World;
}

const glm::vec3& Transform::GetRight()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		BuildWorld();
	}

	return m_Right;
}

const glm::vec3& Transform::GetUp()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		BuildWorld();
	}

	return m_Up;
}

const glm::vec3& Transform::GetForward()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		BuildWorld();
	}

	return m_Forward;
}

void Transform::SetPosition(const glm::vec3& position)
{
	LUMEDA_PROFILE;
	m_Position = position;
	m_IsDirty = true;
}

void Transform::SetRotation(const glm::vec3& rotation)
{
	LUMEDA_PROFILE;
	m_Rotation = rotation;
	m_IsDirty = true;
}

void Transform::SetScale(const glm::vec3& scale)
{
	LUMEDA_PROFILE;
	m_Scale = scale;
	m_IsDirty = true;
}



