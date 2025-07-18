#include <Lumeda/Core/Window.h>


#if LUMEDA_PLATFORM_WINDOWS

// Create a Window for Windows
#include <Lumeda/Implementation/GLFW/WindowGLFW.h>
using namespace Lumeda;
using namespace Lumeda::GLFW;
std::unique_ptr<Window> Window::Create()
{
	std::unique_ptr<WindowGLFW> window = std::make_unique<WindowGLFW>();
	return window;
}

#else
	#error "Only windows is supported"
#endif