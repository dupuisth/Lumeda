#pragma once
#include <Lumeda/Core/Log.h>



#if LUMEDA_DEBUG
#define LUMEDA_ENABLE_ASSERTS
#endif

#pragma once

#if defined(_MSC_VER)
#define LUMEDA_DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#define LUMEDA_DEBUGBREAK() __builtin_trap()
#else
#include <cstdlib>
#define LUMEDA_DEBUGBREAK() std::abort()
#endif


#ifdef LUMEDA_ENABLE_ASSERTS

#define LUMEDA_INTERNAL_ASSERT_IMPL(type, check, fmt, ...)                     \
        do                                                                         \
        {                                                                          \
            if (!(check))                                                          \
            {                                                                      \
                LUMEDA##type##ERROR(fmt " ({0}:{1})"                               \
                    , __FILE__, __LINE__                                           \
                    __VA_OPT__(, ) __VA_ARGS__);                                   \
                LUMEDA_DEBUGBREAK();                                               \
            }                                                                      \
        } while (0)

#define LUMEDA_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
        LUMEDA_INTERNAL_ASSERT_IMPL(type, check, __VA_ARGS__)

#define LUMEDA_INTERNAL_ASSERT_NO_MSG(type, check)                             \
        LUMEDA_INTERNAL_ASSERT_IMPL(type, check,                                   \
            "Assertion failed: {0}", #check)

#define LUMEDA_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define LUMEDA_INTERNAL_ASSERT_GET_MACRO(...)                                   \
        LUMEDA_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__,                          \
            LUMEDA_INTERNAL_ASSERT_WITH_MSG,                                        \
            LUMEDA_INTERNAL_ASSERT_NO_MSG)

#define LUMEDA_ASSERT(...) \
        LUMEDA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__)

#define LUMEDA_CORE_ASSERT(...) \
        LUMEDA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__)

#else

#define LUMEDA_ASSERT(...)
#define LUMEDA_CORE_ASSERT(...)

#endif
