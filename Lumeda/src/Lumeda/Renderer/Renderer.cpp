#include <Lumeda/Renderer/Renderer.h>

using namespace Lumeda;

#if LUMEDA_PLATFORM_WINDOWS

#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>
std::unique_ptr<Renderer> Renderer::Create()
{
	std::unique_ptr<RendererOpenGL> renderer = std::make_unique<RendererOpenGL>();
	return renderer;
}
#elif LUMEDA_PLATFORM_LINUX
#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>
std::unique_ptr<Renderer> Renderer::Create()
{
	std::unique_ptr<RendererOpenGL> renderer = std::make_unique<RendererOpenGL>();
	return renderer;
}
#else
	#error "Current platform not supported!"
#endif