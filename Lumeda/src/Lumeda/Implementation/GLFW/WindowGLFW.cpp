#include <Lumeda/Implementation/GLFW/WindowGLFW.h>

#include <exception>

using namespace Lumeda;

std::unordered_map<GLFWwindow*, WindowGLFW*> WindowGLFW::s_Windows;

WindowGLFW::WindowGLFW()
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
	glfwSetWindowSizeCallback(m_NativeWindow, GlfwWindowSizeCallback);

	SetVSync(true);

	s_Windows.insert({ m_NativeWindow, this });
}

WindowGLFW::~WindowGLFW()
{
	LUMEDA_PROFILE;

	s_Windows.erase(m_NativeWindow);

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

void WindowGLFW::GlfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	LUMEDA_PROFILE;
	auto iterator = s_Windows.find(window);
	if (iterator != s_Windows.end())
	{
		WindowGLFW* window = iterator->second;
		for (const auto& [token, callback] : window->m_ResizeCallbacks)
		{
			callback(*window, width, height);
		}
	}
	else
	{
		LUMEDA_CORE_WARN("[WindowGLFW] The given window was not found for the size callback ({0})", (void*)window);
	}
}
