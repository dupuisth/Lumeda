#include <Lumeda/Implementation/GLFW/WindowGLFW.h>

#include <exception>

using namespace Lumeda::GLFW;

WindowGLFW::WindowGLFW() : m_IsVSync(true)
{
	LUMEDA_PROFILE;
	if (glfwInit() != GLFW_TRUE) 
	{
		LUMEDA_CORE_ERROR("Failed to initialized GLFW");
		throw std::runtime_error("Failed to initialize GLFW");
	}

	m_NativeWindow = glfwCreateWindow(500, 500, "Lumeda", nullptr, nullptr);
	if (m_NativeWindow == nullptr)
	{
		LUMEDA_CORE_ERROR("Failed to create GLFW window");
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(m_NativeWindow);

	SetVSync(true);
}

WindowGLFW::~WindowGLFW()
{
	LUMEDA_PROFILE;
	glfwDestroyWindow(m_NativeWindow);
	m_NativeWindow = nullptr;

	glfwTerminate();
}

void WindowGLFW::Update()
{
	LUMEDA_PROFILE;
	glfwPollEvents();
	glfwSwapBuffers(m_NativeWindow);
}

int WindowGLFW::GetWidth() const
{
	LUMEDA_PROFILE;
	int width, height;
	glfwGetWindowSize(m_NativeWindow, &width, &height);
	return width;
}

int WindowGLFW::GetHeight() const
{
	LUMEDA_PROFILE;
	int width, height;
	glfwGetWindowSize(m_NativeWindow, &width, &height);
	return height;
}

const glm::ivec2& WindowGLFW::GetSize() const
{
	LUMEDA_PROFILE;
	int width, height;
	glfwGetWindowSize(m_NativeWindow, &width, &height);
	return glm::ivec2(width, height);
}

float WindowGLFW::GetAspectRatio() const
{
	LUMEDA_PROFILE;
	const glm::ivec2& size = GetSize();
	return (float)size.x / (float)size.y;
}

void WindowGLFW::SetVSync(bool enabled)
{
	LUMEDA_PROFILE;
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}

	m_IsVSync = enabled;
}

bool WindowGLFW::IsVSync() const
{
	LUMEDA_PROFILE;
	return m_IsVSync;
}

bool WindowGLFW::ShouldClose() const
{
	LUMEDA_PROFILE;
	return glfwWindowShouldClose(m_NativeWindow) == GLFW_TRUE;
}

void* WindowGLFW::GetNativeWindow() const
{
	LUMEDA_PROFILE;
	return m_NativeWindow;
}
