#include <Lumeda/Core/Window.h>

using namespace Lumeda;

#if LUMEDA_PLATFORM_WINDOWS

// Create a Window for Windows
std::unique_ptr<Window> Window::Create()
{
	// TODO ...
	return nullptr;
}

#else
	#error "Only windows is supported"
#endif