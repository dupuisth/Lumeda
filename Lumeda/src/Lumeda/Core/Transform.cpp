#include <Lumeda/Core/Transform.h>

#include <Lumeda/Renderer/Camera.h>
#include <Lumeda/Node/Node.h>

#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

using namespace Lumeda;

#define BAKE_IF_REQUIRED if(m_IsDirty) Bake()

Transform::Transform(Node* attachedTo)
	:
	m_LocalPosition(0.0f), m_LocalRotation(0.0f), m_LocalScale(1.0f),
	m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f),
	m_World(1.0f),
	m_Right(0.0f), m_Up(0.0f), m_Forward(0.0f),
	m_IsDirty(true), m_AttachedTo(attachedTo)
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
	if (m_AttachedTo != nullptr && m_AttachedTo->GetParent() != nullptr)
	{
		parentWorld = m_AttachedTo->GetParent()->GetTransform().GetWorld();
	}

	m_World = glm::mat4(1.0f);
	m_World = glm::translate(m_World, m_LocalPosition);
	m_World = glm::rotate(m_World, glm::radians(m_LocalRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_World = glm::rotate(m_World, glm::radians(m_LocalRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_World = glm::rotate(m_World, glm::radians(m_LocalRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_World = glm::scale(m_World, m_LocalScale);
	m_World = parentWorld * m_World;

	glm::mat4 inverse = glm::inverse(m_World);
	m_Right = glm::normalize(glm::vec3(inverse[0]));
	m_Up = glm::normalize(glm::vec3(inverse[1]));
	m_Forward = glm::normalize(glm::vec3(inverse[2]));

	// m_Right = glm::normalize(glm::vec3(m_World[0])); 
	// m_Up = glm::normalize(glm::vec3(m_World[1]));
	// m_Forward = glm::normalize(glm::vec3(m_World[2]));

	// Bake global position, rotation and scale
	if (m_AttachedTo != nullptr && m_AttachedTo->GetParent() != nullptr)
	{
		// Attached to a parent so the globals depends on it
		m_Position = glm::vec3(m_World[3]);

		glm::quat q = glm::quat_cast(m_World);
		m_Rotation = glm::degrees(glm::eulerAngles(q));

		m_Scale = m_AttachedTo->GetParent()->GetTransform().GetScale() * m_LocalScale;
	}
	else
	{
		// No parent so the locals are globals
		m_Position = m_LocalPosition;
		m_Rotation = m_LocalRotation;
		m_Scale = m_LocalScale;
	}

	SetDirty(false);
}

const glm::vec3& Lumeda::Transform::GetPosition()
{
	LUMEDA_PROFILE;
	BAKE_IF_REQUIRED;
	return m_Position;
}

const glm::vec3& Lumeda::Transform::GetRotation()
{
	LUMEDA_PROFILE;
	BAKE_IF_REQUIRED;
	return m_Rotation;
}

const glm::vec3& Lumeda::Transform::GetScale()
{
	LUMEDA_PROFILE;
	BAKE_IF_REQUIRED;
	return m_Scale;
}

const glm::vec3& Lumeda::Transform::GetLocalPosition()
{
	LUMEDA_PROFILE;
	return m_LocalPosition;
}

const glm::vec3& Lumeda::Transform::GetLocalRotation()
{
	LUMEDA_PROFILE;
	return m_LocalRotation;
}

const glm::vec3& Lumeda::Transform::GetLocalScale()
{
	LUMEDA_PROFILE;
	return m_LocalScale;
}

glm::vec3& Lumeda::Transform::GetLocalPositionRef()
{
	LUMEDA_PROFILE;
	return m_LocalPosition;
}

glm::vec3& Lumeda::Transform::GetLocalRotationRef()
{
	LUMEDA_PROFILE;
	return m_LocalRotation;
}

glm::vec3& Lumeda::Transform::GetLocalScaleRef()
{
	LUMEDA_PROFILE;
	return m_LocalScale;
}

const glm::mat4& Lumeda::Transform::GetWorld()
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

void Transform::SetPosition(const glm::vec3& position)
{
	LUMEDA_PROFILE;
	m_Position = position;
	SetDirty();
}

void Transform::SetRotation(const glm::vec3& rotation)
{
	LUMEDA_PROFILE;
	m_Rotation = rotation;
	SetDirty();
}

void Transform::SetScale(const glm::vec3& scale)
{
	LUMEDA_PROFILE;
	m_Scale = scale;
	SetDirty();
}

void Transform::SetLocalPosition(const glm::vec3& position)
{
	LUMEDA_PROFILE;
	m_LocalPosition = position;
	SetDirty();
}

void Transform::SetLocalRotation(const glm::vec3& rotation)
{
	LUMEDA_PROFILE;
	m_LocalRotation = rotation;
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
	if (dirty && m_AttachedTo != nullptr)
	{
		for (auto& child : m_AttachedTo->GetChildren())
		{
			child->GetTransform().SetDirty();
		}
	}
}



