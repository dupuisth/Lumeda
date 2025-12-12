#include <Lumeda/Core/InputsLayer.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLFW
#include <Lumeda/Implementation/GLFW/InputsLayerGLFW.h>
using namespace Lumeda;
std::unique_ptr<InputsLayer> InputsLayer::Create()
{
	LUMEDA_PROFILE;
	std::unique_ptr<InputsLayerGLFW> window = std::make_unique<InputsLayerGLFW>();
	return window;
}
#else
#error "Current platform not supported!"
#endif