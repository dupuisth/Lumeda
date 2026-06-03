#include <Lumeda/Core/InputsLayer.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLFW
#include <Lumeda/Implementation/GLFW/InputsLayerGLFW.h>
using namespace Lumeda;
InputsLayer* InputsLayer::Create()
{
    LUMEDA_PROFILE;
    InputsLayerGLFW* window = LUMEDA_NEW(InputsLayerGLFW);
    return window;
}
#else
#error "Current platform not supported!"
#endif