#include <Lumeda/Gizmos/Gizmos.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLAD
#include <Lumeda/Implementation/OpenGL/GizmosOpenGL.h>
Gizmos* Gizmos::Create()
{
    GizmosOpenGL* gizmos = LUMEDA_NEW(GizmosOpenGL, MemTag::General);
    return gizmos;
}
#else
#error "Current platform not supported!"
#endif