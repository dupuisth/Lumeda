#include <Lumeda/Gizmos/Gizmos.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLAD
#include <Lumeda/Implementation/OpenGL/GizmosOpenGL.h>
std::unique_ptr<Gizmos> Gizmos::Create()
{
    std::unique_ptr<GizmosOpenGL> gizmos = std::make_unique<GizmosOpenGL>();
    return gizmos;
}
#else
#error "Current platform not supported!"
#endif