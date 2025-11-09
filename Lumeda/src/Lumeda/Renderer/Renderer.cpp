#include <Lumeda/Renderer/Renderer.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLAD
#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>
std::unique_ptr<Renderer> Renderer::Create()
{
	std::unique_ptr<RendererOpenGL> renderer = std::make_unique<RendererOpenGL>();
	return renderer;
}
#else
	#error "Current platform not supported!"
#endif