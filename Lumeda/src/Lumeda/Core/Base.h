#pragma once

#include <Lumeda/Core/Log.h>

// Don't use tracy for Linux build (spent too much time on the Linux support so it's ok for now)
#if defined(LUMEDA_RELEASE) || defined(LUMEDA_PLATFORM_LINUX)
#define LUMEDA_PROFILE
#define LUMEDA_PROFILE_FRAME
#define LUMEDA_PROFILE_SECTION(x)
#define LUMEDA_PROFILE_TAG(y, x)
#define LUMEDA_PROFILE_LOG(text, size)
#define LUMEDA_PROFILE_VALUE(text, value)

#elif defined(LUMEDA_PLATFORM_WINDOWS)
// Enable tracy profiling
#include <tracy/Tracy.hpp>
#define LUMEDA_PROFILE ZoneScoped
#define LUMEDA_PROFILE_FRAME FrameMark
#define LUMEDA_PROFILE_SECTION(x) ZoneScopedN(x)
#define LUMEDA_PROFILE_TAG(x) ZoneText(x, strlen(x))
#define LUMEDA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define LUMEDA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#else
#error "Undefined profiling macros!"
#endif