#include <Lumeda/Renderer/Camera.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Window.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Lumeda;

static Camera* s_Instance = nullptr;

Camera::Camera(Transform* transform)
	: m_ProjectionView(1.0f), m_IsDirty(true), m_Transform(transform), m_HasTransformOwnership(false)
{
	LUMEDA_PROFILE;
	if (transform == nullptr)
	{
		m_Transform = LUMEDA_NEW(Transform);
		m_HasTransformOwnership = true;
	}

	SetFOV(60.0f);
	SetZNear(0.01f);
	SetZFar(1000.0f);
	SetAspectRatio(Engine::Get().GetWindow().GetAspectRatio());

	m_WindowResizeCallbackToken = Engine::Get().GetWindow().AddResizeCallback(
		std::bind(&Camera::OnWindowResized, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);
}

Camera::~Camera()
{
	LUMEDA_PROFILE;
	Engine::Get().GetWindow().RemoveResizeCallback(m_WindowResizeCallbackToken);

	if (m_HasTransformOwnership)
	{
		LUMEDA_FREE(m_Transform);
	}

	if (s_Instance == this)
	{
		s_Instance = nullptr;
	}
}

const glm::mat4& Camera::GetProjectionView()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		Rebuild();
	}

	return m_ProjectionView;
}

const glm::mat4& Camera::GetProjection()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		Rebuild();
	}
	return m_Projection;
}

const glm::mat4& Camera::GetView()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		Rebuild();
	}
	return m_View;
}

void Camera::Rebuild()
{
	LUMEDA_PROFILE;		

	// Build View
	glm::vec3 position = m_Transform->GetPosition();
	position.x = position.x;
	m_View = glm::lookAt(position, m_Transform->GetPosition() + m_Transform->GetForward(), m_Transform->GetUp());
	
	// Build Projection
	m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_ZNear, m_ZFar);
	
	// Build ProjView
	m_ProjectionView = m_Projection * m_View;
	
	m_IsDirty = false;
}

Camera* Camera::GetCurrent()
{
	LUMEDA_PROFILE;
	return s_Instance;
}

void Camera::SetCurrent(Camera* camera)
{
	LUMEDA_PROFILE;
	s_Instance = camera;
}

void Camera::SetCurrent()
{
	LUMEDA_PROFILE;
	s_Instance = this;
}

void Camera::SetAspectRatio(float aspectRatio)
{
	LUMEDA_PROFILE;
	m_IsDirty = true;
	m_AspectRatio = aspectRatio;
}

void Camera::SetFOV(float fov)
{
	LUMEDA_PROFILE;
	m_IsDirty = true;
	m_FOV = fov;
}

void Camera::SetZNear(float zNear)
{
	LUMEDA_PROFILE;
	m_IsDirty = true;
	m_ZNear = zNear;
}

void Camera::SetZFar(float zFar)
{
	LUMEDA_PROFILE;
	m_IsDirty = true;
	m_ZFar = zFar;
}

void Camera::OnWindowResized(Window& window, int width, int height)
{
	LUMEDA_PROFILE;
	SetAspectRatio((float)width / (float)height);
}