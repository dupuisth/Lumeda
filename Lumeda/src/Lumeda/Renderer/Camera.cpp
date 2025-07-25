#include <Lumeda/Renderer/Camera.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Window.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace Lumeda;

Camera* s_Instance = nullptr;

Camera::Camera() : m_ProjectionView(1.0f), m_IsDirty(true)
{
	LUMEDA_PROFILE;
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
}

const glm::mat4& Camera::GetProjectionView()
{
	LUMEDA_PROFILE;
	if (m_IsDirty)
	{
		glm::mat4 projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_ZNear, m_ZFar);
		glm::mat4 view = glm::lookAt(m_Transform.GetPositionRef(), m_Transform.GetPosition() + m_Transform.GetForward(), m_Transform.GetUp());
		m_ProjectionView = projection * view;
		m_IsDirty = false;
	}

	return m_ProjectionView;
}

Camera& Camera::GetCurrent()
{
	LUMEDA_PROFILE;
	return *s_Instance;
}

void Camera::SetCurrent(Camera& camera)
{
	LUMEDA_PROFILE;
	s_Instance = &camera;
}

void Camera::SetCurrent()
{
	LUMEDA_PROFILE;
	s_Instance = nullptr;
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