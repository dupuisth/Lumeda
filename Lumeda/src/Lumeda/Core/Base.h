#pragma once

#include <Lumeda/Core/Log.h>

#define LUMEDA_PROFILE
#define LUMEDA_PROFILE_FRAME
#define LUMEDA_PROFILE_SECTION(x)
#define LUMEDA_PROFILE_TAG(y, x)
#define LUMEDA_PROFILE_LOG(text, size)
#define LUMEDA_PROFILE_VALUE(text, value)

#if LUMEDA_PLATFORM_WINDOWS
#if LUMEDA_DEBUG
#define TRACY_ENABLE
#include <tracy/Tracy.hpp>
#define LUMEDA_PROFILE ZoneScoped
#define LUMEDA_PROFILE_FRAME FrameMark
#define LUMEDA_PROFILE_SECTION(x) ZoneScopedN(x)
#define LUMEDA_PROFILE_TAG(x) ZoneText(x, strlen(x))
#define LUMEDA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define LUMEDA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#endif
#endif