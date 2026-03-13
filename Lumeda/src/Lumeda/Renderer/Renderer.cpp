#include <Lumeda/Renderer/Renderer.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLAD
#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>
Renderer* Renderer::Create()
{
	RendererOpenGL* renderer = LUMEDA_NEW(RendererOpenGL);
	return renderer;
}
#else
#error "Current platform not supported!"
#endif