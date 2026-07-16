#pragma once

#if !defined(LUMEDA_PROFILING)
#define LUMEDA_PROFILE
#define LUMEDA_PROFILE_FRAME
#define LUMEDA_PROFILE_SECTION(x)
#define LUMEDA_PROFILE_TAG(x)
#define LUMEDA_PROFILE_LOG(text, size)
#define LUMEDA_PROFILE_VALUE(text, value)
#define LUMEDA_PROFILE_MEMORY_ALLOC(p, size)
#define LUMEDA_PROFILE_MEMORY_FREE(p)

#else

#define TRACY_ENABLE
#include <tracy/Tracy.hpp>
#define LUMEDA_PROFILING_ENABLED
#define LUMEDA_PROFILE ZoneScoped
#define LUMEDA_PROFILE_FRAME FrameMark
#define LUMEDA_PROFILE_SECTION(x) ZoneScopedN(x)
// #define LUMEDA_PROFILE_TAG(x) ZoneText(x, strlen(x))
#define LUMEDA_PROFILE_TAG(x) ZoneScoped
#define LUMEDA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define LUMEDA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#define LUMEDA_PROFILE_MEMORY_ALLOC(p, size) TracyAlloc(p, size);
#define LUMEDA_PROFILE_MEMORY_FREE(p) TracyFree(p);
#endif