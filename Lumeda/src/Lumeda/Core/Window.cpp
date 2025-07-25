#include <Lumeda/Core/Window.h>


#if LUMEDA_PLATFORM_WINDOWS

// Create a Window for Windows
#include <Lumeda/Implementation/GLFW/WindowGLFW.h>
using namespace Lumeda;
std::unique_ptr<Window> Window::Create()
{
	LUMEDA_PROFILE;
	std::unique_ptr<WindowGLFW> window = std::make_unique<WindowGLFW>();
	return window;
}

#else
	#error "Only windows is supported"
#endif

Window::Window() : m_NextCallbackToken(0)
{ 
	LUMEDA_PROFILE;
}

WindowCallbackToken Window::AddResizeCallback(const WindowResizeCallback& callback)
{
	LUMEDA_PROFILE;
	m_NextCallbackToken += 1;
	m_ResizeCallbacks.insert({ m_NextCallbackToken, callback });
	return m_NextCallbackToken;
}

void Window::RemoveResizeCallback(WindowCallbackToken token)
{
	LUMEDA_PROFILE;
	m_ResizeCallbacks.erase(token);
}
