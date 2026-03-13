#include <Lumeda/Core/Time.h>

using namespace Lumeda;

#ifdef LUMEDA_USE_GLFW
#include <Lumeda/Implementation/GLFW/TimeGLFW.h>
using namespace Lumeda;
Time* Time::Create()
{
    LUMEDA_PROFILE;
    TimeGLFW* time = LUMEDA_NEW(TimeGLFW);
    return time;
}
#else
#error "Current platform not supported!"
#endif