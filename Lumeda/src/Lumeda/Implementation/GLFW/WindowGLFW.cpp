#include <Lumeda/Implementation/GLFW/WindowGLFW.h>

#include <exception>

using namespace Lumeda::GLFW;

WindowGLFW::WindowGLFW() : m_IsVSync(true)
{
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
	glfwDestroyWindow(m_NativeWindow);
	m_NativeWindow = nullptr;

	glfwTerminate();
}

void WindowGLFW::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_NativeWindow);
}

int WindowGLFW::GetWidth() const
{
	int width, height;
	glfwGetWindowSize(m_NativeWindow, &width, &height);
	return width;
}

int WindowGLFW::GetHeight() const
{
	int width, height;
	glfwGetWindowSize(m_NativeWindow, &width, &height);
	return height;
}

void WindowGLFW::SetVSync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapBuffers(0);
	}

	m_IsVSync = enabled;
}

bool WindowGLFW::IsVSync() const
{
	return m_IsVSync;
}

bool WindowGLFW::ShouldClose() const
{
	return glfwWindowShouldClose(m_NativeWindow) == GLFW_TRUE;
}

void* WindowGLFW::GetNativeWindow() const
{
	return m_NativeWindow;
}
